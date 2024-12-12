#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include <QSettings>
#include <QDebug>
#include "mainwindow.h"
#include "loginform.h"
#include "registerform.h"
#include "mainchatwindow.h"
#include "chatwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    //chatWindow = new ChatWindow("", this);
    loginForm = new LoginForm(this);
    registerForm = new RegisterForm(this);
    mainChatWindow = new MainChatWindow(this);
    //chatWindow = nullptr;

    if (checkTokens()) {
        validateTokens();
    } else {
        setCentralWidget(loginForm);
    }



    loginForm->setMinimumSize(300, 300);
    //loginForm->setMaximumSize(800, 600);

    registerForm->setMinimumSize(800, 600);
    //registerForm->setMaximumSize(1200, 800);

    mainChatWindow->setMinimumSize(600, 400);
    //mainChatWindow->setMaximumSize(1200, 800);

    setCentralWidget(loginForm);
    loginForm->show();
    registerForm->hide();
    mainChatWindow->hide();

    connect(loginForm, &LoginForm::goToRegister, this, &MainWindow::showRegisterForm);
    connect(registerForm, &RegisterForm::loginClicked, this, &MainWindow::showLoginForm);
    connect(loginForm, &LoginForm::loginSuccessful, this, &MainWindow::showMainChatWindow);
    connect(mainChatWindow, &MainChatWindow::chatSelected, this, &MainWindow::showChatWindow);
}

bool MainWindow::checkTokens() {
    QSettings settings;
    QString accessToken = settings.value("access_token").toString();
    QString refreshToken = settings.value("refresh_token").toString();

    if (accessToken.isEmpty() || refreshToken.isEmpty() || accessToken == refreshToken) {
        return false;
    }
    return true;
}

void MainWindow::validateTokens() {
    QSettings settings;
    QString accessToken = settings.value("access_token").toString();
    QString refreshToken = settings.value("refresh_token").toString();

    // Отправляем токены на сервер для проверки
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject jsonData;
    jsonData["token"] = accessToken;

    QJsonDocument doc(jsonData);
    QByteArray postData = doc.toJson();

    QNetworkReply *reply = manager->post(request, postData);
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            QJsonDocument responseDoc = QJsonDocument::fromJson(responseData);
            QJsonObject responseObj = responseDoc.object();
            showMainChatWindow();
        } else {
            QNetworkRequest request(url);
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

            QJsonObject jsonData;
            jsonData["token"] = refreshToken;

            QJsonDocument doc(jsonData);
            QByteArray postData = doc.toJson();
            connect(reply, &QNetworkReply::finished, [=](){
                if (reply->error() == QNetworkReply::NoError) {
                    QByteArray responseData = reply->readAll();
                    QJsonDocument responseDoc = QJsonDocument::fromJson(responseData);
                    QJsonObject responseObj = responseDoc.object();
                    QString accessToken = responseObj["access_token"].toString();
                    globalSettings->setValue("access_token", accessToken);
                    showMainChatWindow();
                } else {
                    setCentralWidget(loginForm);
                }
            });
        }
        reply->deleteLater();
    });
}


MainWindow::~MainWindow() {}

void MainWindow::showRegisterForm() {
    qDebug() << "showRegisterForm";
    loginForm->hide();
    //delete registerForm;
    registerForm = new RegisterForm(this);
    registerForm->show();
    setCentralWidget(registerForm);

    connect(registerForm, &RegisterForm::loginClicked, this, &MainWindow::showLoginForm);
}

void MainWindow::showLoginForm() {
    qDebug() << "showLoginForm";
    registerForm->hide();
    qDebug() << "showLoginForm2";
    //delete loginForm;
    loginForm = new LoginForm(this);
    loginForm->show();
    qDebug() << "showLoginForm3";
    setCentralWidget(loginForm);

    connect(loginForm, &LoginForm::goToRegister, this, &MainWindow::showRegisterForm);
    connect(loginForm, &LoginForm::loginSuccessful, this, &MainWindow::showMainChatWindow);
}

void MainWindow::showMainChatWindow() {
    qDebug() << "showMainChatWindow";
    loginForm->hide();
    qDebug() << "showMainChatWindow1";
    mainChatWindow->show();
    setCentralWidget(mainChatWindow);

    connect(mainChatWindow, &MainChatWindow::chatSelected, this, &MainWindow::showChatWindow);
}

void MainWindow::showChatWindow(const QString &chatName, const QString &chatId, const QString &recipientId) {
    if (chatWindow) {
        delete chatWindow;

        chatWindow = nullptr;
    }

    // Создаем новый объект ChatWindow
    chatWindow = new ChatWindow(chatName, chatId, recipientId, this);
    connect(chatWindow, &ChatWindow::backToChatList, this, &MainWindow::showMainChatWindow);

    // Устанавливаем центральный виджет на ChatWindow
    setCentralWidget(chatWindow);
}

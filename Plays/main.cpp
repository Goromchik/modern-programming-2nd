#include "mainwindow.h"
#include "loginwindow.h"

#include <QApplication>
#include <QPushButton>
#include <QtWidgets>
#include <QHBoxLayout>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QWidget window;
    window.setWindowTitle("Игра");
    window.setMinimumSize(400, 400);
    window.setMaximumSize(800, 800);   // Устанавливаем размер родительского виджета

    QVBoxLayout *mainLayout = new QVBoxLayout(&window);
    QHBoxLayout *buttonLayout = new QHBoxLayout(&window);

    QPushButton *button_login = new QPushButton("Войти");
    button_login->setFixedSize(80, 30);
    buttonLayout->addWidget(button_login);

    QPushButton *button_quit = new QPushButton("Выход");
    button_quit->setFixedSize(80, 30);
    buttonLayout->addWidget(button_quit);

    QObject::connect(button_quit, &QPushButton::clicked, &window, &QWidget::close); //закрывает окно

    QObject::connect(button_login, &QPushButton::clicked, [&]() {
        LoginWindow *loginWindow = new LoginWindow();
        loginWindow->show();
    });

    mainLayout->addLayout(buttonLayout);

    window.setLayout(mainLayout);


    // Показываем родительский виджет
    window.show();
    return a.exec();

}

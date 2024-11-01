#include "mainwindow.h"
#include "loginform.h"
#include "registerform.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    loginForm = new LoginForm(this);
    registerForm = new RegisterForm(this);

    setCentralWidget(loginForm);

    connect(loginForm, &LoginForm::registerClicked, this, &MainWindow::showRegisterForm);
    connect(registerForm, &RegisterForm::loginClicked, this, &MainWindow::showLoginForm);
}

MainWindow::~MainWindow() {}

void MainWindow::showRegisterForm() {
    setCentralWidget(registerForm);
}

void MainWindow::showLoginForm() {
    setCentralWidget(loginForm);
}

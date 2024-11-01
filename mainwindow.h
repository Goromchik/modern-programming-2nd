#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginform.h"
#include "registerform.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showRegisterForm();
    void showLoginForm();

private:
    LoginForm *loginForm;
    RegisterForm *registerForm;
};

#endif // MAINWINDOW_H

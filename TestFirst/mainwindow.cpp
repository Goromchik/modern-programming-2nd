#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->label->setText("Кнопка нажата!");
}


void MainWindow::on_pushButton_2_clicked() //отображение всплывающего диалогового окна
{
     QMessageBox::about(this, "Заголовок", "Просто текст внутри");
   // QMessageBox::critical(this, "Заголовок", "Просто текст внутри"); иконка с ошибкой
   // QMessageBox::information(this, "Заголовок", "Просто текст внутри");
   //  QMessageBox::warning(this, "Заголовок", "Просто текст внутри"); иконка с предупреждением
   //  QMessageBox::question(this, "Заголовок", "Просто текст внутри"); можно получить ответ да или нет

}


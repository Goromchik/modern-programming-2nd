#include "dialog.h"
#include "ui_dialog.h"


#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setFixedSize(300, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Hello World", this);
    layout->addWidget(label);

    QWidget::setLayout(layout);
}

Dialog::~Dialog()
{
    delete ui;
}

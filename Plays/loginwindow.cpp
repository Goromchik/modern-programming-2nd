#include "loginwindow.h"

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent) {
    setFixedSize(300, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Hello World", this);
    layout->addWidget(label);

    QWidget::setLayout(layout);
}

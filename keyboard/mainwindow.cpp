#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QApplication>
#include <QtWidgets>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget* window = centralWidget();
    window->setWindowTitle("Клавиатура");
    window->setMinimumSize(660, 300);
    //window.setMaximumSize(800, 800);

    QVBoxLayout *mainLayout = new QVBoxLayout(window);

    // поле для текста
    QLineEdit *display = new QLineEdit(window);
    display->setFixedHeight(50);
    display->setAlignment(Qt::AlignLeft);
    mainLayout->addWidget(display);

    // Макет для клавиатуры (сетка)
    QGridLayout *keyboardLayout = new QGridLayout();
    keyboardLayout->setSpacing(0);  // Отступы между кнопками
    mainLayout->addLayout(keyboardLayout);

    QStringList key = {"А", "Б", "В", "Г", "Д", "Е", " Ё", "Ж", "З", "И", "Й", "К", "Л", "М", "Н", "О", "П", "Р", "С", "Т", "У",
        "Ф", "Х", "Ц", "Ч", "Ш", "Щ", "ъ", "Ы", "Ь", "Э", "Ю", "Я"
    };

    int line=0; //строка
    int columns=0; // столбец
    const int buttonslicol = 11; // количество букв в строке
    for(const QString &letter : key){
        QPushButton *button_word = new QPushButton (letter, window);
        button_word->setMinimumSize(60, 60);
        button_word->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); //чтобы размер букв менялся автоматически
        keyboardLayout->addWidget(button_word, line, columns);

        QObject::connect(button_word, &QPushButton::clicked, display, [display, letter]() {
            QString currentText = display->text();
            currentText.append(letter);  // Добавляем букву к текущему тексту
            display->setText(currentText);
        });
        columns++;
        if (columns >= buttonslicol) {
            columns=0;
            line++;
        }
    }
    QPushButton *button_space = new QPushButton ("Пробел", window );
    //button_space->setFixedSize(200, 60);
    keyboardLayout->addWidget(button_space, line, 0, 1, 5);

    QObject::connect(button_space, &QPushButton::clicked, display, [display]() {
        QString currentText = display->text();
        currentText.append(" ");  // Добавляем пробел
        display->setText(currentText);
    });

    QPushButton *backspaceButton = new QPushButton("Удалить", window);
    backspaceButton->setFixedSize(120, 60);
    keyboardLayout->addWidget(backspaceButton, line, 5, 1, 3);

    QObject::connect(backspaceButton, &QPushButton::clicked, display, [display]() {
        QString currentText = display->text();
        currentText.chop(1);
        display->setText(currentText);
    });

    window->setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

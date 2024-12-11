#include <QJsonObject>
#include <QJsonDocument>
#include "chatwindow.h"

ChatWindow::ChatWindow(const QString &chatName, QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    QPalette palette;
    palette.setColor(QPalette::Window, QColor("#E0F0F6"));
    setPalette(palette);
    setAutoFillBackground(true);

    backButton = new QPushButton("Назад", this);
    backButton->setStyleSheet("background-color: #6C757D; color: white; border: none; border-radius: 5px; padding: 10px;");
    layout->addWidget(backButton, 0, Qt::AlignLeft);

    chatNameLabel = new QLabel(chatName, this);
    chatNameLabel->setAlignment(Qt::AlignCenter);
    chatNameLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
    layout->addWidget(chatNameLabel);

    messageDisplay = new QTextEdit(this);
    messageDisplay->setReadOnly(true);
    messageDisplay->setStyleSheet("border: 1px solid #ccc; border-radius: 5px; padding: 5px;");
    layout->addWidget(messageDisplay);

    messageInput = new QLineEdit(this);
    messageInput->setPlaceholderText("Введите сообщение...");
    messageInput->setStyleSheet("border: 1px solid #ccc; border-radius: 5px; padding: 5px;");
    layout->addWidget(messageInput);

    sendButton = new QPushButton("Отправить", this);
    sendButton->setStyleSheet("background-color: #007BFF; color: white; border: none; border-radius: 5px; padding: 10px;");
    layout->addWidget(sendButton);

    connect(sendButton, &QPushButton::clicked, this, &ChatWindow::sendMessage);
    connect(backButton, &QPushButton::clicked, this, &ChatWindow::backToChatList);

    webSocketClient = new WebSocketClient(this);
    connect(webSocketClient, &WebSocketClient::messageReceived, this, &ChatWindow::onMessageReceived);

    webSocketClient->connectToServer(QUrl("ws://192.168.243.187:8001/ws/user1"));
}

void ChatWindow::sendMessage() {
    QString messageContent = messageInput->text();
    if (!messageContent.isEmpty()) {
        // Создаем JSON-объект с необходимыми полями
        QJsonObject message;
        message["type"] = "message";
        message["chat_id"] = "675749186b5d0fb8979fa7e8";
        message["recipient_id"] = "user2";
        message["content"] = messageContent;

        // Преобразуем JSON-объект в строку и отправляем через WebSocket
        QJsonDocument doc(message);
        QString jsonString = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
        webSocketClient->sendMessage(jsonString);

        // Отображаем сообщение в интерфейсе
        messageDisplay->append(chatNameLabel->text() + ": " + messageContent);
        messageInput->clear();
    }
}

void ChatWindow::onMessageReceived(const QString &message) {
    messageDisplay->append("Собеседник: " + message);
}

void ChatWindow::setChatName(const QString &chatName) {
    chatNameLabel->setText(chatName);
}

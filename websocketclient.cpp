#include "websocketclient.h"
#include <QDebug>

WebSocketClient::WebSocketClient(QObject *parent) : QObject(parent) {
    m_webSocket = new QWebSocket();

    connect(m_webSocket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
    connect(m_webSocket, &QWebSocket::disconnected, this, &WebSocketClient::onDisconnected);
    connect(m_webSocket, &QWebSocket::textMessageReceived, this, &WebSocketClient::onTextMessageReceived);
}

WebSocketClient::~WebSocketClient() {
    m_webSocket->close();
    delete m_webSocket;
}

void WebSocketClient::connectToServer(const QUrl &url) {
    m_url = url;
    m_webSocket->open(m_url);
}

void WebSocketClient::sendMessage(const QString &message) {
    if (m_webSocket->state() == QAbstractSocket::ConnectedState) {
        m_webSocket->sendTextMessage(message);
    } else {
        qDebug() << "WebSocket is not connected.";
    }
}

void WebSocketClient::onConnected() {
    qDebug() << "WebSocket connected to" << m_url;
    emit connected();
}

void WebSocketClient::onDisconnected() {
    qDebug() << "WebSocket disconnected from" << m_url;
    qDebug() << "Error:" << m_webSocket->errorString();
    emit disconnected();
}

void WebSocketClient::onTextMessageReceived(const QString &message) {
    qDebug() << "Message received:" << message;
    emit messageReceived(message);
}

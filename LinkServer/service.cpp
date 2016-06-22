#include "service.h"
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QDataStream>
#include <QThreadPool>
#include <QDebug>
#include "acceptor.h"
#include "messagetask.h"

Service::Service(QObject *parent, QTcpSocket *tcpSocket, int sessionID) :
    QObject(parent), m_tcpSocket(tcpSocket), m_sessionID(sessionID), m_blockSize(0)
{
    if (m_tcpSocket)
    {
        connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        connect(m_tcpSocket, SIGNAL(disconnected()), this, SLOT(onDisconnect()));
        connect(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
    }
    qDebug() << "client connected: " << m_tcpSocket->peerAddress() << " id: " << m_sessionID;
}

int Service::sessionID()
{
    return m_sessionID;
}

void Service::sendData(const QString &data)
{
    m_tcpSocket->write(data.toLocal8Bit(), data.size());
}

void Service::onReadyRead()
{
    QDataStream in(m_tcpSocket);
    in.setVersion(QDataStream::Qt_5_6);

    //获取消息长度的前2个字节
    if (m_blockSize == 0)
    {
        if (m_tcpSocket->bytesAvailable() < (int)sizeof(m_blockSize))
            return;
    }

    in >> m_blockSize;

    //获取消息
    if (m_tcpSocket->bytesAvailable() < m_blockSize)
        return;

    QString message;
    in >> message;

    QThreadPool::globalInstance()->start(new MessageTask(message));
}

void Service::onDisconnect()
{
    emit signalDisconncet(m_sessionID);
}

void Service::onError(QAbstractSocket::SocketError error)
{
    qDebug() << "socket error" << error;
    m_tcpSocket->close();
}

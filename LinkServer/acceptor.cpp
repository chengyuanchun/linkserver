#include "acceptor.h"
#include <QDebug>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include "service.h"
#include "idcreator.h"


Acceptor::Acceptor(QObject *parent) : QObject(parent), m_tcpServer(NULL)
{
    m_tcpServer = new QTcpServer(this);
}

Acceptor::~Acceptor()
{
    if (m_tcpServer)
        delete m_tcpServer;
}

int Acceptor::open(const QHostAddress &listenAddr, short port)
{
    if (!m_tcpServer->listen(listenAddr, port))
        return -1;

    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
    connect(m_tcpServer, SIGNAL(acceptError(QAbstractSocket::SocketError)), this, SLOT(onAcceptError(QAbstractSocket::SocketError)));

    qDebug() << "listen:" << m_tcpServer->serverAddress() << ":" << m_tcpServer->serverPort();
    return 0;
}

Service *Acceptor::getService(int sessionID)
{
    Service* result = 0;

    foreach(Service* service, m_services)
    {
        if (service->sessionID() == sessionID)
            result = service;
    }

    return result;
}

QList<Service *>& Acceptor::services()
{
    return m_services;
}

void Acceptor::onNewConnection()
{
    QTcpSocket *client = m_tcpServer->nextPendingConnection();

    Service *service = new Service(this, client, IDCreator::instance()->id());
    connect(service, SIGNAL(signalDisconncet(int)), this, SLOT(onDisconnect(int)));
    m_services.push_back(service);
}

void Acceptor::onAcceptError(QAbstractSocket::SocketError error)
{
    qDebug() << "acceptor error" << error;
    m_tcpServer->close();
}

void Acceptor::onDisconnect(int sessionID)
{
    removeService(sessionID);
}

void Acceptor::removeService(int sessionID)
{
    foreach (Service* service, m_services)
    {
        if (service->sessionID() == sessionID)
        {
            m_services.removeOne(service);
            if (service) delete service;
        }
    }
}

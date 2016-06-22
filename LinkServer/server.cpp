#include "server.h"
#include "acceptor.h"
#include <QDebug>

Server::Server(QObject *parent) : QObject(parent)
{
    m_acceptor = new Acceptor(this);
}

Server::Server(const QString &ip, short port, QObject *parent) : QObject(parent),
    m_ip(ip), m_port(port)
{
    m_acceptor = new Acceptor(this);
}

Server::~Server()
{
    if (m_acceptor)
        delete m_acceptor;
}

void Server::start()
{
    if (m_ip.isEmpty())
        m_acceptor->open(QHostAddress::Any, m_port);
    else
        m_acceptor->open(QHostAddress(m_ip), m_port);
}

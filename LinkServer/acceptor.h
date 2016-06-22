#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <QObject>
#include <QList>
#include <QtNetwork/QHostAddress>

class QTcpServer;
class Service;

class Acceptor : public QObject
{
    Q_OBJECT
public:
    explicit Acceptor(QObject *parent = 0);
    ~Acceptor();

    int open(const QHostAddress &listenAddr, short port);

    Service* getService(int sessionID);
    QList<Service*>& services();

protected slots:
    void onNewConnection();
    void onAcceptError(QAbstractSocket::SocketError);
    void onDisconnect(int sessionID);

private:
    void removeService(int sessionID);

private:
    QTcpServer *m_tcpServer;
    QList<Service*> m_services;
};

#endif // ACCEPTOR_H

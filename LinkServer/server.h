#ifndef SERVER_H
#define SERVER_H

#include <QObject>

class Acceptor;

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    explicit Server(const QString &ip, short port, QObject *parent = 0);
    ~Server();
    void start();

private:
    Acceptor *m_acceptor = NULL;
    QString m_ip;
    short m_port = 60000;
};

#endif // SERVER_H

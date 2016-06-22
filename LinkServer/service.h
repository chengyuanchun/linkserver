#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>
#include <QtNetwork/QAbstractSocket>

class QTcpSocket;


class Service : public QObject
{
    Q_OBJECT
public:
    explicit Service(QObject *parent = 0, QTcpSocket *tcpSocket= 0, int sessionID = 0);

    int sessionID();
    void sendData(const QString &data);

signals:
    void signalDisconncet(int sessionID);

private slots:
    void onReadyRead();
    void onDisconnect();
    void onError(QAbstractSocket::SocketError);

private:
    QTcpSocket *m_tcpSocket;
    int m_sessionID;
    short m_blockSize;
};

#endif // SERVICE_H

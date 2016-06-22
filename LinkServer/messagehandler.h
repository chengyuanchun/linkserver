#ifndef MESAAGEHANDLER_H
#define MESAAGEHANDLER_H

#include <QObject>
#include <QQueue>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>


const int g_maxQueueSize = 1024;
QWaitCondition g_queueNotEmpty;
QWaitCondition g_queueNotFull;
QMutex g_mutex;
QQueue<QString> g_queue;


class Producer : public QThread
{
public:
    Producer(QObject *parent = NULL);
    void run() Q_DECL_OVERRIDE;

private:
    QQueue<QString> m_queue;
};


class Consumer : public QThread
{
public:
    Consumer(QObject *parent = NULL);
    void run() Q_DECL_OVERRIDE;
};


class MessageHandler : public QObject
{
    Q_OBJECT
public:
    explicit MesaageHandler(QObject *parent = 0);
    void pushMessage();
    void processMessage(const QString &message);

};

#endif // MESAAGEHANDLER_H

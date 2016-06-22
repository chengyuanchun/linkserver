#include "messagehandler.h"

MessageHandler::MesaageHandler(QObject *parent) : QObject(parent)
{

}

void MessageHandler::pushMessage()
{

}

void MessageHandler::processMessage(const QString &message)
{

}

Producer::Producer(QObject *parent) : QThread(parent)
{

}

void Producer::run()
{
    while (true)
    {
        g_mutex.lock();
        if (g_queue.size() >= g_maxQueueSize)
            g_queueNotFull.wait(&g_mutex);

        QString message = g_queue.front();
        g_queue.pop_front();

        g_mutex.unlock();
        g_queueNotEmpty.wakeAll();

        MessageHandler *handler = dynamic_cast<MessageHandler*>(parent());
        if (handler)
            handler->processMessage(message);
    }
}

Consumer::Consumer(QObject *parent) : QThread(parent)
{

}

void Consumer::run()
{
    while (true)
    {
        g_mutex.lock();
        if (g_queue.size() == 0)
            g_queueNotEmpty.wait(&g_mutex);

        QString message = g_queue.front();
        g_queue.pop_front();

        g_mutex.unlock();
        g_queueNotFull.wakeAll();

        MessageHandler *handler = dynamic_cast<MessageHandler*>(parent());
        if (handler)
            handler->processMessage(message);

    }
}

#include "messagetask.h"
#include <QDebug>

MessageTask::MessageTask(const QString &message) : m_message(message)
{

}

void MessageTask::run()
{
    qDebug() << m_message;
}

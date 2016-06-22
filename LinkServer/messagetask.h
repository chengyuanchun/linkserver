#ifndef MESSAGETASK_H
#define MESSAGETASK_H

#include <QRunnable>
#include <QString>

class MessageTask : public QRunnable
{
public:
    MessageTask(const QString &message);
    void run() override;

private:
    QString m_message;
};

#endif // MESSAGETASK_H

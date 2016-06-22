#ifndef IDCREATOR_H
#define IDCREATOR_H

#include <QObject>
#include <QMutex>

class IDCreator : public QObject
{
    Q_OBJECT
public:
    static IDCreator* instance();

    int id();

private:
    IDCreator(QObject *parent = 0);
    IDCreator(const IDCreator &);
    IDCreator& operator = (const IDCreator &);

private:
    static IDCreator *m_instance;
    static QMutex m_mutex;

    int m_id = 0;
};

#endif // IDCREATOR_H

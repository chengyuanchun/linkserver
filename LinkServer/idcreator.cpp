#include "idcreator.h"

IDCreator *IDCreator::m_instance = NULL;
QMutex IDCreator::m_mutex;

IDCreator *IDCreator::instance()
{
    if (m_instance == NULL)
    {
        m_mutex.lock();
        if (m_instance == NULL)
        {
            m_instance = new IDCreator();
        }
        m_mutex.unlock();
    }
    return m_instance;
}

int IDCreator::id()
{
    return m_id++;
}

IDCreator::IDCreator(QObject *parent) : QObject(parent)
{

}


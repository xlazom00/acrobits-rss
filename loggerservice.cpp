#include "loggerservice.h"

#include <QMutexLocker>
#include <QDebug>
#include <QFile>
#include <QDir>

LoggerService::LoggerService()
{
    start();
}

LoggerService::~LoggerService()
{
    quit();
}


void LoggerService::writeMessage( const QString & message )
{
    {
        QMutexLocker lock(&m_mutex);
        m_pendingMessages.append(message);
    }
    resume();
}

void LoggerService::resume()
{
    m_waitCondition.wakeAll();
}


void LoggerService::quit()
{
    m_quit = true;

    m_waitCondition.wakeAll();


    wait();
}

void LoggerService::run()
{
    while(m_quit == false)
    {
        {
            QMutexLocker locker(&m_mutex);
            m_waitCondition.wait(&m_mutex);
        }

        processMessages();
    }

    if (m_quit)
    {
        m_file.close();
    }
}

void LoggerService::processMessages()
{
    QList<QString> pendingMessages;
    {
        QMutexLocker lock(&m_mutex);
        pendingMessages = m_pendingMessages;
        m_pendingMessages = {};
    }
	if (pendingMessages.isEmpty())
		return;

    // write to file log
    if (m_file.isOpen() == false)
    {
        QString fileName = QDir::currentPath() + QDir::separator() + "file.log";
        m_file.setFileName(fileName);
        m_file.open(QIODeviceBase::OpenModeFlag::WriteOnly | QIODeviceBase::OpenModeFlag::Append | QIODeviceBase::OpenModeFlag::Text);
    }

    QTextStream textStream(&m_file);
    for (const auto & message : qAsConst(pendingMessages))
    {
        textStream << message + "\n";
    }
}


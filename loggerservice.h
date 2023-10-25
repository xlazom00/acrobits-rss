#ifndef LOGGERSERVICE_H
#define LOGGERSERVICE_H

#include <QList>
#include <QString>
#include <QMutex>
#include <QWaitCondition>
#include <QThread>
#include <QFile>


class LoggerService: public QThread
{
    Q_OBJECT

public:
    LoggerService();
    ~LoggerService();


    void writeMessage( const QString & message );
    void quit();

protected:
    void run() override;

private:
    void resume();
    void processMessages();

private:
    QMutex m_mutex;
    QList<QString> m_pendingMessages;

    QWaitCondition m_waitCondition;

    bool m_quit = false;

    QFile m_file;
};

#endif // LOGGERSERVICE_H

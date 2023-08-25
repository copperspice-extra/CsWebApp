/**
  @file
  @author Stefan Frings
*/

#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <QDateTime>
#include <QThread>
#include <QObject>
#include <QRecursiveMutex>
using namespace stefanfrings;

Logger* Logger::defaultLogger=nullptr;


QThreadStorage<QHash<QString,QString>*> Logger::logVars;


QMutex Logger::mutex;


Logger::Logger(QObject* parent)
    : QObject(parent),
    msgFormat("{timestamp} {type} {msg}"),
    timestampFormat("dd.MM.yyyy hh:mm:ss.zzz"),
    minLevel(QtDebugMsg),
    bufferSize(0)
    {}


Logger::Logger(const QString msgFormat, const QString timestampFormat, const QtMsgType minLevel, const int bufferSize, QObject* parent)
    :QObject(parent)
{
    this->msgFormat=msgFormat;
    this->timestampFormat=timestampFormat;
    this->minLevel=minLevel;
    this->bufferSize=bufferSize;
}
    static QRecursiveMutex recursiveMutex;
    static QMutex nonRecursiveMutex;

void Logger::msgHandler(const QtMsgType type, const QString &message, const QString &file, const QString &function, const int line)
{   
    // Prevent multiple threads from calling this method simultaneoulsy.
    // But allow recursive calls, which is required to prevent a deadlock
    // if the logger itself produces an error message.
    recursiveMutex.lock();

    // Fall back to stderr when this method has been called recursively.
    if (defaultLogger && nonRecursiveMutex.tryLock())
    {
        defaultLogger->log(type, message, file, function, line);
        nonRecursiveMutex.unlock();
    }
    else
    {
        fputs(qPrintable(message),stderr);
        fflush(stderr);
    }

    // Abort the program after logging a fatal message
    if (type==QtFatalMsg)
    {
        abort();
    }

    recursiveMutex.unlock();
}

    void Logger::msgHandler4(const QtMsgType type,QStringView message)
      {
      msgHandler(type,message);
      }


Logger::~Logger()
{
    if (defaultLogger==this)
    {
        csInstallMsgHandler(nullptr);
        defaultLogger=nullptr;
    }
}


void Logger::write(const LogMessage* logMessage)
{
    fputs(qPrintable(logMessage->toString(msgFormat,timestampFormat)),stderr);
    fflush(stderr);
}


void Logger::installMsgHandler()
{
    defaultLogger=this;
    qInstallMsgHandler(msgHandler4);
}


void Logger::set(const QString& name, const QString& value)
{
    mutex.lock();
    if (!logVars.hasLocalData())
    {
        logVars.setLocalData(new QHash<QString,QString>);
    }
    logVars.localData()->insert(name,value);
    mutex.unlock();
}


void Logger::clear(const bool buffer, const bool variables)
{
    mutex.lock();
    if (buffer && buffers.hasLocalData())
    {
        QList<LogMessage*>* buffer=buffers.localData();
        while (buffer && !buffer->isEmpty())
        {
            LogMessage* logMessage=buffer->takeLast();
            delete logMessage;
        }
    }
    if (variables && logVars.hasLocalData())
    {
        logVars.localData()->clear();
    }
    mutex.unlock();
}


void Logger::log(const QtMsgType type, const QString& message, const QString &file, const QString &function, const int line)
{    
    // Check if the type of the message reached the configured minLevel in the order
    // DEBUG, INFO, WARNING, CRITICAL, FATAL
    // Since Qt 5.5: INFO messages are between DEBUG and WARNING
    bool toPrint=false;
    switch (type)
    {
        case QtDebugMsg:
            if (minLevel==QtDebugMsg)
            {
                toPrint=true;
            }
            break;
/*
        case QtInfoMsg:
            if (minLevel==QtDebugMsg || minLevel == QtInfoMsg) {
                toPrint = true;
            }
            break;
*/

        case QtWarningMsg:
//          if (minLevel==QtDebugMsg || minLevel==QtInfoMsg || minLevel == QtWarningMsg) {

            if (minLevel==QtDebugMsg || minLevel == QtWarningMsg) {
                toPrint=true;
            }
            break;

        case QtCriticalMsg: // or QtSystemMsg which has the same int value
//          if (minLevel==QtDebugMsg || minLevel==QtInfoMsg ||  minLevel==QtWarningMsg || minLevel==QtCriticalMsg) {

            if (minLevel==QtDebugMsg || minLevel==QtWarningMsg || minLevel==QtCriticalMsg) {
               toPrint=true;
            }
            break;

        case QtFatalMsg:
            toPrint=true;
            break;

        default: // For additional type that might get introduced in future
            toPrint=true;
    }

    mutex.lock();

    // If the buffer is enabled, write the message into it
    if (bufferSize>0)
    {
        // Create new thread local buffer, if necessary
        if (!buffers.hasLocalData())
        {
            buffers.setLocalData(new QList<LogMessage*>());
        }
        QList<LogMessage*>* buffer=buffers.localData();

        // Append the decorated log message to the buffer
        LogMessage* logMessage=new LogMessage(type,message,logVars.localData(),file,function,line);
        buffer->append(logMessage);

        // Delete oldest message if the buffer became too large
        if (buffer->size()>bufferSize)
        {
            delete buffer->takeFirst();
        }

        // Print the whole buffer if the type is high enough
        if (toPrint)
        {
            // Print the whole buffer content
            while (!buffer->isEmpty())
            {
                LogMessage* logMessage=buffer->takeFirst();
                write(logMessage);
                delete logMessage;
            }
        }
    }

    // Buffer is disabled, print the message if the type is high enough
    else
    {
        if (toPrint)
        {
            LogMessage logMessage(type,message,logVars.localData(),file,function,line);
            write(&logMessage);
        }
    }
    mutex.unlock();
}

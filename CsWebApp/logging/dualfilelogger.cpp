/**
  @file
  @author Stefan Frings
*/

/**************************************************************************
*
* Copyright 2023 Barbara Geller
* Copyright 2023 Ansel Sermersheim
*
* CsWebApp is released under the LGPL 3.0 license and is derivative work
*
* This project is distributed WITHOUT ANY WARRANTY; without even the
* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
**************************************************************************/

#include "dualfilelogger.h"

using namespace stefanfrings;

DualFileLogger::DualFileLogger(QSettings *firstSettings, QSettings* secondSettings, const int refreshInterval, QObject* parent)
    :Logger(parent)
{
     firstLogger=new FileLogger(firstSettings, refreshInterval, this);
     secondLogger=new FileLogger(secondSettings, refreshInterval, this);
}

void DualFileLogger::log(const QtMsgType type, const QString& message, const QString &file,
      const QString &function, const int line)
{
    firstLogger->log(type,message,file,function,line);
    secondLogger->log(type,message,file,function,line);
}

void DualFileLogger::clear(const bool buffer, const bool variables)
{
    firstLogger->clear(buffer,variables);
    secondLogger->clear(buffer,variables);
}

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

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QSet>
#include <QStringList>
#include <QTextStream>
#include <QRegularExpression>

#include "templateloader.h"

using namespace stefanfrings;

TemplateLoader::TemplateLoader(const QSettings *settings, QObject *parent)
    : QObject(parent)
{
    templatePath=settings->value("path",QString(".")).toString();
    // Convert relative path to absolute, based on the directory of the config file.
#ifdef Q_OS_WIN32
    if (QDir::isRelativePath(templatePath) && settings->format()!=QSettings::NativeFormat)
#else
    if (QDir::isRelativePath(templatePath))
#endif
    {
        QFileInfo configFile(settings->fileName());
        templatePath=QFileInfo(configFile.absolutePath(),templatePath).absoluteFilePath();
    }
    fileNameSuffix=settings->value("suffix",QString(".tpl")).toString();
    QString encoding=settings->value("encoding").toString();
    if (encoding.isEmpty())
    {
        textCodec=QTextCodec::codecForLocale();
    }
    else
    {
       textCodec=QTextCodec::codecForName(encoding.toUtf8());
    }
    qDebug("TemplateLoader: path=%s, codec=%s",qPrintable(templatePath),qPrintable(encoding));
}

TemplateLoader::~TemplateLoader()
{}

QString TemplateLoader::tryFile(QString localizedName)
{
    QString fileName=templatePath+"/"+localizedName+fileNameSuffix;
    qDebug("TemplateCache: trying file %s",qPrintable(fileName));
    QFile file(fileName);
    if (file.exists()) {
        file.open(QIODevice::ReadOnly);
        QString document=textCodec->toUnicode(file.readAll());
        file.close();
        if (file.error())
        {
            qCritical("TemplateLoader: cannot load file %s, %s",qPrintable(fileName),qPrintable(file.errorString()));
            return "";
        }
        else
        {
            return document;
        }
    }
    return "";
}

Template TemplateLoader::getTemplate(QString templateName, QString locales)
{
    QSet<QString> tried; // used to suppress duplicate attempts

    QStringList locs=locales.split(',',QStringParser::SkipEmptyParts);

    // Search for exact match
    //foreach (QString loc,locs)
    for(int i=0; i<locs.size(); i++)
    {
        locs[i].replace(QRegularExpression(";.*"),"");
        locs[i].replace('-','_');

        QString localizedName=templateName+"-"+locs[i].trimmed();
        if (!tried.contains(localizedName))
        {
            QString document=tryFile(localizedName);
            if (!document.isEmpty()) {
                return Template(document,localizedName);
            }
            tried.insert(localizedName);
        }
    }

    // Search for correct language but any country
    //foreach (QString loc,locs)
    for(int i=0; i<locs.size(); i++)
    {
        locs[i].replace(QRegularExpression("[;_-].*"),"");
        QString localizedName=templateName+"-"+locs[i].trimmed();

        if (!tried.contains(localizedName))
        {
            QString document=tryFile(localizedName);
            if (!document.isEmpty())
            {
                return Template(document,localizedName);
            }
            tried.insert(localizedName);
        }
    }

    // Search for default file
    QString document=tryFile(templateName);
    if (!document.isEmpty())
    {
        return Template(document,templateName);
    }

    qCritical("TemplateCache: cannot find template %s",qPrintable(templateName));
    return Template("",templateName);
}

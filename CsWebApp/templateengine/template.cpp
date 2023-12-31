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

#include <QFileInfo>

#include "template.h"

using namespace stefanfrings;

Template::Template(const QString source, const QString sourceName)
    : QString(source)
{
    this->sourceName=sourceName;
    this->warnings=false;
}

Template::Template(QFile& file, const QTextCodec* textCodec)
{
    this->warnings=false;
    sourceName=QFileInfo(file.fileName()).baseName();

    if (!file.isOpen()) {
        file.open(QFile::ReadOnly | QFile::Text);
    }

    QByteArray data=file.readAll();
    file.close();

    if (data.size()==0 || file.error())
    {
        qCritical("Template: Can not read from %s, %s", csPrintable(sourceName), csPrintable(file.errorString()));
    }
    else
    {
        append(textCodec->toUnicode(data));
    }
}

int Template::setVariable(const QString name, const QString value)
{
    int count=0;
    QString variable="{"+name+"}";
    int start=indexOf(variable);

    while (start>=0) {
        replace(start, variable.length(), value);
        count++;
        start=indexOf(variable,start+value.length());
    }

    if (count==0 && warnings) {
        qWarning("Template: Missing variable %s in %s", csPrintable(variable), csPrintable(sourceName));
    }

    return count;
}

int Template::setCondition(const QString name, const bool value)
{
    int count=0;
    QString startTag=QString("{if %1}").formatArg(name);
    QString elseTag=QString("{else %1}").formatArg(name);
    QString endTag=QString("{end %1}").formatArg(name);

    // search for if-else-end
    int start=indexOf(startTag);

    while (start>=0)
    {
        int end=indexOf(endTag,start+startTag.length());
        if (end>=0)
        {
            count++;
            int ellse=indexOf(elseTag,start+startTag.length());
            if (ellse>start && ellse<end)
            {
                // there is an else part
                if (value==true)
                {
                    QString truePart=mid(start+startTag.length(), ellse-start-startTag.length());
                    replace(start, end-start+endTag.length(), truePart);
                }
                else
                {
                    // value==false
                    QString falsePart=mid(ellse+elseTag.length(), end-ellse-elseTag.length());
                    replace(start, end-start+endTag.length(), falsePart);
                }
            }
            else if (value==true)
            {
                // and no else part
                QString truePart=mid(start+startTag.length(), end-start-startTag.length());
                replace(start, end-start+endTag.length(), truePart);
            }
            else
            {
                // value==false and no else part
                replace(start, end-start+endTag.length(), "");
            }
            start=indexOf(startTag,start);
        }
        else
        {
            qWarning("Template: Missing condition end %s in %s", csPrintable(endTag), csPrintable(sourceName));
        }
    }

    // search for ifnot-else-end
    QString startTag2="{ifnot "+name+"}";
    start=indexOf(startTag2);

    while (start>=0) {
        int end=indexOf(endTag,start+startTag2.length());
        if (end>=0)
        {
            count++;
            int ellse=indexOf(elseTag,start+startTag2.length());
            if (ellse>start && ellse<end)
            {
                // there is an else part
                if (value==false)
                {
                    QString falsePart=mid(start+startTag2.length(), ellse-start-startTag2.length());
                    replace(start, end-start+endTag.length(), falsePart);
                }
                else
                {
                    // value==true
                    QString truePart=mid(ellse+elseTag.length(), end-ellse-elseTag.length());
                    replace(start, end-start+endTag.length(), truePart);
                }
            }
            else if (value==false)
            {
                // and no else part
                QString falsePart=mid(start+startTag2.length(), end-start-startTag2.length());
                replace(start, end-start+endTag.length(), falsePart);
            }
            else
            {
                // value==true and no else part
                replace(start, end-start+endTag.length(), "");
            }
            start=indexOf(startTag2,start);
        }
        else
        {
            qWarning("Template: missing condition end %s in %s", csPrintable(endTag), csPrintable(sourceName));
        }
    }

    if (count==0 && warnings) {
        qWarning("Template: missing condition %s or %s in %s", csPrintable(startTag),
              csPrintable(startTag2), csPrintable(sourceName));
    }

    return count;
}

int Template::loop(const QString name, const int repetitions)
{
    Q_ASSERT(repetitions>=0);

    int count=0;
    QString startTag="{loop "+name+"}";
    QString elseTag="{else "+name+"}";
    QString endTag="{end "+name+"}";

    // search for loop-else-end
    int start=indexOf(startTag);

    while (start>=0)
    {
        int end=indexOf(endTag,start+startTag.length());
        if (end>=0)
        {
            count++;
            int ellse=indexOf(elseTag,start+startTag.length());
            if (ellse>start && ellse<end)
            {
                // there is an else part
                if (repetitions>0)
                {
                    QString loopPart=mid(start+startTag.length(), ellse-start-startTag.length());
                    QString insertMe;
                    for (int i=0; i<repetitions; ++i)
                    {
                        // number variables, conditions and sub-loop within the loop
                        QString nameNum=name+QString::number(i);
                        QString s=loopPart;
                        s.replace(QString("{%1.").formatArg(name), QString("{%1.").formatArg(nameNum));
                        s.replace(QString("{if %1.").formatArg(name), QString("{if %1.").formatArg(nameNum));
                        s.replace(QString("{ifnot %1.").formatArg(name), QString("{ifnot %1.").formatArg(nameNum));
                        s.replace(QString("{else %1.").formatArg(name), QString("{else %1.").formatArg(nameNum));
                        s.replace(QString("{end %1.").formatArg(name), QString("{end %1.").formatArg(nameNum));
                        s.replace(QString("{loop %1.").formatArg(name), QString("{loop %1.").formatArg(nameNum));
                        insertMe.append(s);
                    }
                    replace(start, end-start+endTag.length(), insertMe);
                }
                else
                {
                    // repetitions==0
                    QString elsePart=mid(ellse+elseTag.length(), end-ellse-elseTag.length());
                    replace(start, end-start+endTag.length(), elsePart);
                }
            }
            else if (repetitions>0)
            {
                // and no else part
                QString loopPart=mid(start+startTag.length(), end-start-startTag.length());
                QString insertMe;
                for (int i=0; i<repetitions; ++i)
                {
                    // number variables, conditions and sub-loop within the loop
                    QString nameNum=name+QString::number(i);
                    QString s=loopPart;
                    s.replace(QString("{%1.").formatArg(name), QString("{%1.").formatArg(nameNum));
                    s.replace(QString("{if %1.").formatArg(name), QString("{if %1.").formatArg(nameNum));
                    s.replace(QString("{ifnot %1.").formatArg(name), QString("{ifnot %1.").formatArg(nameNum));
                    s.replace(QString("{else %1.").formatArg(name), QString("{else %1.").formatArg(nameNum));
                    s.replace(QString("{end %1.").formatArg(name), QString("{end %1.").formatArg(nameNum));
                    s.replace(QString("{loop %1.").formatArg(name), QString("{loop %1.").formatArg(nameNum));
                    insertMe.append(s);
                }
                replace(start, end-start+endTag.length(), insertMe);
            }
            else
            {
                // repetitions==0 and no else part
                replace(start, end-start+endTag.length(), "");
            }
            start=indexOf(startTag,start);
        }
        else
        {
            qWarning("Template: Missing loop end %s in %s", csPrintable(endTag), csPrintable(sourceName));
        }
    }

    if (count==0 && warnings) {
        qWarning("Template: missing loop %s in %s", csPrintable(startTag), csPrintable(sourceName));
    }

    return count;
}

void Template::enableWarnings(const bool enable)
{
    warnings=enable;
}


#include "tecplot.h"

#include "teczonereader.h"

#include <QTextStream>
#include <QStringList>
#include <QStringBuilder>
#include <QThreadPool>

TecPlot::TecPlot()
{
}

bool
TecPlot::readFile(QFile file)
{
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    QString data;

    data = in.readAll();

    file.close();

    //Split the different Zones
    QStringList zones = data.split("ZONE", QString::SkipEmptyParts, Qt::CaseInsensitive);

    //try to read header read header data
    QString header = removeComments(zones.first()); //it is saver to remove comments manually
    QStringList headerList = header.split('=');

    QStringList::iterator line;
    for (line = headerList.begin(); line != headerList.end(); ++line)
    {
       QString simpleLine = line->simplified();
       if(QString::compare(simpleLine, "Variables", Qt::CaseInsensitive) == 0)
       {
           ++line;
           m_Variables = wordSplitter(*line, {' ', ','}, {'\"'});
       }
       else if(QString::compare(simpleLine, "Filetype", Qt::CaseInsensitive) == 0)
       {
           ++line;
           m_FileType = line->simplified();
       }
       else if(QString::compare(simpleLine, "Title", Qt::CaseInsensitive) == 0)
       {
           ++line;
           m_Title = line->simplified();
       }
    }

    //reading zones
    QThreadPool *threadPool = QThreadPool::globalInstance();
    foreach (QString zoneData, zones)
    {
        TecZoneReader zoneReader(zoneData, m_Variables);
        zoneReader.setAutoDelete(false);
        threadPool->start(&zoneReader);
    }

    threadPool->waitForDone();

    return true;
}

QString
TecPlot::removeComments(QString input)
{
    QStringList retList;
    foreach (QString line, input.split(QRegExp("[\r\n]"), QString::SkipEmptyParts))
    {
        QString simpleLine = line.simplified();
        if(simpleLine[0] == '#')
           retList << simpleLine;
    }

    return retList.join(' ');
}

QStringList
TecPlot::wordSplitter(QString text, QVector<QChar> splitChars, QVector<QChar> oneWordChar)
{
    QStringList retval;

    QString word;
    bool oneWord = false;
    foreach (QChar letter, text)
    {
        if(oneWordChar.contains(letter))
        {
            if(oneWord)
            {
                retval << word;
                word.clear();
            }

            oneWord != oneWord;
        }
        else if(splitChars.contains(letter))
        {
            if(oneWord)
            {
                word += letter;
            }
            else
            {
                retval << word;
                word.clear();
            }
        }
        else
            word += letter;
    }
}

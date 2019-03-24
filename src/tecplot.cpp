#include "tecplot.h"

#include <QTextStream>
#include <QStringList>
#include <QStringBuilder>

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

    //remove all comments while reading the file
    QString line = in.readLine();
    while (!line.isNull())
    {
        QString simple = line.simplified();
        if(simple.at(0) != '#')
            data += simple;
    }

    file.close();

    //Split the different Zones
    QStringList zones = data.split("ZONE", QString::SkipEmptyParts, Qt::CaseInsensitive);
}

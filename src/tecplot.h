#ifndef TECPLOT_H
#define TECPLOT_H

#include "tecplot_global.h"

#include "teczone.h"

#include <QObject>
#include <QFile>

class TECPLOTSHARED_EXPORT TecPlot : public QObject
{
    Q_OBJECT

public:
    TecPlot();
    bool readFile(QFile file);

private:
    QString removeComments(QString input);
    QStringList wordSplitter(QString text, QVector<QChar> splitChars, QVector<QChar> oneWordChar);

    QVector<TecZone> m_Zones;
    QString m_Title;
    QString m_FileType;
    QStringList m_Variables;

};

#endif // TECPLOT_H

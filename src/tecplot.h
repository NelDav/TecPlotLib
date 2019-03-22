#ifndef TECPLOT_H
#define TECPLOT_H

#include "tecplot_global.h"

#include <QObject>
#include <QFile>

class TECPLOTSHARED_EXPORT TecPlot : public QObject
{
    Q_OBJECT

public:
    TecPlot();
    bool readFile(QFile file);

private:

};

#endif // TECPLOT_H

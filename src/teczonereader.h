#ifndef TECZONEREADER_H
#define TECZONEREADER_H

#include "teczone.h"

#include <QRunnable>

class TecZoneReader : public QRunnable
{
public:
    TecZoneReader(QString input, QStringList var);

    void run() override;

private:
    QString m_ZoneData;
    QStringList m_Vars;
    TecZone m_Zone;
};

#endif // TECZONEREADER_H

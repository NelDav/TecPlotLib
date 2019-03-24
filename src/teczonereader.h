#ifndef TECZONEREADER_H
#define TECZONEREADER_H

#include "teczone.h"

#include <QRunnable>

class TecZoneReader : QRunnable
{
public:
    TecZoneReader(QString input);

    void run() override;

private:
    QString m_ZoneData;
    TecZone m_Zone;
};

#endif // TECZONEREADER_H

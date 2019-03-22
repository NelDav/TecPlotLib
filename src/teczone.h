#ifndef TECZONE_H
#define TECZONE_H

#include <QObject>
#include <QMap>
#include <QVector>
#include <QString>
#include <QStringList>

class TecZone : public QObject
{
    Q_OBJECT

public:
    TecZone();
    bool setData(QMap<QString, QVector<double>> values);
    bool setData(QMap<QString, QVector<double>> values, int firstAxisLength);
    bool setData(QMap<QString, QVector<double>> values, int firstAxisLength, int seccondAxislength);

private:
    int m_dimension;

    QMap<QString, QVector<double>> m_1dData;
    QMap<QString, QVector<QVector<double>>> m_2dData;
    QMap<QString, QVector<QVector<QVector<double>>>> m_3dData;

    int chekForConsistence(QMap<QString, QVector<double>> input);
};

#endif // TECZONE_H

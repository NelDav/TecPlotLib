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
    Q_ENUMS(Axis)

public:
    enum Axis {I, J, K};

    TecZone();
    bool setData(QMap<QString, QVector<double>> values);
    bool setData(QMap<QString, QVector<double>> values, int firstAxisLength);
    bool setData(QMap<QString, QVector<double>> values, int firstAxisLength, int seccondAxislength);
    bool setData(QMap<QString, QVector<QVector<double>>> values);
    bool setData(QMap<QString, QVector<QVector<QVector<double>>>> values);

    /**
     * @brief To get a value of an 1D-Zone
     * @param param
     * @param iAxisPosition
     * @return value of an 1D-Zone
     */
    double data0D(QString param, int iAxisPosition); //if dimension == 1

    /**
     * @brief To get a value of an 2D-Zone
     * @param param
     * @param iAxisPosition
     * @param jAxisPosition
     * @return value of an 2D-Zone
     */
    double data0D(QString param, int iAxisPosition, int jAxisPosition); //if dimension == 2

    /**
     * @brief To get a value of an 3D-Zone
     * @param param
     * @param iAxisPosition
     * @param jAxisPosition
     * @param kAxisPosition
     * @return value of an 3D-Zone
     */
    double data0D(QString param, int iAxisPosition, int jAxisPosition, int kAxisPosition); //if dimension == 3

    /**
     * @brief Get whole 1D-Data as Vector
     * @param param
     * @return 1D-Data as Vector
     */
    QVector<double> data1D(QString param);  //if dimension == 1

    /**
     * @brief Get 1D-Data from 2D-Data as Vector
     * @param param
     * @param axisPosition
     * @param returnAxis
     * @return 1D-Data as Vector
     */
    QVector<double> data1D(QString param, int axisPosition, Axis returnAxis); //if dimension == 2

    /**
     * @brief Get 1D-Data from 3D-Data as Vector
     * @param param
     * @param firstAxisPosition = if returnAxis==I : J else I
     * @param seccondAxisPosition = if returnAxis==K : J else K
     * @param returnAxis
     * @return 1D-Data as Vector
     */
    QVector<double> data1D(QString param, int firstAxisPosition, int seccondAxisPosition, Axis returnAxis); //if dimension == 3

    /**
     * @brief Get whole 2D-Data as Vector
     * @param param
     * @return 2D-Data as Vector
     */
    QVector<QVector<double>> data2D(QString param); //if dimension == 2

    /**
     * @brief Get 2D-Slice from 3D-Data as Vector
     * @param param
     * @param axisPosition of the in returnAxis mentuned axis
     * @param returnAxis = ortegonal axis of the slice
     * @return 2D-Slice as Vector
     */
    QVector<QVector<double>> data2D(QString param, int axisPosition, Axis returnAxis); //if dimension == 3

    /**
     * @brief Get whole 3D-Data as Vector
     * @param param
     * @return 3D-Data as Vector
     */
    QVector<QVector<QVector<double>>> data3D(QString param); //dimenion = 3

    int dimension();

private:
    int m_dimension;

    QMap<QString, QVector<double>> m_1dData; //[i]
    QMap<QString, QVector<QVector<double>>> m_2dData; //[j][i]
    QMap<QString, QVector<QVector<QVector<double>>>> m_3dData; //[k][j][i]

    int checkForConsistence(QMap<QString, QVector<double>> input);
};

#endif // TECZONE_H

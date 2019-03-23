#include "teczone.h"

TecZone::TecZone() :
    m_dimension(0)
{

}

bool
TecZone::setData(QMap<QString, QVector<double>> values)
{
    //check if TecZone is alredy used
    if(m_dimension != 0)
        return false;

    //check if all vectors in values have the same length
    if (!checkForConsistence(values))
        return false;

    m_dimension = 1;

    m_1dData = values;

    return true;
}

bool
TecZone::setData(QMap<QString, QVector<double>> values, int firstAxisLength)
{
    //check if TecZone is alredy used
    if(m_dimension != 0)
        return false;

    //check if all vectors in values have the same length
    int vectorLength = checkForConsistence(values);
    if(!vectorLength)
        return false;

    //check if length of the vectors is divisible integer
    if(vectorLength / firstAxisLength != double(vectorLength) / double(firstAxisLength))
        return false;

    m_dimension = 2;

    foreach(QString param, values.keys())
    {
        QVector<double> firstAxisData;
        for(int i = 0; i < vectorLength; i++)
        {
            firstAxisData << values[param][i];

            if(firstAxisData.length() == firstAxisLength)
            {
                m_2dData[param] << firstAxisData;
                firstAxisData.clear();
            }
        }
    }

    return true;
}

bool
TecZone::setData(QMap<QString, QVector<double>> values, int firstAxisLength, int seccondAxisLength)
{
    //check if TecZone is alredy used
    if(m_dimension != 0)
        return false;

    //check if all vectors in values have the same length
    int vectorLength = checkForConsistence(values);
    if(!vectorLength)
        return false;

    //check if length of the vectors is divisible integer
    if(vectorLength / (firstAxisLength * seccondAxisLength) != double(vectorLength) / double(firstAxisLength * seccondAxisLength))
        return false;

    m_dimension = 3;

    foreach(QString param, values.keys())
    {
        QVector<double> firstAxisData;
        QVector<QVector<double>> seccondAxisData;
        for(int i = 0; i < vectorLength; i++)
        {
            firstAxisData << values[param][i];

            if(firstAxisData.length() == firstAxisLength)
            {
                seccondAxisData << firstAxisData;
                firstAxisData.clear();
            }

            if(seccondAxisData.length() == seccondAxisLength)
            {
                m_3dData[param] << seccondAxisData;
                seccondAxisData.clear();
            }
        }
    }

    return true;
}

bool
TecZone::setData(QMap<QString, QVector<QVector<double>>> values)
{
    //check if TecZone is alredy used
    if(m_dimension != 0)
        return false;

    //check if all vectors in values have the same length
/*    int vectorLength = checkForConsistence(values);
    if(!vectorLength)
        return false;*/

    m_2dData = values;

    return true;
}

bool
TecZone::setData(QMap<QString, QVector<QVector<QVector<double>>>> values)
{
    //check if TecZone is alredy used
    if(m_dimension != 0)
        return false;

/*    //check if all vectors in values have the same length
    int vectorLength = checkForConsistence(values);
    if(!vectorLength)
        return false;*/

    m_3dData = values;

    return true;
}


double
TecZone::data0D(QString param, int iAxisPosition) //if dimension == 1
{
    if(m_dimension != 1)
        return NAN;

    return m_1dData[param][iAxisPosition];
}

double
TecZone::data0D(QString param, int iAxisPosition, int jAxisPosition) //if dimension == 2
{
    if(m_dimension != 2)
        return NAN;

    return m_2dData[param][jAxisPosition][iAxisPosition];
}

double
TecZone::data0D(QString param, int iAxisPosition, int jAxisPosition, int kAxisPosition) //if dimension == 3
{
    if(m_dimension != 1)
        return NAN;

    return m_3dData[param][kAxisPosition][jAxisPosition][iAxisPosition];
}

QVector<double>
TecZone::data1D(QString param) //if dimension == 1
{
    if(m_dimension != 1)
        return QVector<double>();

    return m_1dData[param];
}

QVector<double>
TecZone::data1D(QString param, int axisPosition, Axis returnAxis) //if dimension == 2
{
    if(m_dimension != 2)
        return QVector<double>();

    if(returnAxis == Axis::I)
    {
        return m_2dData[param][axisPosition];
    }
    else
    {
        QVector<double> retval;

        foreach (QVector<double> jLine, m_2dData[param])
        {
            retval << jLine[axisPosition];
        }

        return retval;
    }
}

QVector<double>
TecZone::data1D(QString param, int firstAxisPosition, int seccondAxisPosition, Axis returnAxis) //if dimension == 3
{
    if(m_dimension != 3)
        return QVector<double>();

    if(returnAxis == Axis::I)
    {
        return m_3dData[param][seccondAxisPosition][firstAxisPosition];
    }
    else if(returnAxis == Axis::J)
    {
        QVector<double> retval;
        foreach (QVector<double> jLine, m_3dData[param][seccondAxisPosition])
        {
            retval << jLine[firstAxisPosition];
        }

        return retval;
    }
    else
    {
        QVector<double> retval;
        foreach (QVector<QVector<double>> kSlice, m_3dData[param])
        {
            retval << kSlice[seccondAxisPosition][firstAxisPosition];
        }

        return retval;
    }
}

QVector<QVector<double>> data2D(QString param); //if dimension == 2
QVector<QVector<double>> data2D(QString param, int iaxisPosition); //if dimension == 3
QVector<QVector<QVector<double>>> data3D(QString param); //dimenion = 3





int
TecZone::dimension()
{
    return m_dimension;
}

int
TecZone::checkForConsistence(QMap<QString, QVector<double>> input)
{
    int refLength = input[input.keys().first()].length();

    foreach (QString e, input.keys())
    {
        if(input[e].length() != refLength)
            return false;
    }

    return refLength;
}

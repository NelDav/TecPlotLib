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
    if (!chekForConsistence(values))
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
    int vectorLength = chekForConsistence(values);
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
    int vectorLength = chekForConsistence(values);
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

int
TecZone::chekForConsistence(QMap<QString, QVector<double>> input)
{
    int refLength = input[input.keys().first()].length();

    foreach (QString e, input.keys())
    {
        if(input[e].length() != refLength)
            return false;
    }

    return refLength;
}

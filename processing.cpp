#include "processing.h"


Processing::Processing(QObject *parent) : QObject(parent)
{

}

void Processing::fileRead(QString dataPath)
{
    QFile dataFile;
    QStringList data;

    dataFile.setFileName(dataPath);

    if(!dataFile.open(QIODevice::ReadOnly))
    {
        emit responce("file don't want to be opened");
        while(!y_Axis_Values.isEmpty())
        {
            free(y_Axis_Values.takeFirst());
        }
        y_Axis.clear();
        x_Axis.clear();
        return;
    }

    while(!dataFile.atEnd())
    {
        data.append(QString(dataFile.readLine()));
    }

    dataFile.close();
    emit progress(10);

    QList <float*> time_data;
    QStringList temporary_list;
    float *vector;
    int i;

    foreach (QString line, data)
    {
        temporary_list = line.split("\t");
        vector = (float*)calloc(3, sizeof(float));
        i = 0;

        foreach (QString temp_string, temporary_list)
        {
            *(vector+i) = temp_string.toFloat();
            i++;
        }

        time_data.append(vector);

        if(!x_Axis.contains(*vector))
        {
            x_Axis.append(*vector);
        }

        if(!y_Axis.contains(*(vector+1)))
        {
            y_Axis.append(*(vector+1));
        }

        vector = NULL;
    }

    qSort(x_Axis);
    qSort(y_Axis);

    emit progress(20);

    for(i = 0;  i<y_Axis.size(); i++)
    {
        vector = (float*)calloc(x_Axis.size(), sizeof(float));
        y_Axis_Values.append(vector);
    }

    while(!time_data.isEmpty())
    {
        vector = time_data.takeAt(0);
        *(y_Axis_Values.at(y_Axis.indexOf(*(vector+1))) + x_Axis.indexOf(*(vector))) = *(vector+2);
        free(vector);
    }
    emit progress(40);
    emit readEnded();
}

void Processing::fileWrite(QString outPath)
{
    QFile resultFile;
    QString line;
    line  = outPath + QDateTime::currentDateTime().toString("d.M.yy_h:m:s")+".txt";

    resultFile.setFileName(outPath + QDateTime::currentDateTime().toString("_d_M_yy_h_m_s")+".xls");
    if(!resultFile.open(QIODevice::WriteOnly))
    {
        emit responce("file don't want to be created");
        return;
    }


    resultFile.write("y\\x\t");
    foreach (float x, x_Axis)
    {
        line = QString::number(x);
        line.append('\t');
        resultFile.write(line.toLocal8Bit());
    }
    resultFile.write("\n");
    emit progress(50);

    int i,k,j;

    k = y_Axis.size()-1;

    if(k==0)
    {
        return;
    }
    for(i = 0; i < y_Axis.size(); i++)
    {
        line = QString::number(y_Axis.at(k - i));
        line.append('\t');
        for(j = 0; j < x_Axis.size(); j++)
        {
            line.append(QString::number(*(y_Axis_Values.at(k-i) + j)));
            line.append("\t");
        }
        line.append("\n");
        resultFile.write(line.toLocal8Bit());
    }

    resultFile.close();

    while(!y_Axis_Values.isEmpty())
    {
        free(y_Axis_Values.takeFirst());
    }
    y_Axis.clear();
    x_Axis.clear();

    emit responce("Complete");
    emit progress(100);
}

Processing::~Processing()
{
    foreach (float* value, y_Axis_Values)
    {
        free(value);
    }
}


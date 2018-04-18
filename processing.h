#ifndef PROCESSING_H
#define PROCESSING_H

#include <QObject>
#include <QFile>
#include <QDateTime>

class Processing : public QObject
{
    Q_OBJECT
private:
    QList <float*> y_Axis_Values;
    QList <float> x_Axis;
    QList <float> y_Axis;

private slots:
    void fileRead(QString dataPath);
    void fileWrite(QString outPath);


public:
    explicit Processing(QObject *parent = 0);
    ~Processing();

signals:
    void responce(QString Responce);
    void readEnded();
    void progress(int value);

public slots:
};

#endif // PROCESSING_H

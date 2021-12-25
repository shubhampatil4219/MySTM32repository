#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QtSerialPort>

class Worker : public QObject
{
    Q_OBJECT
    QSerialPort *serial;
public:
    explicit Worker(QObject *parent = nullptr);
    void delay(int millisecondsWait);
    bool stop=false;
    bool Bat1_Enter_Maintenance_Flag=false;
    bool Bat1_Start_Maint_Autotest_Flag=false;
    bool Bat1_Maint_Display_GenInfo_Flag=false;



signals:
//void dataread(int,int,int,int);   // These are the signals to update Bat1 General Info
//void voltageread(int);             // during maintenance use case at specific intervals
//void asocread(int);
//void tempread(float);
//void countread(int);
//void rcapread(int);
//void curead(int);
//void batstatusread(int);

//void entered_maint(bool);
void send_read_data_to_processing_thread(QByteArray);


public slots:
void DoWork();
void ReadDatafromSTM();
//void when_entered_maint(bool);

private:
QByteArray rx_array;


};

#endif // WORKER_H

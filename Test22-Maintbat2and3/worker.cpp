#include "worker.h"
#include <QThread>
#include <QtCore>
#include <QtSerialPort>
#include <QFloat16>

Worker::Worker(QObject *parent) : QObject(parent)
{



}

//void Worker::DoWork(){

//    serial = new QSerialPort();
//    serial->setPortName("/dev/serial0");
//    serial->open(QIODevice::ReadWrite);
//    // serial->setBaudRate(QSerialPort::Baud9600);  9600 for UART example project in STM32
//    serial->setBaudRate(QSerialPort::Baud115200);
//    serial->setParity(QSerialPort::NoParity);
//    serial->setDataBits(QSerialPort::Data8);
//    serial->setStopBits(QSerialPort::OneStop);
//    serial->setFlowControl(QSerialPort::NoFlowControl);
//    serial->setReadBufferSize(27);

//    //   connect(serial,&QSerialPort::readyRead,this,&Worker::Dataread);
//    //   connect(serial,&QSerialPort::readyRead,this,SIGNAL(readsignalemitted()));

//    char buf2[27]={0x00};
//    static qint64 var;

//    for (;;) {


//        if(this->stop==false)
//        {
//            if(Bat1_Enter_Maintenance_Flag==true)
//            {


//                QByteArray tx_Bat1_Maint("MAI");
//                serial->write(tx_Bat1_Maint);
//                Bat1_Enter_Maintenance_Flag=false;
//            }

//            if(Bat1_Maint_Display_GenInfo_Flag==true)
//            {

//                QByteArray ginfo_bat1("GIN");
//                serial->write(ginfo_bat1);
//                Bat1_Maint_Display_GenInfo_Flag=false;
//            }

//            if(Bat1_Start_Maint_Autotest_Flag==true)
//            {
//                QByteArray tx_Bat1_Maint_Autotest("B1M");
//                serial->write(tx_Bat1_Maint_Autotest);
//                Bat1_Start_Maint_Autotest_Flag=false;

//            }


//            //                        char buf2[27]={0x00};
//            //                        static qint64 w;


//            var=serial->read(buf2,27);

//            delay(15);




//            if(buf2[0]=='1' && buf2[1]=='M' && buf2[2]=='G' &&buf2[3]=='V' &&buf2[4]=='T' )
//            {
//                quint8 M=0;
//                quint8 L=0;
//                int v;
//                M=buf2[5];
//                L=buf2[6];
//                v=((M<<8)+L);
//                emit voltageread(v);

//                memset(buf2,0,sizeof (buf2));

//            }

//            if(buf2[0]=='1' && buf2[1]=='M' && buf2[2]=='G' &&buf2[3]=='A' &&buf2[4]=='S'   )
//            {
//                int a;
//                a=buf2[5];
//                emit asocread(a);
//                memset(buf2,0,sizeof (buf2));

//            }

//            if(buf2[0]=='1' && buf2[1]=='M' && buf2[2]=='G' &&buf2[3]=='T' &&buf2[4]=='P'   )
//            {
//                quint8 t1=0;
//                quint8 t2=0;
//                float t=0;
//                t1=buf2[5];
//                t2=buf2[6];
//                t=static_cast<float>(((t1<<8)+t2));
//                t=static_cast<float>(((t/10.0)-273.15));
//                emit tempread(t);
//                memset(buf2,0,sizeof (buf2));

//            }

//            if(buf2[0]=='1' && buf2[1]=='M' && buf2[2]=='G' &&buf2[3]=='R' &&buf2[4]=='C'   )
//            {
//                quint8 r1=0;
//                quint8 r2=0;
//                int r;
//                r1=buf2[5];
//                r2=buf2[6];
//                r=((r1<<8)+r2);
//                emit rcapread(r);
//                memset(buf2,0,sizeof (buf2));

//            }

//            if(buf2[0]=='1' && buf2[1]=='M' && buf2[2]=='G' &&buf2[3]=='C' &&buf2[4]=='C'   )
//            {
//                quint8 c1=0;
//                quint8 c2=0;
//                int c;
//                c1=buf2[5];
//                c2=buf2[6];
//                c=((c1<<8)+c2);
//                emit countread(c);
//                memset(buf2,0,sizeof (buf2));

//            }

//            if(buf2[0]=='1' && buf2[1]=='M' && buf2[2]=='G' &&buf2[3]=='C' &&buf2[4]=='R'   )
//            {
//                quint8 current1=0;
//                quint8 current2=0;
//                int current;
//                current1=buf2[5];
//                current2=buf2[6];
//                current=((current1<<8)+current2);
//                emit curead(current);
//                memset(buf2,0,sizeof (buf2));

//            }
//            if(buf2[0]=='1' && buf2[1]=='M' && buf2[2]=='G' &&buf2[3]=='B' &&buf2[4]=='S'   )
//            {
//                quint8 bs1=0;
//                quint8 bs2=0;
//                int bstatus;
//                bs1=buf2[5];
//                bs2=buf2[6];
//                bstatus=((bs1<<8)+bs2);
//                emit batstatusread(bstatus);
//                memset(buf2,0,sizeof (buf2));

//            }

//            if(buf2[0]=='1' && buf2[1]=='M' && buf2[2]=='G' &&buf2[3]=='I' && buf2[4]=='S'
//                    && buf2[20]=='1' && buf2[21]=='M' && buf2[22]=='G' &&buf2[23]=='I' && buf2[24]=='E')
//            {

//                quint8 sern1=buf2[5];
//                quint8 sern2=buf2[6];

//                quint8 mdd1=buf2[7];
//                quint8 mdd2=buf2[8];

//                quint8 ccc1=buf2[9];
//                quint8 ccc2=buf2[10];

//                quint8 rcc1=buf2[11];
//                quint8 rcc2=buf2[12];

//                quint8 ass=buf2[13];


//                quint8 vt1=buf2[14];
//                quint8 vt2=buf2[15];

//                quint8 temp1=buf2[16];
//                quint8 temp2=buf2[17];

//                quint8 bs1=buf2[18];
//                quint8 bs2=buf2[19];

//                int voltage,temperature,asoc,sernum,mandate,remcapac,ccount,bstatus;


//                sernum=((sern1<<8)+sern2);
//                mandate=((mdd1<<8)+mdd2);
//                ccount=((ccc1<<8)+ccc2);
//                remcapac=((rcc1<<8)+rcc2);
//                asoc=ass;
//                voltage=((vt1<<8)+vt2);
//                temperature=((temp1<<8)+temp2);
//                bstatus=((bs1<<8)+bs2);

//                emit Bat1_Maint_generalInforead(sernum,mandate,ccount,remcapac,asoc,voltage,temperature,bstatus);

//                qDebug()<<"This is battery 1 General Information\n";
//                qDebug()<<"asoc = "<<asoc;
//                qDebug()<<"Voltage = "<<voltage;
//                qDebug()<<"rem capacity = "<<remcapac;
//                qDebug()<<"Serial No = "<<sernum;
//                qDebug()<<"Cycle Count ="<<ccount ;
//                qDebug()<<"Bat Status ="<<bstatus ;
//                qDebug()<<"Temp="<<temperature;


//                memset(buf2,0,sizeof (buf2));



//                // Parameters are updated at specific intervals on GUI
//                // General Info is also displayed correctly
//                // It works


//            }

//            if(buf2[0]=='1' && buf2[1]=='M' && buf2[2]=='S' &&buf2[3]=='S' && buf2[10]=='1'
//                    && buf2[11]=='M' && buf2[12]=='S' && buf2[13]=='E')
//            {





//                quint8 dc1=buf2[6];
//                quint8 dc2=buf2[7];

//                quint8 fcc1=buf2[8];
//                quint8 fcc2=buf2[9];


//                quint8 bs1=buf2[4];
//                quint8 bs2=buf2[5];


//                int designcap, fullchargecap, bstatus;


//                designcap=((dc1<<8)+dc2);
//                fullchargecap=((fcc1<<8)+fcc2);

//                bstatus=((bs1<<8)+bs2);

//                emit Bat1_Maint_specificInforead(designcap,fullchargecap,bstatus);


//                qDebug()<<"\nThis is battery 1 Specific Information\n";

//                qDebug()<<"Design capacity = "<<designcap;
//                qDebug()<<"Full Charge Capacity = "<<fullchargecap;
//                qDebug()<<"Bat Status ="<<bstatus ;



//                memset(buf2,0,sizeof (buf2));



//            }

//            if(buf2[0]=='1' && buf2[1]=='M' && buf2[2]=='F' &&buf2[3]=='8' && buf2[4]=='0'
//                    && buf2[5]=='P' && buf2[6]=='C' && buf2[7]=='S')
//            {



//                quint8 ccc1=buf2[15];
//                quint8 ccc2=buf2[16];

//                quint8 rcc1=buf2[13];
//                quint8 rcc2=buf2[14];

//                quint8 ass=buf2[12];


//                quint8 vt1=buf2[8];
//                quint8 vt2=buf2[9];

//                quint8 temp1=buf2[10];
//                quint8 temp2=buf2[11];

//                quint8 bs1=buf2[17];
//                quint8 bs2=buf2[18];

//                int voltage,temperature,asoc,remcapac,ccount,bstatus;



//                ccount=((ccc1<<8)+ccc2);
//                remcapac=((rcc1<<8)+rcc2);
//                asoc=ass;
//                voltage=((vt1<<8)+vt2);
//                temperature=((temp1<<8)+temp2);
//                bstatus=((bs1<<8)+bs2);

//                emit bat1_maint_first80(voltage,temperature,asoc,remcapac,ccount,bstatus);

//                qDebug()<<"\n This is Result 1 - 80 %\n";
//                qDebug()<<"asoc = "<<asoc;
//                qDebug()<<"Voltage = "<<voltage;
//                qDebug()<<"rem capacity = "<<remcapac;

//                qDebug()<<"Cycle Count ="<<ccount ;
//                qDebug()<<"Bat Status ="<<bstatus ;
//                qDebug()<<"Temp="<<temperature;


//                qDebug()<<"\nFirst 80 percent received";


//                // This function works
//                // I will have to adjust some timings
//                // Maybe while transmiiting the results of autotest to gui
//                // Stop Other flags on STM side which send info to raspi


//                memset(buf2,0,sizeof (buf2));



//            }

//            if(buf2[0]=='1' && buf2[1]=='M' && buf2[2]=='M' &&buf2[3]=='1' && buf2[4]=='0'
//                    && buf2[5]=='P' && buf2[6]=='D' && buf2[7]=='S' )
//            {



//                quint8 ccc1=buf2[15];
//                quint8 ccc2=buf2[16];

//                quint8 rcc1=buf2[13];
//                quint8 rcc2=buf2[14];

//                quint8 ass=buf2[12];


//                quint8 vt1=buf2[8];
//                quint8 vt2=buf2[9];

//                quint8 temp1=buf2[10];
//                quint8 temp2=buf2[11];

//                quint8 bs1=buf2[17];
//                quint8 bs2=buf2[18];

//                int voltage,temperature,asoc,remcapac,ccount,bstatus;



//                ccount=((ccc1<<8)+ccc2);
//                remcapac=((rcc1<<8)+rcc2);
//                asoc=ass;
//                voltage=((vt1<<8)+vt2);
//                temperature=((temp1<<8)+temp2);
//                bstatus=((bs1<<8)+bs2);

//                emit bat1_maint_middle80(voltage,temperature,asoc,remcapac,ccount,bstatus);

//                qDebug()<<"\n This is Result Middle - 10 %\n";
//                qDebug()<<"asoc = "<<asoc;
//                qDebug()<<"Voltage = "<<voltage;
//                qDebug()<<"rem capacity = "<<remcapac;

//                qDebug()<<"Cycle Count ="<<ccount ;
//                qDebug()<<"Bat Status ="<<bstatus ;
//                qDebug()<<"Temp="<<temperature;


//                qDebug()<<"\n Middle  10 percent received";

//                memset(buf2,0,sizeof (buf2));

//            }


//            if(buf2[0]=='1' && buf2[1]=='M' && buf2[2]=='L' && buf2[3]=='8' && buf2[4]=='0'
//                    && buf2[5]=='P' && buf2[6]=='C' && buf2[7]=='S')
//            {

//                quint8 ccc1=buf2[15];
//                quint8 ccc2=buf2[16];

//                quint8 rcc1=buf2[13];
//                quint8 rcc2=buf2[14];

//                quint8 ass=buf2[12];


//                quint8 vt1=buf2[8];
//                quint8 vt2=buf2[9];

//                quint8 temp1=buf2[10];
//                quint8 temp2=buf2[11];

//                quint8 bs1=buf2[17];
//                quint8 bs2=buf2[18];

//                int voltage,temperature,asoc,remcapac,ccount,bstatus;



//                ccount=((ccc1<<8)+ccc2);
//                remcapac=((rcc1<<8)+rcc2);
//                asoc=ass;
//                voltage=((vt1<<8)+vt2);
//                temperature=((temp1<<8)+temp2);
//                bstatus=((bs1<<8)+bs2);

//                emit bat1_maint_last80(voltage,temperature,asoc,remcapac,ccount,bstatus);

//                qDebug()<<"\n This is Result Last - 80 %\n";
//                qDebug()<<"asoc = "<<asoc;
//                qDebug()<<"Voltage = "<<voltage;
//                qDebug()<<"rem capacity = "<<remcapac;

//                qDebug()<<"Cycle Count ="<<ccount ;
//                qDebug()<<"Bat Status ="<<bstatus ;
//                qDebug()<<"Temp="<<temperature;


//                qDebug()<<"\n Last  80 percent received";

//                memset(buf2,0,sizeof (buf2));

//            }











//        }

//        else if (this->stop==true) {
//            break;
//        }

//    }

//    serial->close();
//}

void Worker::delay(int millisecondsWait)
{
    QEventLoop loop;
    QTimer t;
    t.connect(&t, &QTimer::timeout,&loop, &QEventLoop::quit);
    t.start(millisecondsWait);
    loop.exec();
}


// This function works with SM_OPT2_New_Specs_Copy_2

void Worker::DoWork()
{
    serial = new QSerialPort();
   // serial->setPortName("/dev/serial0");
    serial->setPortName("/dev/ttyAMA1");
    serial->open(QIODevice::ReadWrite);
    // serial->setBaudRate(QSerialPort::Baud9600);  9600 for UART example project in STM32
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setParity(QSerialPort::NoParity);
    serial->setDataBits(QSerialPort::Data8);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setReadBufferSize(14);
    //serial->write("B1X");







    if(this->stop==false)
    {





       // connect(this,SIGNAL(entered_maint(bool)),this,SLOT(when_entered_maint(bool)));
        connect(serial,SIGNAL(readyRead()),this,SLOT(ReadDatafromSTM()));

    }

    else if (this->stop==true) {



        serial->close();
    }

}

void Worker::ReadDatafromSTM()


{



   if(serial->bytesAvailable()==14)
    {


if(Bat1_Enter_Maintenance_Flag==true)
{
    Bat1_Enter_Maintenance_Flag=false;
//qDebug()<<"Maintenance is true";
//serial->write("BAT1ENTERMAINT");
serial->write("BAT2ENTERMAINT");    // Data send here is received by STM32
 // serial->write("BAT3ENTERMAINT");
}


//if(Bat1_Enter_Maintenance_Flag==false)
//{
//qDebug()<<"Maintenance is false";

//}
if(Bat1_Start_Maint_Autotest_Flag==true)
{
    Bat1_Start_Maint_Autotest_Flag=false;
   //serial->write("BAT1STRMAINTST");
    serial->write("BAT2STRMAINTST");
  //  serial->write("BAT3STRMAINTST");
}
if(Bat1_Maint_Display_GenInfo_Flag==true)
{
Bat1_Maint_Display_GenInfo_Flag=false;
//serial->write("BAT1MAINDPGNIF");
serial->write("BAT2MAINDPGNIF");
//serial->write("BAT3MAINDPGNIF");

}
//QByteArray rx_array;
 //       rx_array.reserve(14);
//        rx_array.resize(14);
        //qDebug()<<"Length:"<<rx_array.length()<<"Capacity:"<<rx_array.capacity();
        //rx_array.fill('\x00');
        rx_array=serial->readAll();
        //rx_array+=serial->readAll();
      //qDebug()<<rx_array;
     // qDebug()<<"Length:"<<rx_array.length()<<"Capacity:"<<rx_array.capacity();

       emit send_read_data_to_processing_thread(rx_array); // Sends data to data_processing thread

       // serial->clear();





    }


}

//void Worker::when_entered_maint(bool xwe)
//{
//    if(xwe==true)
//    {
//qDebug()<<"Bat has entered Maintenance";
//    }
//}


// This program works properly with ReadyRead_Interrupt_Mode_Test program of STM32

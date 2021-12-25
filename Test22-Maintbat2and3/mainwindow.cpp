#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QApplication>
#include<QGraphicsEffect>
#include <QEventLoop>
#include <qeventloop.h>
#include <QTimer>
#include <qtimer.h>
#include <QtSerialPort>
#include <QSerialPort>
#include <QThread>
#include "worker.h"
#include "data_processing_thread.h"
#include <QtCore>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

//QSerialPort *serial;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    thread1 = new QThread();
    worker=new Worker();
    worker->moveToThread(thread1);

    thread2 = new QThread();
    process=new data_process();
    process->moveToThread(thread2);
    thread2->start();

   // connect(worker,SIGNAL(dataread(int,int,int,int)),this,SLOT(ondataread(int,int,int,int)));

    connect(thread1,SIGNAL(started()),worker,SLOT(DoWork()));

   connect(process,SIGNAL(send_bat1_update_voltage_maint(int)),this,SLOT(bat1_update_voltage_maint_read(int)));
    connect(process,SIGNAL(send_bat1_update_asoc_maint(int)),this,SLOT(bat1_update_asoc_maint_read(int)));

    connect(process,SIGNAL(send_bat1_update_temp_maint(float)),this,SLOT(bat1_update_temp_maint_read(float)));
    connect(process,SIGNAL(send_bat1_update_cyccount_maint(int)),this,SLOT(bat1_update_cyclecount_maint_read(int)));
    connect(process,SIGNAL(send_bat1_update_remcap_maint(int)),this,SLOT(bat1_update_remcap_maint_read(int)));
//    connect(worker,SIGNAL(curead(int)),this,SLOT(oncuread(int)));
    connect(process,SIGNAL(send_bat1_update_batstatus_maint(int)),this,SLOT(bat1_update_batstatus_maint_read(int)));




    connect(worker,SIGNAL(send_read_data_to_processing_thread(QByteArray)),process,SLOT(data_from_worker(QByteArray)));


//    connect(worker,SIGNAL(Bat1_Maint_generalInforead(int,int,int,int,int,int,int,int)),this,SLOT(onBat1_Maint_generalInforead(int,int,int,int,int,int,int,int)));
//    connect(worker,SIGNAL(Bat1_Maint_specificInforead(int,int,int)),this,SLOT(onBat1_Maint_specificInforead(int,int,int)));
//    connect(worker,SIGNAL(bat1_maint_first80(int,int,int,int,int,int)),this,SLOT(onbat1_maint_first80(int,int,int,int,int,int)));
//    connect(worker,SIGNAL(bat1_maint_middle80(int,int,int,int,int,int)),this,SLOT(onbat1_maint_middle80(int,int,int,int,int,int)));
//    connect(worker,SIGNAL(bat1_maint_last80(int,int,int,int,int,int)),this,SLOT(onbat1_maint_last80(int,int,int,int,int,int)));

    // Following are the connections when Bat1 General Info is received during Maintenance Use Case
    connect(process,SIGNAL(send_battery1_MaintGI_voltage(int)),this,SLOT(Receive_battery1_MaintGI_voltage(int)));
    connect(process,SIGNAL(send_battery1_MaintGI_serial_no(int)),this,SLOT(Receive_battery1_MaintGI_serial_no(int)));
    connect(process,SIGNAL(send_battery1_MaintGI_manuf_date(int)),this,SLOT(Receive_battery1_MaintGI_manuf_date(int)));
    connect(process,SIGNAL(send_battery1_MaintGI_cyclecount(int)),this,SLOT(Receive_battery1_MaintGI_cyclecount(int)));
    connect(process,SIGNAL(send_battery1_MaintGI_RemCap(int)),this,SLOT(Receive_battery1_MaintGI_RemCap(int)));
    connect(process,SIGNAL(send_battery1_MaintGI_asoc(int)),this,SLOT(Receive_battery1_MaintGI_asoc(int)));
    connect(process,SIGNAL(send_battery1_MaintGI_batstatus(int)),this,SLOT(Receive_battery1_MaintGI_batstatus(int)));
    connect(process,SIGNAL(send_battery1_MaintGI_temperature(float)),this,SLOT(Receive_battery1_MaintGI_temperature(float)));

     // Following are the connections when Bat1 Specific Info is received during Maintenance Use Case

    connect(process,SIGNAL(send_battery1_Maint_SpecificInfo_batstatus(int)),this,SLOT(Receive_battery1_Maint_SpecificInfo_batstatus(int)));
    connect(process,SIGNAL(send_battery1_Maint_SpecificInfo_fullchargecapacity(int)),this,SLOT(Receive_battery1_Maint_SpecificInfo_fullchargecapacity(int)));
    connect(process,SIGNAL(send_battery1_Maint_SpecificInfo_designcapacity(int)),this,SLOT(Receive_battery1_Maint_SpecificInfo_designcapacity(int)));
    connect(process,SIGNAL(send_battery1_Maint_SpecificInfo_run_time_to_empty(int)),this,SLOT(Receive_battery1_Maint_SpecificInfo_run_time_to_empty(int)));
    connect(process,SIGNAL(send_battery1_Maint_SpecificInfo_run_time_to_empty_end_of_discharge(int)),this,SLOT(Receive_battery1_Maint_SpecificInfo_run_time_to_empty_end_of_discharge(int)));

     // Following are the connections when Bat 1 results are received during Maintenance Use Case

    connect(process,SIGNAL(send_battery1_Maint_f80_voltage(int)),this,SLOT(Receive_battery1_Maint_f80_voltage(int)));
    connect(process,SIGNAL(send_battery1_Maint_f80_asoc(int)),this,SLOT(Receive_battery1_Maint_f80_asoc(int)));
    connect(process,SIGNAL(send_battery1_Maint_f80_remcap(int)),this,SLOT(Receive_battery1_Maint_f80_remcap(int)));
    connect(process,SIGNAL(send_battery1_Maint_f80_cycount(int)),this,SLOT(Receive_battery1_Maint_f80_cycount(int)));
    connect(process,SIGNAL(send_battery1_Maint_f80_batstatus(int)),this,SLOT(Receive_battery1_Maint_f80_batstatus(int)));
    connect(process,SIGNAL(send_battery1_Maint_f80_temperature(float)),this,SLOT(Receive_battery1_Maint_f80_temperature(float)));


    connect(process,SIGNAL(send_battery1_Maint_m10_voltage(int)),this,SLOT(Receive_battery1_Maint_m10_voltage(int)));
    connect(process,SIGNAL(send_battery1_Maint_m10_asoc(int)),this,SLOT(Receive_battery1_Maint_m10_asoc(int)));
    connect(process,SIGNAL(send_battery1_Maint_m10_remcap(int)),this,SLOT(Receive_battery1_Maint_m10_remcap(int)));
    connect(process,SIGNAL(send_battery1_Maint_m10_cycount(int)),this,SLOT(Receive_battery1_Maint_m10_cycount(int)));
    connect(process,SIGNAL(send_battery1_Maint_m10_batstatus(int)),this,SLOT(Receive_battery1_Maint_m10_batstatus(int)));
    connect(process,SIGNAL(send_battery1_Maint_m10_temperature(float)),this,SLOT(Receive_battery1_Maint_m10_temperature(float)));

    connect(process,SIGNAL(send_battery1_Maint_l80_voltage(int)),this,SLOT(Receive_battery1_Maint_l80_voltage(int)));
    connect(process,SIGNAL(send_battery1_Maint_l80_asoc(int)),this,SLOT(Receive_battery1_Maint_l80_asoc(int)));
    connect(process,SIGNAL(send_battery1_Maint_l80_remcap(int)),this,SLOT(Receive_battery1_Maint_l80_remcap(int)));
    connect(process,SIGNAL(send_battery1_Maint_l80_cycount(int)),this,SLOT(Receive_battery1_Maint_l80_cycount(int)));
    connect(process,SIGNAL(send_battery1_Maint_l80_batstatus(int)),this,SLOT(Receive_battery1_Maint_l80_batstatus(int)));
    connect(process,SIGNAL(send_battery1_Maint_l80_temperature(float)),this,SLOT(Receive_battery1_Maint_l80_temperature(float)));



    // Following are the connections when Bat2 General Info is received during Maintenance Use Case
    connect(process,SIGNAL(send_battery2_MaintGI_voltage(int)),this,SLOT(Receive_battery2_MaintGI_voltage(int)));
    connect(process,SIGNAL(send_battery2_MaintGI_serial_no(int)),this,SLOT(Receive_battery2_MaintGI_serial_no(int)));
    connect(process,SIGNAL(send_battery2_MaintGI_manuf_date(int)),this,SLOT(Receive_battery2_MaintGI_manuf_date(int)));
    connect(process,SIGNAL(send_battery2_MaintGI_cyclecount(int)),this,SLOT(Receive_battery2_MaintGI_cyclecount(int)));
    connect(process,SIGNAL(send_battery2_MaintGI_RemCap(int)),this,SLOT(Receive_battery2_MaintGI_RemCap(int)));
    connect(process,SIGNAL(send_battery2_MaintGI_asoc(int)),this,SLOT(Receive_battery2_MaintGI_asoc(int)));
    connect(process,SIGNAL(send_battery2_MaintGI_batstatus(int)),this,SLOT(Receive_battery2_MaintGI_batstatus(int)));
    connect(process,SIGNAL(send_battery2_MaintGI_temperature(float)),this,SLOT(Receive_battery2_MaintGI_temperature(float)));


    // Following are the connections when Bat2 Specific Info is received during Maintenance Use Case

   connect(process,SIGNAL(send_battery2_Maint_SpecificInfo_batstatus(int)),this,SLOT(Receive_battery2_Maint_SpecificInfo_batstatus(int)));
   connect(process,SIGNAL(send_battery2_Maint_SpecificInfo_fullchargecapacity(int)),this,SLOT(Receive_battery2_Maint_SpecificInfo_fullchargecapacity(int)));
   connect(process,SIGNAL(send_battery2_Maint_SpecificInfo_designcapacity(int)),this,SLOT(Receive_battery2_Maint_SpecificInfo_designcapacity(int)));
   connect(process,SIGNAL(send_battery2_Maint_SpecificInfo_run_time_to_empty(int)),this,SLOT(Receive_battery2_Maint_SpecificInfo_run_time_to_empty(int)));
   connect(process,SIGNAL(send_battery2_Maint_SpecificInfo_run_time_to_empty_end_of_discharge(int)),this,SLOT(Receive_battery2_Maint_SpecificInfo_run_time_to_empty_end_of_discharge(int)));

   // Following are the connections when Bat 2 results are received during Maintenance Use Case

  connect(process,SIGNAL(send_battery2_Maint_f80_voltage(int)),this,SLOT(Receive_battery2_Maint_f80_voltage(int)));
  connect(process,SIGNAL(send_battery2_Maint_f80_asoc(int)),this,SLOT(Receive_battery2_Maint_f80_asoc(int)));
  connect(process,SIGNAL(send_battery2_Maint_f80_remcap(int)),this,SLOT(Receive_battery2_Maint_f80_remcap(int)));
  connect(process,SIGNAL(send_battery2_Maint_f80_cycount(int)),this,SLOT(Receive_battery2_Maint_f80_cycount(int)));
  connect(process,SIGNAL(send_battery2_Maint_f80_batstatus(int)),this,SLOT(Receive_battery2_Maint_f80_batstatus(int)));
  connect(process,SIGNAL(send_battery2_Maint_f80_temperature(float)),this,SLOT(Receive_battery2_Maint_f80_temperature(float)));


  connect(process,SIGNAL(send_battery2_Maint_m10_voltage(int)),this,SLOT(Receive_battery2_Maint_m10_voltage(int)));
  connect(process,SIGNAL(send_battery2_Maint_m10_asoc(int)),this,SLOT(Receive_battery2_Maint_m10_asoc(int)));
  connect(process,SIGNAL(send_battery2_Maint_m10_remcap(int)),this,SLOT(Receive_battery2_Maint_m10_remcap(int)));
  connect(process,SIGNAL(send_battery2_Maint_m10_cycount(int)),this,SLOT(Receive_battery2_Maint_m10_cycount(int)));
  connect(process,SIGNAL(send_battery2_Maint_m10_batstatus(int)),this,SLOT(Receive_battery2_Maint_m10_batstatus(int)));
  connect(process,SIGNAL(send_battery2_Maint_m10_temperature(float)),this,SLOT(Receive_battery2_Maint_m10_temperature(float)));


  connect(process,SIGNAL(send_battery2_Maint_l80_voltage(int)),this,SLOT(Receive_battery2_Maint_l80_voltage(int)));
  connect(process,SIGNAL(send_battery2_Maint_l80_asoc(int)),this,SLOT(Receive_battery2_Maint_l80_asoc(int)));
  connect(process,SIGNAL(send_battery2_Maint_l80_remcap(int)),this,SLOT(Receive_battery2_Maint_l80_remcap(int)));
  connect(process,SIGNAL(send_battery2_Maint_l80_cycount(int)),this,SLOT(Receive_battery2_Maint_l80_cycount(int)));
  connect(process,SIGNAL(send_battery2_Maint_l80_batstatus(int)),this,SLOT(Receive_battery2_Maint_l80_batstatus(int)));
  connect(process,SIGNAL(send_battery2_Maint_l80_temperature(float)),this,SLOT(Receive_battery2_Maint_l80_temperature(float)));

  // Following are the connections when bat2 updated info is received

  connect(process,SIGNAL(send_bat2_update_voltage_maint(int)),this,SLOT(bat2_update_voltage_maint_read(int)));
   connect(process,SIGNAL(send_bat2_update_asoc_maint(int)),this,SLOT(bat2_update_asoc_maint_read(int)));
   connect(process,SIGNAL(send_bat2_update_temp_maint(float)),this,SLOT(bat2_update_temp_maint_read(float)));
   connect(process,SIGNAL(send_bat2_update_cyccount_maint(int)),this,SLOT(bat2_update_cyclecount_maint_read(int)));
   connect(process,SIGNAL(send_bat2_update_remcap_maint(int)),this,SLOT(bat2_update_remcap_maint_read(int)));
   connect(process,SIGNAL(send_bat2_update_batstatus_maint(int)),this,SLOT(bat2_update_batstatus_maint_read(int)));


    // QPushButton *ptr = ui->pushButton_1;
    // QObject::connect(ptr,SIGNAL(clicked()),this,SLOT(on_pushButton_1_clicked()));

    //ui->label_10->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:1 rgba(0, 159, 0, 255));");

    //    serial = new QSerialPort();
    //    serial->setPortName("/dev/serial0");
    //    serial->setBaudRate(QSerialPort::Baud9600);
    //    serial->setParity(QSerialPort::NoParity);
    //    serial->setStopBits(QSerialPort::OneStop);
    //    serial->setFlowControl(QSerialPort::NoFlowControl);
    //    serial->setReadBufferSize(2);
    //    serial->open(QIODevice::ReadWrite);



   //  ui->Bat1_Maint_GI_BS->setText(QString::number(m)+"\n"+QString::number(23)+"\n"+QString::number(u));
//     ui->Bat1_Maint_GI_BS->setText("Bat is in good condition\n It is okaz");

 Interpret_specific_Info_maint_bat1=(int*)calloc(2,sizeof (int));





}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::delay(int millisecondsWait)
{
    QEventLoop loop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
    t.start(millisecondsWait);
    loop.exec();
}


void MainWindow::on_close_btn_clicked()
{
    MainWindow::close();
}

void MainWindow::on_pushButton_clicked()
{
    MainWindow::showMaximized();
}

void MainWindow::on_minimize_btn_clicked()
{
    MainWindow::showMinimized();

}




void MainWindow::on_left_toggle_menu_btn_clicked()
{

    //   int width=5;
    //    animation=new QPropertyAnimation(ui->left_menu,"minimumWidth");
    //    animation->setDuration(400);
    //    animation->setStartValue(55);
    //    animation->setEndValue(width);
    //    animation->start();

    int maxwidth=200;

    int wi=ui->left_menu->width();
    if(wi==65){
        animation=new QPropertyAnimation(ui->left_menu,"minimumWidth");
        animation->setDuration(400);
        animation->setStartValue(65);
        animation->setEndValue(maxwidth);
        animation->start();

    }
    else {
        animation=new QPropertyAnimation(ui->left_menu,"minimumWidth");
        animation->setDuration(400);
        animation->setStartValue(65);
        animation->setEndValue(65);
        animation->start();
    }




}





void MainWindow::on_pushButton_1_clicked()
{

    ui->stackedWidget->setCurrentIndex(1);
}






void MainWindow::on_pushButton_8_clicked()
{

    if(ui->pushButton_8->isChecked()){
        ui->stackedWidget_2->setCurrentIndex(0);
        ui->pushButton_9->setChecked(false);
        ui->pushButton_10->setChecked(false);
        worker->stop=false;
        thread1->start();


        //     serial->open(QIODevice::ReadWrite);

        //     serial->setReadBufferSize(3);

        //     serial->write("1");
        //     delay(500);
        //     quint8 LSB=0;
        //     quint8 MSB=0;
        //     quint8 ss=0;
        //     int val;
        //     char buf[3]={0x00};
        //     static qint64 in;
        //     if(serial->bytesAvailable()){
        //     in=serial->read(buf, 3);
        //     MSB=buf[0];
        //     LSB=buf[1];
        //     ss=buf[2];
        //     val=((MSB<<8)+LSB);
        //     qDebug()<<MSB;
        //     qDebug()<<LSB;
        //     qDebug()<<ss;
        //     qDebug()<<val;


        ////     ui->label_11->setText(QString::number(val));
        ////      ui->label_3->setText(QString::number(ss));


        //      delay(500);
    }
    else {

        worker->stop=true;

        thread1->exit();
        ui->Voltage_value->setText("Not Selected");
        ui->Current_value->setText("");

        ui->ASOC_value->setText("");
        // ui->label_2->setText("Error: Bytes not available");


    }
    //      serial->clear();
    //      serial->close();

}






void MainWindow::on_pushButton_10_clicked()
{
    if(ui->pushButton_10->isChecked()){
        ui->stackedWidget_2->setCurrentIndex(1);
        ui->pushButton_8->setChecked(false);
        ui->pushButton_9->setChecked(false);
    }


}

void MainWindow::on_pushButton_0_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_9_clicked()
{
    if(ui->pushButton_9->isChecked()){
        ui->pushButton_8->setChecked(false);
        ui->pushButton_10->setChecked(false);
        ui->stackedWidget_2->setCurrentIndex(2);
    }
    else{
        //  ui->stackedWidget_2->setCurrentIndex(0);
    }

}



// Following are the slots when Bat1 Update Info is received during Maintenance Use Case

void MainWindow::bat1_update_voltage_maint_read(int volt)
{
    ui->Bat1_Maint_GI_Volt->setText(QString::number(volt));
}

void MainWindow::bat1_update_asoc_maint_read(int asoc)
{
        ui->Bat1_Maint_GI_ASOC->setText(QString::number(asoc));
         ui->progressBar->setValue(asoc);
}


void MainWindow::bat1_update_temp_maint_read(float temp)
{
ui->Bat1_Maint_GI_Temp->setText(QString::number(temp));
}

void MainWindow::bat1_update_remcap_maint_read(int rcap)
{
ui->Bat1_Maint_GI_RC->setText(QString::number(rcap));
}

void MainWindow::bat1_update_cyclecount_maint_read(int count)
{
ui->Bat1_Maint_GI_CC->setText(QString::number(count));
}

//void MainWindow::oncuread(int current)
//{
//ui->Current_value->setText(QString::number(current));
//}

void MainWindow::bat1_update_batstatus_maint_read(int bat_status)
{
//ui->Bat1_Maint_GI_BS_bit15to11->setText(QString::number(bat_status));
//qDebug()<< "Entered BS function";
//qDebug()<<bat_status;   // Works properly

uint8_t batterystatusarray_update[16];
if(0<= bat_status && bat_status<=65535)
{
    for (int j=0;j<16;j++) {
        if(bat_status % 2 == 0)
        {
            batterystatusarray_update[j]=0;
        }
        else {
            batterystatusarray_update[j]=1;
        }
        bat_status = bat_status / 2;
    }
}

if(batterystatusarray_update[15]==1)
{
    ui->Bat1_Maint_GI_BS_bit15to11->setText("Overcharged Alarm detected");
}
if(batterystatusarray_update[14]==1)
{
    ui->Bat1_Maint_GI_BS_bit15to11->setText("Terminate charge Alarm detected");
}
if(batterystatusarray_update[12]==1)
{
    ui->Bat1_Maint_GI_BS_bit15to11->setText("Overtemperature Alarm detected");
}
if(batterystatusarray_update[11]==1)
{
    ui->Bat1_Maint_GI_BS_bit15to11->setText("Terminate discharge Alarm detected");
}

if(batterystatusarray_update[6]==1)
{
    ui->Bat1_Maint_GI_BS_bit6->setText("Battery is in Discharge /Relax mode");
}
if(batterystatusarray_update[6]==0)
{
    ui->Bat1_Maint_GI_BS_bit6->setText("Battery is in charge mode");
  //  qDebug()<<"Entered charging mode";
}

if(batterystatusarray_update[7]==1)
{
    ui->Bat1_Maint_GI_BS_bit7->setText("Gauge Initialization is complete");
}
if(batterystatusarray_update[7]==0)
{
    ui->Bat1_Maint_GI_BS_bit7->setText("Gauge Initialization is in process");
}
if(batterystatusarray_update[15]==0 || batterystatusarray_update[14]==0  || batterystatusarray_update[12]==0
        || batterystatusarray_update[11]==0 )
{
    ui->Bat1_Maint_GI_BS_bit15to11->setText("No alarm detected\nBattery is in good condition");
}
}


void MainWindow::on_pushButton_Maintenance_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_Bat1EnterMaint_button_clicked()
{
    if(ui->Bat1EnterMaint_button->isChecked()){
worker->Bat1_Enter_Maintenance_Flag=true;

    }

    if(ui->Bat1EnterMaint_button->isChecked()==false){
worker->Bat1_Enter_Maintenance_Flag=false;

    }

}

void MainWindow::on_Bat1_Star_Auto_Test_Button_clicked()
{
    if(ui->Bat1_Star_Auto_Test_Button->isChecked())
    {
    worker->Bat1_Start_Maint_Autotest_Flag=true;
    }
}

void MainWindow::on_Bat1_Maint_GI_Button_clicked()
{
    worker->Bat1_Maint_Display_GenInfo_Flag=true;

}






void MainWindow::on_Bat1_Maint_See_Autotestresults_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_maint_bat1_BacktoMaint_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}



 // Following are the slots when Bat1 GI is received during Maintenance Use Case

void MainWindow::Receive_battery1_MaintGI_serial_no(int serialno)
{
    QFile file("Mylogfile.txt"); //

    if(!file.open(QFile::WriteOnly | QFile::Text ))
    {
        //QMessageBox::warning(this,"title","file not open");
    }

    QTextStream stream(&file);
  //  stream<<"\t\t\t\t\t\tLog File\n\n";
    stream<<"\t\t\t\t\t\t BATTERY 1 MAINTENANCE USE CASE REPORT \n";
    stream<<"->Battery 1 Maintenance Use Case general info\n\n";
    stream<<"Serial No:"<<QString::number(serialno)<<"\n";
    stream<<"Manufacturer Name: LS Telcom AG \n";
    file.flush();
    file.close();


ui->Bat1_Maint_GI_SN->setText(QString::number(serialno));

ui->Bat1_Maint_GI_MN->setText("LS Telcom AG");
}

void MainWindow::Receive_battery1_MaintGI_manuf_date(int mandate)
{

uint16_t date = 0x001F & mandate;
uint16_t month = 0x01E0 & mandate;
month = month >> 5;
uint16_t year = 0xFE00 & mandate;
year = year>>9;
year=year+1980;

ui->Bat1_Maint_GI_MD->setText(QString::number(date)+"."+QString::number(month)+"."+QString::number(year));

}

void MainWindow::Receive_battery1_MaintGI_cyclecount(int ccount)
{

ui->Bat1_Maint_GI_CC->setText(QString::number(ccount));



QFile file("Mylogfile.txt");
file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
QTextStream stream(&file);
stream<<"Cycle Count:"<<QString::number(ccount)<<" cycles\n";
file.flush();
file.close();

}

void MainWindow::Receive_battery1_MaintGI_RemCap(int remcap)
{
    ui->Bat1_Maint_GI_RC->setText(QString::number(remcap));
    QFile file("Mylogfile.txt");
    file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
    QTextStream stream(&file);
    stream<<"Remaining Capacity:"<<QString::number(remcap)<<" mAh \n";
    file.flush();
    file.close();
}

void MainWindow::Receive_battery1_MaintGI_asoc(int asoc)
{
    ui->Bat1_Maint_GI_ASOC->setText(QString::number(asoc));
    QFile file("Mylogfile.txt");
    file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
    QTextStream stream(&file);
    stream<<"Absolute State of Charge:"<<QString::number(asoc)<<" % \n";
    file.flush();
    file.close();
}



void MainWindow::Receive_battery1_MaintGI_voltage(int voltage)
{
ui->Bat1_Maint_GI_Volt->setText(QString::number(voltage));
QFile file("Mylogfile.txt");
file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
QTextStream stream(&file);
stream<<"Voltage:"<<QString::number(voltage)<<" mV \n";
file.flush();
file.close();

}

void MainWindow::Receive_battery1_MaintGI_batstatus(int bat_status)
{

    uint8_t batterystatusarray_update[16];
    QFile file("Mylogfile.txt");
    file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
    QTextStream stream(&file);
    stream<<"Battery Status:\n";

    if(0<= bat_status && bat_status<=65535)
    {
        for (int j=0;j<16;j++) {
            if(bat_status % 2 == 0)
            {
                batterystatusarray_update[j]=0;
            }
            else {
                batterystatusarray_update[j]=1;
            }
            bat_status = bat_status / 2;
        }
    }

    if(batterystatusarray_update[15]==1)
    {
        ui->Bat1_Maint_GI_BS_bit15to11->setText("Overcharged Alarm detected");
    }
    if(batterystatusarray_update[14]==1)
    {
        ui->Bat1_Maint_GI_BS_bit15to11->setText("Terminate charge Alarm detected");
    }
    if(batterystatusarray_update[12]==1)
    {
        ui->Bat1_Maint_GI_BS_bit15to11->setText("Overtemperature Alarm detected");
    }
    if(batterystatusarray_update[11]==1)
    {
        ui->Bat1_Maint_GI_BS_bit15to11->setText("Terminate discharge Alarm detected");
    }

    if(batterystatusarray_update[6]==1)
    {
        ui->Bat1_Maint_GI_BS_bit6->setText("Battery is in Discharge /Relax mode");
        stream<<"Battery is in Discharge /Relax mode\n";
    }
    if(batterystatusarray_update[6]==0)
    {
        ui->Bat1_Maint_GI_BS_bit6->setText("Battery is in charge mode");
      //  qDebug()<<"Entered charging mode";

    }

    if(batterystatusarray_update[7]==1)
    {
        ui->Bat1_Maint_GI_BS_bit7->setText("Gauge Initialization is complete");
        stream<<"Gauge Initialization is complete\n";
    }
    if(batterystatusarray_update[7]==0)
    {
        ui->Bat1_Maint_GI_BS_bit7->setText("Gauge Initialization is in process");
    }
    if(batterystatusarray_update[15]==0 || batterystatusarray_update[14]==0  || batterystatusarray_update[12]==0
            || batterystatusarray_update[11]==0 )
    {
        ui->Bat1_Maint_GI_BS_bit15to11->setText("No alarm detected\nBattery is in good condition");
        stream<<"No alarm Detected\n\n";
    }

    file.flush();
    file.close();

}

void MainWindow::Receive_battery1_MaintGI_temperature(float temp)
{
float temperature =static_cast<float>(((temp/10.0)-273.15));
ui->Bat1_Maint_GI_Temp->setText(QString::number(temperature));
QFile file("Mylogfile.txt");
file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
QTextStream stream(&file);
stream<<"Temperature:"<<QString::number(temperature)<<" C \n";
file.flush();
file.close();
}


// Following are the slots when Bat1 Specific Info is received during Maintenance Use Case

void MainWindow::Receive_battery1_Maint_SpecificInfo_batstatus(int bat_status)
{

    uint8_t batterystatusarray_update[16];
    QFile file("Mylogfile.txt");
    file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
    QTextStream stream(&file);
    stream<<"->Battery 1 Maintenance Use Case Specific Info\n\n";
    stream<<"Battery Status: \n";
    if(0<= bat_status && bat_status<=65535)
    {
        for (int j=0;j<16;j++) {
            if(bat_status % 2 == 0)
            {
                batterystatusarray_update[j]=0;
            }
            else {
                batterystatusarray_update[j]=1;
            }
            bat_status = bat_status / 2;
        }
    }

    if(batterystatusarray_update[15]==1)
    {
        ui->Bat1_Maint_SPCI_BS_bit11to15->setText("Overcharged Alarm detected");
    }
    if(batterystatusarray_update[14]==1)
    {
        ui->Bat1_Maint_SPCI_BS_bit11to15->setText("Terminate charge Alarm detected");
    }
    if(batterystatusarray_update[12]==1)
    {
        ui->Bat1_Maint_SPCI_BS_bit11to15->setText("Overtemperature Alarm detected");
    }
    if(batterystatusarray_update[11]==1)
    {
        ui->Bat1_Maint_SPCI_BS_bit11to15->setText("Terminate discharge Alarm detected");
    }

    if(batterystatusarray_update[6]==1)
    {
        ui->Bat1_Maint_SPCI_BS_bit6->setText("Battery is in Discharge /Relax mode");
        stream<<"Battery is in Discharge /Relax mode\n";
    }
    if(batterystatusarray_update[6]==0)
    {
        ui->Bat1_Maint_SPCI_BS_bit6->setText("Battery is in charge mode");
      //  qDebug()<<"Entered charging mode";
    }

    if(batterystatusarray_update[7]==1)
    {
        ui->Bat1_Maint_SPCI_BS_bit7->setText("Gauge Initialization is complete");
        stream<<"Gauge Initialization is complete\n";
    }
    if(batterystatusarray_update[7]==0)
    {
        ui->Bat1_Maint_SPCI_BS_bit7->setText("Gauge Initialization is in process");
    }
    if(batterystatusarray_update[15]==0 || batterystatusarray_update[14]==0  || batterystatusarray_update[12]==0
            || batterystatusarray_update[11]==0 )
    {
        ui->Bat1_Maint_SPCI_BS_bit11to15->setText("No alarm detected");
        stream<<"No alarm detected";
    }

qDebug()<<"Entered bat1 specific info in Main Thread"<<bat_status; // Works
file.flush();
file.close();
}

void MainWindow::Receive_battery1_Maint_SpecificInfo_fullchargecapacity(int fullchargecap)
{
    ui->Bat1_Maint_SPCI_FCC->setText(QString::number(fullchargecap));

    // Allocated dynamically for interpretation
    Interpret_specific_Info_maint_bat1[0]=fullchargecap;
    qDebug()<<"This is pointer fcc"<<Interpret_specific_Info_maint_bat1[0];

    QFile file("Mylogfile.txt");
    file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
    QTextStream stream(&file);
    stream<<"\n\nFull Charge Capacity:"<<QString::number(fullchargecap)<<" mAh \n";
    file.flush();
    file.close();
}

void MainWindow::Receive_battery1_Maint_SpecificInfo_designcapacity(int designcap)
{
    ui->Bat1_Maint_SPCI_DC->setText(QString::number(designcap));

    // Allocated dynamically for interpretation
    Interpret_specific_Info_maint_bat1[1]=designcap;
    qDebug()<<"This is pointer dc"<<Interpret_specific_Info_maint_bat1[1];
    int fcc=Interpret_specific_Info_maint_bat1[0];
    int dc=Interpret_specific_Info_maint_bat1[1];
    if(fcc>4620 && fcc<dc)
    {

        ui->Interpret_bat1_maint_spci->setText("Full charge capacity is whithin specified\n"
                                               "range : 4620-6600 mAh"
                                               "\nBattery's health is good and could be used for respective application");
//

    }
    if(fcc<4620)
    {

        ui->Interpret_bat1_maint_spci->setText("Battery Capacity has deteriorated\n"
                                               "The battery should be replaced"
                                               "\nIf FCC goes below 4620, then Lithium ions would \ncombine"
                                                " with the electrode and it would be difficult to \nrecover them,"
                                                "This reduces the battery capacity");

    }
    QFile file("Mylogfile.txt");
    file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
    QTextStream stream(&file);
    stream<<"Design Capacity:"<<QString::number(designcap)<<" mAh \n";
    file.flush();
    file.close();
    free(Interpret_specific_Info_maint_bat1);  // Specific Info pointer is cleared
}

void MainWindow::Receive_battery1_Maint_SpecificInfo_run_time_to_empty(int rte)
{



qDebug()<<"RTE mainwindow specific info received="<<QString::number(rte);
ui->Bat_Maint_SPCI_RTE_10S->setText(QString::number(rte));// Works

Interpret_b1m_rte[0]=rte;
QFile file("Mylogfile.txt");
file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
QTextStream stream(&file);
stream<<"\n\n Specific Info - Run Time to Empty \n";
stream<<"RTE 10 % discharge start :";
stream<<QString::number(rte);
stream<<" min";
file.flush();
file.close();


}

void MainWindow::Receive_battery1_Maint_SpecificInfo_run_time_to_empty_end_of_discharge(int rte)
{


    ui->Bat_Maint_SPCI_RTE_10E->setText(QString::number(rte));

    Interpret_b1m_rte[1]=rte;

    Battery1_Maint_Specific_Info_Interpret_RTE();

    QFile file("Mylogfile.txt");
    file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
    QTextStream stream(&file);

    stream<<"\nRTE 10 % discharge end :";
    stream<<QString::number(rte);
    stream<<" min";
    file.flush();
    file.close();
}


void MainWindow::Battery1_Maint_Specific_Info_Interpret_RTE()
{
    int rte1,rte2;
    rte1=Interpret_b1m_rte[0];
    rte2=Interpret_b1m_rte[1];

    if(rte1>rte2)
    {
    ui->Interpret_bat1_maint_spci_RTE->setText("Run time to empty gives how long the battery will last "
                                               "under a given load."
                                               "\nThis parameter decreases as we discharge the battery"
                                               "\nRTE was "+QString::number(rte1)+" min at the when battery"
                                                " discharging was started. "
                                                "\nIt decreased to "+QString::number(rte2)+" min by the end of discharge cycle");
    }
}


// Following are the slots when Bat1 Maintenance Use Case results are received


// Results bat 1 Maint charged to 80 %
void MainWindow::Receive_battery1_Maint_f80_voltage(int voltage)
{
    ui->bat1_maint_result_f80_vt->setText(QString::number(voltage));
    QFile file("Mylogfile.txt");
    file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
    QTextStream stream(&file);

    stream<<QString::number(voltage)<<",";
    file.flush();
    file.close();

    Interpret_b1m_result_f80[3]=voltage;
   // qDebug()<< "f80 pos 3 voltage"<<Interpret_b1m_result_f80[3];


}
void MainWindow:: Receive_battery1_Maint_f80_asoc(int asoc)
{
 ui->bat1_maint_result_f80_asoc->setText(QString::number(asoc));


 QFile file("Mylogfile.txt");
 file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
 QTextStream stream(&file);

 stream<<QString::number(asoc)<<",";
 file.flush();
 file.close();

 Interpret_b1m_result_f80[2]=asoc;
// qDebug()<< "f80 pos 2 asoc"<<Interpret_b1m_result_f80[2];

}
void MainWindow:: Receive_battery1_Maint_f80_remcap(int remcap)
{
   ui->bat1_maint_result_f80_remcap->setText(QString::number(remcap));
   QFile file("Mylogfile.txt");
   file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
   QTextStream stream(&file);

   stream<<QString::number(remcap)<<",";
   file.flush();
   file.close();

   Interpret_b1m_result_f80[1]=remcap;
  // qDebug()<< "f80 pos 1 remcap"<<Interpret_b1m_result_f80[1];
}
void MainWindow:: Receive_battery1_Maint_f80_cycount(int cyclecount)
{
   ui->bat1_maint_result_f80_cyclecount->setText(QString::number(cyclecount));
   QFile file("Mylogfile.txt");
   file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
   QTextStream stream(&file);
   stream<<"\n->Battery 1 Maintenance Use case Test Results\n";
   stream<<"CycleCount, RemainingCapacity, ASOC, Voltage,Temperature, Battery Status\n";
   stream<<"Battery Charged to 80%\n";
   stream<<QString::number(cyclecount)<<",";
   file.flush();
   file.close();


   Interpret_b1m_result_f80[0]=cyclecount;
   //qDebug()<< "f80 pos 0 cyc"<<Interpret_b1m_result_f80[0];



}
void MainWindow:: Receive_battery1_Maint_f80_batstatus(int batstatus)
{
    uint8_t batterystatusarray[16];

    Interpret_b1m_result_f80[4]=batstatus;
   // qDebug()<< "f80 pos 4 batstatus"<<Interpret_b1m_result_f80[4];



    QFile file("Mylogfile.txt");
    file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
    QTextStream stream(&file);

    stream<<QString::number(batstatus)<<",";
    file.flush();
    file.close();

    if(0<= batstatus && batstatus<=65535)
    {
        for (int j=0;j<16;j++) {
            if(batstatus % 2 == 0)
            {
                batterystatusarray[j]=0;
            }
            else {
                batterystatusarray[j]=1;
            }
            batstatus = batstatus / 2;
        }
    }

    if(batterystatusarray[15]==1)
    {
        ui->bat1_maint_result_f80_bs_bit11to15->setText("Overcharged Alarm detected");
    }
    if(batterystatusarray[14]==1)
    {
        ui->bat1_maint_result_f80_bs_bit11to15->setText("Terminate charge Alarm detected");
    }
    if(batterystatusarray[12]==1)
    {
        ui->bat1_maint_result_f80_bs_bit11to15->setText("Overtemperature Alarm detected");
    }
    if(batterystatusarray[11]==1)
    {
        ui->bat1_maint_result_f80_bs_bit11to15->setText("Terminate discharge Alarm detected");
    }

    if(batterystatusarray[6]==1)
    {
        ui->bat1_maint_result_f80_bs_bit6->setText("Battery is in Discharge /Relax mode");
    }
    if(batterystatusarray[6]==0)
    {
        ui->bat1_maint_result_f80_bs_bit6->setText("Battery is in charge mode");

    }

    if(batterystatusarray[7]==1)
    {
        ui->bat1_maint_result_f80_bs_bit7->setText("Gauge Initialization is complete");
    }
    if(batterystatusarray[7]==0)
    {
        ui->bat1_maint_result_f80_bs_bit7->setText("Gauge Initialization is in process");
    }
    if(batterystatusarray[15]==0 || batterystatusarray[14]==0  || batterystatusarray[12]==0
            || batterystatusarray[11]==0 )
    {
        ui->bat1_maint_result_f80_bs_bit11to15->setText("No alarm detected");
    }

  //  free(Interpret_b1m_result_f80);

}
void MainWindow::Receive_battery1_Maint_f80_temperature(float temp)
{
        float temperature =static_cast<float>(((temp/10.0)-273.15));
    ui->bat1_maint_result_f80_temp->setText(QString::number(temperature));
    QFile file("Mylogfile.txt");
    file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
    QTextStream stream(&file);

    stream<<QString::number(temperature)<<",";
    file.flush();
    file.close();

    Interpret_b1m_temperature[0]=temperature;


}

// Results bat 1 Maint discharged to 10 %
void MainWindow::Receive_battery1_Maint_m10_voltage(int voltage)
{
        ui->bat1_maint_result_m80_vt->setText(QString::number(voltage));
        QFile file("Mylogfile.txt");
        file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
        QTextStream stream(&file);

        stream<<QString::number(voltage)<<",";
        file.flush();
        file.close();

        Interpret_b1m_result_m10[3]=voltage;

}
void MainWindow::Receive_battery1_Maint_m10_asoc(int asoc)
{
    ui->bat1_maint_result_m80_asoc->setText(QString::number(asoc));
    QFile file("Mylogfile.txt");
    file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
    QTextStream stream(&file);

    stream<<QString::number(asoc)<<",";
    file.flush();
    file.close();

    Interpret_b1m_result_m10[2]=asoc;
}
void MainWindow::Receive_battery1_Maint_m10_remcap(int remcap)
{
    ui->bat1_maint_result_m80_remcap->setText(QString::number(remcap));
    QFile file("Mylogfile.txt");
    file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
    QTextStream stream(&file);

    stream<<QString::number(remcap)<<",";
    file.flush();
    file.close();

    Interpret_b1m_result_m10[1]=remcap;
}
void MainWindow::Receive_battery1_Maint_m10_cycount(int cycount)
{
    ui->bat1_maint_result_m80_cyclecount->setText(QString::number(cycount));
    QFile file("Mylogfile.txt");
    file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
    QTextStream stream(&file);
    stream<<"\n\nBattery Discharged to 10%\n";
    stream<<QString::number(cycount)<<",";
    file.flush();
    file.close();
    Interpret_b1m_result_m10[0]=cycount;
}

void MainWindow::Receive_battery1_Maint_m10_batstatus(int batstatus)
{
        uint8_t batterystatusarray[16];

        Interpret_b1m_result_m10[4]=batstatus;

        QFile file("Mylogfile.txt");
        file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
        QTextStream stream(&file);

        stream<<QString::number(batstatus)<<",";
        file.flush();
        file.close();
        if(0<= batstatus && batstatus<=65535)
        {
            for (int j=0;j<16;j++) {
                if(batstatus % 2 == 0)
                {
                    batterystatusarray[j]=0;
                }
                else {
                    batterystatusarray[j]=1;
                }
                batstatus = batstatus / 2;
            }
        }

        if(batterystatusarray[15]==1)
        {
            ui->bat1_maint_result_m80_bs_bit11to15->setText("Overcharged Alarm detected");
        }
        if(batterystatusarray[14]==1)
        {
            ui->bat1_maint_result_m80_bs_bit11to15->setText("Terminate charge Alarm detected");
        }
        if(batterystatusarray[12]==1)
        {
            ui->bat1_maint_result_m80_bs_bit11to15->setText("Overtemperature Alarm detected");
        }
        if(batterystatusarray[11]==1)
        {
            ui->bat1_maint_result_m80_bs_bit11to15->setText("Terminate discharge Alarm detected");
        }

        if(batterystatusarray[6]==1)
        {
            ui->bat1_maint_result_m80_bs_bit6->setText("Battery is in Discharge /Relax mode");
        }
        if(batterystatusarray[6]==0)
        {
            ui->bat1_maint_result_m80_bs_bit6->setText("Battery is in charge mode");

        }

        if(batterystatusarray[7]==1)
        {
            ui->bat1_maint_result_m80_bs_bit7->setText("Gauge Initialization is complete");
        }
        if(batterystatusarray[7]==0)
        {
            ui->bat1_maint_result_m80_bs_bit7->setText("Gauge Initialization is in process");
        }
        if(batterystatusarray[15]==0 || batterystatusarray[14]==0  || batterystatusarray[12]==0
                || batterystatusarray[11]==0 )
        {
            ui->bat1_maint_result_m80_bs_bit11to15->setText("No alarm detected");
        }



}
void MainWindow::Receive_battery1_Maint_m10_temperature(float temp)
{
    float temperature =static_cast<float>(((temp/10.0)-273.15));
    ui->bat1_maint_result_m80_temp->setText(QString::number(temperature));
    QFile file("Mylogfile.txt");
    file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
    QTextStream stream(&file);

    stream<<QString::number(temperature)<<",";
    file.flush();
    file.close();

    Interpret_b1m_temperature[1]=temperature;

}

// Results bat 1 Maint Recharged to 80 %

void MainWindow::Receive_battery1_Maint_l80_voltage(int voltage)
{

       ui->bat1_maint_result_l80_vt->setText(QString::number(voltage));
       QFile file("Mylogfile.txt");
       file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
       QTextStream stream(&file);

       stream<<QString::number(voltage)<<",";
       file.flush();
       file.close();


       Interpret_b1m_result_l80[3]=voltage;


}
void MainWindow::Receive_battery1_Maint_l80_asoc(int asoc)
{
     ui->bat1_maint_result_l80_asoc->setText(QString::number(asoc));
     QFile file("Mylogfile.txt");
     file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
     QTextStream stream(&file);

     stream<<QString::number(asoc)<<",";
     file.flush();
     file.close();

     Interpret_b1m_result_l80[2]=asoc;

}
void MainWindow::Receive_battery1_Maint_l80_remcap(int remcap)
{
     ui->bat1_maint_result_l80_rempcap->setText(QString::number(remcap));
     QFile file("Mylogfile.txt");
     file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
     QTextStream stream(&file);

     stream<<QString::number(remcap)<<",";
     file.flush();
     file.close();

     Interpret_b1m_result_l80[1]=remcap;
}
void MainWindow::Receive_battery1_Maint_l80_cycount(int cycount)
{
   ui->bat1_maint_result_l80_cyclecount->setText(QString::number(cycount));
   QFile file("Mylogfile.txt");
   file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
   QTextStream stream(&file);

   stream<<"\n\nBattery Recharged to 80%\n";
   stream<<QString::number(cycount)<<",";
   file.flush();
   file.close();

   Interpret_b1m_result_l80[0]=cycount;

}
void MainWindow::Receive_battery1_Maint_l80_batstatus(int batstatus)
{
        uint8_t batterystatusarray[16];

        Interpret_b1m_result_l80[4]=batstatus;

        QFile file("Mylogfile.txt");
        file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
        QTextStream stream(&file);

        stream<<QString::number(batstatus)<<",";
        file.flush();
        file.close();
        if(0<= batstatus && batstatus<=65535)
        {
            for (int j=0;j<16;j++) {
                if(batstatus % 2 == 0)
                {
                    batterystatusarray[j]=0;
                }
                else {
                    batterystatusarray[j]=1;
                }
                batstatus = batstatus / 2;
            }
        }

        if(batterystatusarray[15]==1)
        {
            ui->bat1_maint_result_l80_bs_bit11to15->setText("Overcharged Alarm detected");
        }
        if(batterystatusarray[14]==1)
        {
            ui->bat1_maint_result_l80_bs_bit11to15->setText("Terminate charge Alarm detected");
        }
        if(batterystatusarray[12]==1)
        {
            ui->bat1_maint_result_l80_bs_bit11to15->setText("Overtemperature Alarm detected");
        }
        if(batterystatusarray[11]==1)
        {
            ui->bat1_maint_result_l80_bs_bit11to15->setText("Terminate discharge Alarm detected");
        }

        if(batterystatusarray[6]==1)
        {
            ui->bat1_maint_result_l80_bs_bit6->setText("Battery is in Discharge /Relax mode");
        }
        if(batterystatusarray[6]==0)
        {
            ui->bat1_maint_result_l80_bs_bit6->setText("Battery is in charge mode");

        }

        if(batterystatusarray[7]==1)
        {
            ui->bat1_maint_result_l80_bs_bit7->setText("Gauge Initialization is complete");
        }
        if(batterystatusarray[7]==0)
        {
            ui->bat1_maint_result_l80_bs_bit7->setText("Gauge Initialization is in process");
        }
        if(batterystatusarray[15]==0 || batterystatusarray[14]==0  || batterystatusarray[12]==0
                || batterystatusarray[11]==0 )
        {
            ui->bat1_maint_result_l80_bs_bit11to15->setText("No alarm detected");
        }



        Battery1_Result_Maint_Interpret_Voltage();
        Battery1_Result_Maint_Interpret_Temperature();
        Battery1_Result_Maint_Interpret_CycleCount();
        Battery1_Result_Maint_Interpret_Remaining_capacity();
        Battery1_Result_Maint_Interpret_asoc();
        Battery1_Result_Maint_Interpret_battery_status();


}
void MainWindow::Receive_battery1_Maint_l80_temperature(float temp)
{
        float temperature =static_cast<float>(((temp/10.0)-273.15));
        ui->bat1_maint_result_l80_temp->setText(QString::number(temperature));
        QFile file("Mylogfile.txt");
        file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
        QTextStream stream(&file);

        stream<<QString::number(temperature)<<",";
        file.flush();
        file.close();

        Interpret_b1m_temperature[2]=temperature;

}






void MainWindow::on_Test_report_bat1_button_clicked()
{
    QFile logfile("Mylogfile.txt");
    logfile.open(QFile::ReadOnly);
    QTextStream stream(&logfile);
    while(!stream.atEnd()){

        QString line = stream.readAll();
        logfile.close();

        QFileDialog dialog;
        dialog.setFileMode(QFileDialog::AnyFile);
        QString reportFile=dialog.getSaveFileName(NULL,"create New file","","");
        QFile report(reportFile);
        report.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
        QTextStream stream2(&report);
       // stream2<<"\t\t\t\t\t\t BATTERY 1 MAINTENANCE USE CASE REPORT \n";
        stream2<<line;
        report.flush();
        qDebug()<<line;


}


}


void MainWindow::Battery1_Result_Maint_Interpret_Voltage()
{
//qDebug()<<"Interpretation of f80 autotest results\n";
//qDebug()<<Interpret_b1m_result_f80[0];  //cyc
//qDebug()<<Interpret_b1m_result_f80[1];  //remcap
//qDebug()<<Interpret_b1m_result_f80[2];  //asoc
//qDebug()<<Interpret_b1m_result_f80[3];  //voltage
//qDebug()<<Interpret_b1m_result_f80[4];  //baststatus
//qDebug()<<Interpret_b1m_temperature[0]; // Temp

//qDebug()<<"\nInterpretation of m10 autotest results\n";
//qDebug()<<Interpret_b1m_result_m10[0];
//qDebug()<<Interpret_b1m_result_m10[1];
//qDebug()<<Interpret_b1m_result_m10[2];
//qDebug()<<Interpret_b1m_result_m10[3];
//qDebug()<<Interpret_b1m_result_m10[4];
//qDebug()<<Interpret_b1m_temperature[1];

//qDebug()<<"\nInterpretation of l80 autotest results\n";
//qDebug()<<Interpret_b1m_result_l80[0];
//qDebug()<<Interpret_b1m_result_l80[1];
//qDebug()<<Interpret_b1m_result_l80[2];
//qDebug()<<Interpret_b1m_result_l80[3];
//qDebug()<<Interpret_b1m_result_l80[4];
//qDebug()<<Interpret_b1m_temperature[2];

int voltage_f80= Interpret_b1m_result_f80[3];
int voltage_m10= Interpret_b1m_result_m10[3];
int voltage_l80= Interpret_b1m_result_l80[3];




//memset(Interpret_b1m_result_f80,0,sizeof (Interpret_b1m_result_f80));
//memset(Interpret_b1m_result_m10,0,sizeof (Interpret_b1m_result_m10));
//memset(Interpret_b1m_result_l80,0,sizeof (Interpret_b1m_result_l80));

ui->interpret_b1m_voltage->setText("Voltage in a battery is the difference in electrical"
                                   " potential between the +ve and -ve terminals\n of the battery"
                                   " .Here the voltage is sum of measured individual cell volatges."
                                   "If this value > 16.8 V \nBMS shuts down to avoid battery explosion/release of harmful gases"
                                   " and if it reaches < 12 V \nbattery capacity would deteriorate."
                                   " Battery voltage reached "+QString::number(voltage_m10)+" mV when discharged to 10%"
                                   " \n and it was "+QString::number(voltage_l80)+" mV when battery was recharged to 80%"
                                   " which is within the safety range");



}


void MainWindow::Battery1_Result_Maint_Interpret_Temperature() // This function is to interpret bat 1 maint result - temperature
{
float temp_f80=Interpret_b1m_temperature[0];
float temp_m10=Interpret_b1m_temperature[1];
float temp_l80=Interpret_b1m_temperature[2];

if(temp_f80<temp_l80)
{
    ui->interpret_b1m_temperature->setText("Temperature of the battery increased from "+QString::number(temp_f80)
                                           +" °C  to "+QString::number(temp_l80)+"  °C. It is whithin the safety range."
                                           "\nThis happens because several sources such as the charger/discharger board"
                                           ",gauge surrounding\nthe battery dissipates heat into to the battery"
                                           " during the charging discharging process");



}

}

void MainWindow::Battery1_Result_Maint_Interpret_CycleCount()
{
    int cyc_f80=Interpret_b1m_result_f80[0];
    int cyc_m10=Interpret_b1m_result_m10[0];
    int cyc_l80=Interpret_b1m_result_l80[0];

    if(cyc_f80 == cyc_m10 && cyc_m10 == cyc_l80 )
    {
        ui->interpret_b1m_cycles->setText("Battery experiences 1 discharge cycle when, from 80%"
                                          " it is discharged to 10% and recharged\nagain to 80%. "
                                          "As we can see the no of discharge cycles battery has "
                                          "experienced is "+QString::number(cyc_l80)+" and \nthis"
                                          " value increases everytime we charge/discharge the battery"
                                         " as mentioned above");
    }

    if(cyc_f80 < cyc_l80 )
    {
        ui->interpret_b1m_cycles->setText("Battery experiences 1 discharge cycle when, from 80% "
                                          "it is discharged to 10% and recharged\nagain to 80%. "
                                          "As we can see the no of discharge cycles of battery increased "
                                          "from "+QString::number(cyc_f80)+" to "+QString::number(cyc_l80)+ " and \nthis"
                                          " value increases everytime we charge/discharge the battery"
                                         " as mentioned above");

    }




}

void MainWindow::Battery1_Result_Maint_Interpret_Remaining_capacity()
{

int remcap_f80= Interpret_b1m_result_f80[1];
int remcap_m10= Interpret_b1m_result_m10[1];
int remcap_l80= Interpret_b1m_result_l80[1];

ui->interpret_b1m_Remcap->setText("Remaining Capacity(RC) is the amount of current delivered by the battery"
                                  " for a specific time"
                                  "\nperiod. The battery stores the charge while charging "
                                  ",so its remaining capacity increases and "
                                  "\nwhile discharging it delivers the charge, "
                                  "so the remaining capacity decreases"
                                  "\nWe can see the RC decreased to "+QString::number(remcap_m10)+
                                  " when bat was discharged to SoC of 10% and \nit increases again"
                                  " to "+QString::number(remcap_l80)+" when bat was charged to SoC of 80%");


}


void MainWindow::Battery1_Result_Maint_Interpret_asoc()
{

int asoc_f80=Interpret_b1m_result_f80[2];
int asoc_m10=Interpret_b1m_result_m10[2];
int asoc_l80=Interpret_b1m_result_l80[2];

ui->interpret_b1m_ASOC->setText("State of charge (SoC) is the electric charge"
                                " present in the battery relative to its design capacity"
                                "\nDepending upon its value when can predict for how much "
                                "duration the battery would last."
                                "\nIt increases while charging and decreases while discharging the battery");
}

void MainWindow:: Battery1_Result_Maint_Interpret_battery_status()
{

int batstatus_f80=Interpret_b1m_result_f80[4];
int batstatus_m10=Interpret_b1m_result_m10[4];
int batstatus_l80=Interpret_b1m_result_l80[4];

ui->interpret_b1m_batstatus->setText("Battery Status gives information if any alarm such as Overtemperature,"
                                     "\nOvercharge etc has been detected\nThe information about the specific flag detected if any"
                                     "could be observed in the results section");


uint8_t batterystatusarray_f80[16];
if(0<= batstatus_f80 && batstatus_f80<=65535)
{
    for (int j=0;j<16;j++) {
        if(batstatus_f80 % 2 == 0)
        {
            batterystatusarray_f80[j]=0;
        }
        else {
            batterystatusarray_f80[j]=1;
        }
        batstatus_f80 = batstatus_f80 / 2;
    }
}

uint8_t batterystatusarray_m10[16];
if(0<= batstatus_m10 && batstatus_m10<=65535)
{
    for (int j=0;j<16;j++) {
        if(batstatus_f80 % 2 == 0)
        {
            batterystatusarray_m10[j]=0;
        }
        else {
            batterystatusarray_m10[j]=1;
        }
        batstatus_m10 = batstatus_m10 / 2;
    }
}

uint8_t batterystatusarray_l80[16];
if(0<= batstatus_l80 && batstatus_l80<=65535)
{
    for (int j=0;j<16;j++) {
        if(batstatus_l80 % 2 == 0)
        {
            batterystatusarray_l80[j]=0;
        }
        else {
            batterystatusarray_l80[j]=1;
        }
        batstatus_l80 = batstatus_l80 / 2;
    }
}


if(batterystatusarray_f80[15]==0 || batterystatusarray_f80[14]==0  || batterystatusarray_f80[12]==0
        || batterystatusarray_f80[11]==0 ||
        batterystatusarray_m10[15]==0 || batterystatusarray_m10[14]==0  || batterystatusarray_m10[12]==0
                || batterystatusarray_m10[11]==0 ||
        batterystatusarray_l80[15]==0 || batterystatusarray_l80[14]==0  || batterystatusarray_l80[12]==0
                || batterystatusarray_l80[11]==0  )
{
ui->interpret_b1m_batstatus_no_alarm->setText("As we can see no specific alarm was detected"
                                              " throughtout the maintenance use case");
}

// No need for else condition because if any alarm is detected during the execution of Maintenance use case
//then the Maintenance use case would be stopped immediately.The program won't reach interpretation function
// Interpretation function will be executed only when the maintenance use case worked properly
// and no battery alarm was detected.



}


// Following are the slots when Bat2 GI is received during Maintenance Use Case

void MainWindow::Receive_battery2_MaintGI_serial_no(int serialno)
{
   QFile file("Bat2_Maint_log_file.txt"); //

   if(!file.open(QFile::WriteOnly | QFile::Text ))
   {
       //QMessageBox::warning(this,"title","file not open");
   }

   QTextStream stream(&file);
 //  stream<<"\t\t\t\t\t\tLog File\n\n";
   stream<<"\t\t\t\t\t\t BATTERY 2 MAINTENANCE USE CASE REPORT \n";
   stream<<"->Battery 2 Maintenance Use Case general info\n\n";
   stream<<"Serial No:"<<QString::number(serialno)<<"\n";
   stream<<"Manufacturer Name: LS Telcom AG \n";
   file.flush();
   file.close();

   qDebug()<<"Bat 2 from mainwindow GI Serial No received ="<<serialno;
//ui->Bat1_Maint_GI_SN->setText(QString::number(serialno));

//ui->Bat1_Maint_GI_MN->setText("LS Telcom AG");
}

void MainWindow::Receive_battery2_MaintGI_manuf_date(int mandate)
{

uint16_t date = 0x001F & mandate;
uint16_t month = 0x01E0 & mandate;
month = month >> 5;
uint16_t year = 0xFE00 & mandate;
year = year>>9;
year=year+1980;
 qDebug()<<" Bat 2 from mainwindow GI manuf date received ="<<mandate;
//ui->Bat1_Maint_GI_MD->setText(QString::number(date)+"."+QString::number(month)+"."+QString::number(year));

QFile file("Bat2_Maint_log_file.txt");
file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
QTextStream stream(&file);
stream<<"Manufacturing Date:"<<QString::number(date)+"."+QString::number(month)+"."+QString::number(year)+"\n";
file.flush();
file.close();

}

void MainWindow::Receive_battery2_MaintGI_cyclecount(int ccount)
{

//ui->Bat1_Maint_GI_CC->setText(QString::number(ccount));



 QFile file("Bat2_Maint_log_file.txt");
file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
QTextStream stream(&file);
stream<<"Cycle Count:"<<QString::number(ccount)<<" cycles\n";
file.flush();
file.close();
qDebug()<<" Bat 2 from mainwidnow GI cycle count received ="<<ccount;
}

void MainWindow::Receive_battery2_MaintGI_RemCap(int remcap)
{
   //ui->Bat1_Maint_GI_RC->setText(QString::number(remcap));
   QFile file("Bat2_Maint_log_file.txt");
   file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
   QTextStream stream(&file);
   stream<<"Remaining Capacity:"<<QString::number(remcap)<<" mAh \n";
   file.flush();
   file.close();

    qDebug()<<" Bat 2 from mainwidnow GI Rem Cap received ="<<remcap;
}

void MainWindow::Receive_battery2_MaintGI_asoc(int asoc)
{
   //ui->Bat1_Maint_GI_ASOC->setText(QString::number(asoc));
    QFile file("Bat2_Maint_log_file.txt");
   file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
   QTextStream stream(&file);
   stream<<"Absolute State of Charge:"<<QString::number(asoc)<<" % \n";
   file.flush();
   file.close();
    qDebug()<<"Bat 2 from mainwindow GI Asoc received="<<asoc;

}



void MainWindow::Receive_battery2_MaintGI_voltage(int voltage)
{
//ui->Bat1_Maint_GI_Volt->setText(QString::number(voltage));
 QFile file("Bat2_Maint_log_file.txt");
file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
QTextStream stream(&file);
stream<<"Voltage:"<<QString::number(voltage)<<" mV \n";
file.flush();
file.close();
qDebug()<<"Bat 2 from mainwidnow GI Voltage  Received="<<voltage; // This function works
}

void MainWindow::Receive_battery2_MaintGI_batstatus(int bat_status)
{

    qDebug()<<" Bat 2 from mainwidnow GI Batstatus received ="<<bat_status;


   uint8_t batterystatusarray_update[16];
    QFile file("Bat2_Maint_log_file.txt");
   file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
   QTextStream stream(&file);
   stream<<"Battery Status:\n";

   if(0<= bat_status && bat_status<=65535)
   {
       for (int j=0;j<16;j++) {
           if(bat_status % 2 == 0)
           {
               batterystatusarray_update[j]=0;
           }
           else {
               batterystatusarray_update[j]=1;
           }
           bat_status = bat_status / 2;
       }
   }

   if(batterystatusarray_update[15]==1)
   {
     //  ui->Bat1_Maint_GI_BS_bit15to11->setText("Overcharged Alarm detected");
   }
   if(batterystatusarray_update[14]==1)
   {
     //  ui->Bat1_Maint_GI_BS_bit15to11->setText("Terminate charge Alarm detected");
   }
   if(batterystatusarray_update[12]==1)
   {
     //  ui->Bat1_Maint_GI_BS_bit15to11->setText("Overtemperature Alarm detected");
   }
   if(batterystatusarray_update[11]==1)
   {
      // ui->Bat1_Maint_GI_BS_bit15to11->setText("Terminate discharge Alarm detected");
   }

   if(batterystatusarray_update[6]==1)
   {
    //   ui->Bat1_Maint_GI_BS_bit6->setText("Battery is in Discharge /Relax mode");
       stream<<"Battery is in Discharge /Relax mode\n";
   }
   if(batterystatusarray_update[6]==0)
   {
     //  ui->Bat1_Maint_GI_BS_bit6->setText("Battery is in charge mode");
     //  qDebug()<<"Entered charging mode";

   }

   if(batterystatusarray_update[7]==1)
   {
     //  ui->Bat1_Maint_GI_BS_bit7->setText("Gauge Initialization is complete");
       stream<<"Gauge Initialization is complete\n";
   }
   if(batterystatusarray_update[7]==0)
   {
      // ui->Bat1_Maint_GI_BS_bit7->setText("Gauge Initialization is in process");
   }
   if(batterystatusarray_update[15]==0 || batterystatusarray_update[14]==0  || batterystatusarray_update[12]==0
           || batterystatusarray_update[11]==0 )
   {
     //  ui->Bat1_Maint_GI_BS_bit15to11->setText("No alarm detected\nBattery is in good condition");
       stream<<"No alarm Detected\n\n";
   }

   file.flush();
   file.close();

}

void MainWindow::Receive_battery2_MaintGI_temperature(float temp)
{
float temperature =static_cast<float>(((temp/10.0)-273.15));
//ui->Bat1_Maint_GI_Temp->setText(QString::number(temperature));
 QFile file("Bat2_Maint_log_file.txt");
file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
QTextStream stream(&file);
stream<<"Temperature:"<<QString::number(temperature)<<" C \n";
file.flush();
file.close();

qDebug()<<"Bat 2 from mainwindow GI temperature received"<<temperature;
}

// Following are the slots when Bat2 Specific Info is received during Maintenance Use Case

void MainWindow::Receive_battery2_Maint_SpecificInfo_batstatus(int bat_status)
{

    qDebug()<<"Bat2 from mainwindow Specific info batstatus"<<bat_status; // Works
    uint8_t batterystatusarray_update[16];
    QFile file("Bat2_Maint_log_file.txt");
    file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
    QTextStream stream(&file);
    stream<<"->Battery 2 Maintenance Use Case Specific Info\n\n";
    stream<<"Battery Status: \n";
    if(0<= bat_status && bat_status<=65535)
    {
        for (int j=0;j<16;j++) {
            if(bat_status % 2 == 0)
            {
                batterystatusarray_update[j]=0;
            }
            else {
                batterystatusarray_update[j]=1;
            }
            bat_status = bat_status / 2;
        }
    }

    if(batterystatusarray_update[15]==1)
    {
       // ui->Bat1_Maint_SPCI_BS_bit11to15->setText("Overcharged Alarm detected");
    }
    if(batterystatusarray_update[14]==1)
    {
       // ui->Bat1_Maint_SPCI_BS_bit11to15->setText("Terminate charge Alarm detected");
    }
    if(batterystatusarray_update[12]==1)
    {
       // ui->Bat1_Maint_SPCI_BS_bit11to15->setText("Overtemperature Alarm detected");
    }
    if(batterystatusarray_update[11]==1)
    {
       // ui->Bat1_Maint_SPCI_BS_bit11to15->setText("Terminate discharge Alarm detected");
    }

    if(batterystatusarray_update[6]==1)
    {
      //  ui->Bat1_Maint_SPCI_BS_bit6->setText("Battery is in Discharge /Relax mode");
        stream<<"Battery is in Discharge /Relax mode\n";
    }
    if(batterystatusarray_update[6]==0)
    {
       // ui->Bat1_Maint_SPCI_BS_bit6->setText("Battery is in charge mode");
      //  qDebug()<<"Entered charging mode";
    }

    if(batterystatusarray_update[7]==1)
    {
        //ui->Bat1_Maint_SPCI_BS_bit7->setText("Gauge Initialization is complete");
        stream<<"Gauge Initialization is complete\n";
    }
    if(batterystatusarray_update[7]==0)
    {
       // ui->Bat1_Maint_SPCI_BS_bit7->setText("Gauge Initialization is in process");
    }
    if(batterystatusarray_update[15]==0 || batterystatusarray_update[14]==0  || batterystatusarray_update[12]==0
            || batterystatusarray_update[11]==0 )
    {
        //ui->Bat1_Maint_SPCI_BS_bit11to15->setText("No alarm detected");
        stream<<"No alarm detected";
    }


file.flush();
file.close();
}

void MainWindow::Receive_battery2_Maint_SpecificInfo_fullchargecapacity(int fullchargecap)
{
    //ui->Bat1_Maint_SPCI_FCC->setText(QString::number(fullchargecap));

    // Allocated dynamically for interpretation
    Interpret_specific_Info_maint_bat2[0]=fullchargecap;
    //qDebug()<<"This is pointer fcc"<<Interpret_specific_Info_maint_bat1[0];

   QFile file("Bat2_Maint_log_file.txt");
    file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
    QTextStream stream(&file);
    stream<<"\n\nFull Charge Capacity:"<<QString::number(fullchargecap)<<" mAh \n";
    file.flush();
    file.close();

    qDebug()<<"Bat 2 from mainwindow Full charge specific info received"<<fullchargecap;
}

void MainWindow::Receive_battery2_Maint_SpecificInfo_designcapacity(int designcap)
{
    //ui->Bat1_Maint_SPCI_DC->setText(QString::number(designcap));


    Interpret_specific_Info_maint_bat2[1]=designcap;
    //qDebug()<<"This is pointer dc"<<Interpret_specific_Info_maint_bat1[1];
    int fcc=Interpret_specific_Info_maint_bat2[0];
    int dc=Interpret_specific_Info_maint_bat2[1];
    if(fcc>4620 && fcc<dc)
    {

        qDebug()<<"Full charge capacity is whithin specified\n"
                                               "range : 4620-6600 mAh"
                                               "\nBattery's health is good and could be used for respective application";
//

    }
    if(fcc<4620)
    {

                  qDebug()<<"Battery Capacity has deteriorated\n"
                             "The battery should be replaced"
                             "\nIf FCC goes below 4620, then Lithium ions would \ncombine"
                           " with the electrode and it would be difficult to \nrecover them,"
                              "This reduces the battery capacity";

    }
    QFile file("Bat2_Maint_log_file.txt");
    file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
    QTextStream stream(&file);
    stream<<"Design Capacity:"<<QString::number(designcap)<<" mAh \n";
    file.flush();
    file.close();
    //free(Interpret_specific_Info_maint_bat1);  // Specific Info pointer is cleared

     qDebug()<<"Bat 2 from mainwindow design capacity specific info received"<<designcap;

}

void MainWindow::Receive_battery2_Maint_SpecificInfo_run_time_to_empty(int rte)
{



qDebug()<<"Bat2 from mainwindow RTE start specific info received="<<QString::number(rte);
//ui->Bat_Maint_SPCI_RTE_10S->setText(QString::number(rte));// Works

Interpret_b2m_rte[0]=rte;

QFile file("Bat2_Maint_log_file.txt");
file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
QTextStream stream(&file);
stream<<"\n\n Specific Info - Run Time to Empty \n";
stream<<"RTE 10 % discharge start :";
stream<<QString::number(rte);
stream<<" min";
file.flush();
file.close();


}

void MainWindow::Receive_battery2_Maint_SpecificInfo_run_time_to_empty_end_of_discharge(int rte)
{


//    ui->Bat_Maint_SPCI_RTE_10E->setText(QString::number(rte));

    Interpret_b2m_rte[1]=rte;

    Battery2_Maint_Specific_Info_Interpret_RTE();

    QFile file("Bat2_Maint_log_file.txt");
    file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
    QTextStream stream(&file);

    stream<<"\nRTE 10 % discharge end :";
    stream<<QString::number(rte);
    stream<<" min";
    file.flush();
    file.close();

    qDebug()<<"Bat2 from mainwindow RTE end specific info received="<<QString::number(rte);
}


// Following are the slots when Bat2 Maintenance Use Case results are received


// Results bat 2 Maint charged to 80 %
void MainWindow::Receive_battery2_Maint_f80_voltage(int voltage)
{
    //ui->bat1_maint_result_f80_vt->setText(QString::number(voltage));
    QFile file("Bat2_Maint_log_file.txt");
    file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
    QTextStream stream(&file);

    stream<<QString::number(voltage)<<",";
    file.flush();
    file.close();

    Interpret_b2m_result_f80[3]=voltage;
   // qDebug()<< "f80 pos 3 voltage"<<Interpret_b1m_result_f80[3];

  qDebug()<<" Bat 2 from mainwindow F80 Voltage  Received="<<voltage;


}
void MainWindow:: Receive_battery2_Maint_f80_asoc(int asoc)
{
 //ui->bat1_maint_result_f80_asoc->setText(QString::number(asoc));


 QFile file("Bat2_Maint_log_file.txt");
 file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
 QTextStream stream(&file);

 stream<<QString::number(asoc)<<",";
 file.flush();
 file.close();

 Interpret_b2m_result_f80[2]=asoc;
// qDebug()<< "f80 pos 2 asoc"<<Interpret_b1m_result_f80[2];
 qDebug()<<"Bat 2 from mainwindow F80 Asoc received="<<asoc;

}
void MainWindow:: Receive_battery2_Maint_f80_remcap(int remcap)
{
   //ui->bat1_maint_result_f80_remcap->setText(QString::number(remcap));
   QFile file("Bat2_Maint_log_file.txt");
   file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
   QTextStream stream(&file);

   stream<<QString::number(remcap)<<",";
   file.flush();
   file.close();

   Interpret_b2m_result_f80[1]=remcap;
  // qDebug()<< "f80 pos 1 remcap"<<Interpret_b1m_result_f80[1];
   qDebug()<<" Bat 2 from mainwindowF80 Rem Cap received ="<<remcap;

}
void MainWindow:: Receive_battery2_Maint_f80_cycount(int cyclecount)
{
  // ui->bat1_maint_result_f80_cyclecount->setText(QString::number(cyclecount));
  QFile file("Bat2_Maint_log_file.txt");
   file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
   QTextStream stream(&file);
   stream<<"\n->Battery 2 Maintenance Use case Test Results\n";
   stream<<"CycleCount, RemainingCapacity, ASOC, Voltage,Temperature, Battery Status\n";
   stream<<"Battery Charged to 80%\n";
   stream<<QString::number(cyclecount)<<",";
   file.flush();
   file.close();


   Interpret_b2m_result_f80[0]=cyclecount;
   //qDebug()<< "f80 pos 0 cyc"<<Interpret_b1m_result_f80[0];
   qDebug()<<" \nBat 2 from mainwindow F80 cycle count received ="<<cyclecount;



}
void MainWindow:: Receive_battery2_Maint_f80_batstatus(int batstatus)
{
    uint8_t batterystatusarray[16];

    qDebug()<<" Bat 2 from mainwindow F80  Batstatus received ="<<batstatus;


    Interpret_b2m_result_f80[4]=batstatus;
   // qDebug()<< "f80 pos 4 batstatus"<<Interpret_b1m_result_f80[4];



    QFile file("Bat2_Maint_log_file.txt");
    file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
    QTextStream stream(&file);

    stream<<QString::number(batstatus)<<",";
    file.flush();
    file.close();

    if(0<= batstatus && batstatus<=65535)
    {
        for (int j=0;j<16;j++) {
            if(batstatus % 2 == 0)
            {
                batterystatusarray[j]=0;
            }
            else {
                batterystatusarray[j]=1;
            }
            batstatus = batstatus / 2;
        }
    }

    if(batterystatusarray[15]==1)
    {
      //  ui->bat1_maint_result_f80_bs_bit11to15->setText("Overcharged Alarm detected");
    }
    if(batterystatusarray[14]==1)
    {
      //  ui->bat1_maint_result_f80_bs_bit11to15->setText("Terminate charge Alarm detected");
    }
    if(batterystatusarray[12]==1)
    {
      //  ui->bat1_maint_result_f80_bs_bit11to15->setText("Overtemperature Alarm detected");
    }
    if(batterystatusarray[11]==1)
    {
      //  ui->bat1_maint_result_f80_bs_bit11to15->setText("Terminate discharge Alarm detected");
    }

    if(batterystatusarray[6]==1)
    {
      //  ui->bat1_maint_result_f80_bs_bit6->setText("Battery is in Discharge /Relax mode");
    }
    if(batterystatusarray[6]==0)
    {
       // ui->bat1_maint_result_f80_bs_bit6->setText("Battery is in charge mode");

    }

    if(batterystatusarray[7]==1)
    {
       // ui->bat1_maint_result_f80_bs_bit7->setText("Gauge Initialization is complete");
    }
    if(batterystatusarray[7]==0)
    {
      //  ui->bat1_maint_result_f80_bs_bit7->setText("Gauge Initialization is in process");
    }
    if(batterystatusarray[15]==0 || batterystatusarray[14]==0  || batterystatusarray[12]==0
            || batterystatusarray[11]==0 )
    {
      //  ui->bat1_maint_result_f80_bs_bit11to15->setText("No alarm detected");
    }

  //  free(Interpret_b1m_result_f80);

}
void MainWindow::Receive_battery2_Maint_f80_temperature(float temp)
{
        float temperature =static_cast<float>(((temp/10.0)-273.15));
   // ui->bat1_maint_result_f80_temp->setText(QString::number(temperature));
    QFile file("Bat2_Maint_log_file.txt");
    file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
    QTextStream stream(&file);

    stream<<QString::number(temperature)<<",";
    file.flush();
    file.close();

    Interpret_b2m_temperature[0]=temperature;

    qDebug()<<" Bat 2 from mainwindow F80 Temperature received ="<<temperature;


}

// Results bat 2 Maint discharged to 10 %
void MainWindow::Receive_battery2_Maint_m10_voltage(int voltage)
{
        //ui->bat1_maint_result_m80_vt->setText(QString::number(voltage));
        QFile file("Bat2_Maint_log_file.txt");
        file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
        QTextStream stream(&file);

        stream<<QString::number(voltage)<<",";
        file.flush();
        file.close();

        Interpret_b2m_result_m10[3]=voltage;
        qDebug()<<" Bat 2 from mainwindow M10 Voltage  Received="<<voltage;

}

void MainWindow::Receive_battery2_Maint_m10_asoc(int asoc)
{
    //ui->bat1_maint_result_m80_asoc->setText(QString::number(asoc));
    QFile file("Bat2_Maint_log_file.txt");
    file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
    QTextStream stream(&file);

    stream<<QString::number(asoc)<<",";
    file.flush();
    file.close();

    Interpret_b2m_result_m10[2]=asoc;
    qDebug()<<"Bat 2 from mainwindow M10 Asoc received="<<asoc;
}

void MainWindow::Receive_battery2_Maint_m10_remcap(int remcap)
{
    //ui->bat1_maint_result_m80_remcap->setText(QString::number(remcap));
     QFile file("Bat2_Maint_log_file.txt");
    file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
    QTextStream stream(&file);

    stream<<QString::number(remcap)<<",";
    file.flush();
    file.close();

    Interpret_b2m_result_m10[1]=remcap;

    qDebug()<<" Bat 2 from mainwindow M10 Rem Cap received ="<<remcap;
}
void MainWindow::Receive_battery2_Maint_m10_cycount(int cycount)
{
    //ui->bat1_maint_result_m80_cyclecount->setText(QString::number(cycount));
    QFile file("Bat2_Maint_log_file.txt");
    file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
    QTextStream stream(&file);
    stream<<"\n\nBattery Discharged to 10%\n";
    stream<<QString::number(cycount)<<",";
    file.flush();
    file.close();
    Interpret_b2m_result_m10[0]=cycount;

    qDebug()<<" \n Bat 2 from mainwindow M10 cycle count received ="<<cycount;
}

void MainWindow::Receive_battery2_Maint_m10_batstatus(int batstatus)
{

     qDebug()<<" Bat 2 from mainwindow M10 Batstatus received ="<<batstatus;
        uint8_t batterystatusarray[16];

        Interpret_b2m_result_m10[4]=batstatus;

        QFile file("Bat2_Maint_log_file.txt");
        file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
        QTextStream stream(&file);

        stream<<QString::number(batstatus)<<",";
        file.flush();
        file.close();
        if(0<= batstatus && batstatus<=65535)
        {
            for (int j=0;j<16;j++) {
                if(batstatus % 2 == 0)
                {
                    batterystatusarray[j]=0;
                }
                else {
                    batterystatusarray[j]=1;
                }
                batstatus = batstatus / 2;
            }
        }

        if(batterystatusarray[15]==1)
        {
          //  ui->bat1_maint_result_m80_bs_bit11to15->setText("Overcharged Alarm detected");
        }
        if(batterystatusarray[14]==1)
        {
         //   ui->bat1_maint_result_m80_bs_bit11to15->setText("Terminate charge Alarm detected");
        }
        if(batterystatusarray[12]==1)
        {
         //   ui->bat1_maint_result_m80_bs_bit11to15->setText("Overtemperature Alarm detected");
        }
        if(batterystatusarray[11]==1)
        {
        //    ui->bat1_maint_result_m80_bs_bit11to15->setText("Terminate discharge Alarm detected");
        }

        if(batterystatusarray[6]==1)
        {
          //  ui->bat1_maint_result_m80_bs_bit6->setText("Battery is in Discharge /Relax mode");
        }
        if(batterystatusarray[6]==0)
        {
          //  ui->bat1_maint_result_m80_bs_bit6->setText("Battery is in charge mode");

        }

        if(batterystatusarray[7]==1)
        {
          //  ui->bat1_maint_result_m80_bs_bit7->setText("Gauge Initialization is complete");
        }
        if(batterystatusarray[7]==0)
        {
         //   ui->bat1_maint_result_m80_bs_bit7->setText("Gauge Initialization is in process");
        }
        if(batterystatusarray[15]==0 || batterystatusarray[14]==0  || batterystatusarray[12]==0
                || batterystatusarray[11]==0 )
        {
          //  ui->bat1_maint_result_m80_bs_bit11to15->setText("No alarm detected");
        }



}
void MainWindow::Receive_battery2_Maint_m10_temperature(float temp)
{
    float temperature =static_cast<float>(((temp/10.0)-273.15));
    //ui->bat1_maint_result_m80_temp->setText(QString::number(temperature));
    QFile file("Bat2_Maint_log_file.txt");
    file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
    QTextStream stream(&file);

    stream<<QString::number(temperature)<<",";
    file.flush();
    file.close();

    Interpret_b2m_temperature[1]=temperature;

    qDebug()<<" Bat 2 from mainwindow M10 Temperature received ="<<temperature;


}

// Results bat 2 Maint Recharged to 80 %

void MainWindow::Receive_battery2_Maint_l80_voltage(int voltage)
{

      // ui->bat1_maint_result_l80_vt->setText(QString::number(voltage));
      QFile file("Bat2_Maint_log_file.txt");
       file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
       QTextStream stream(&file);

       stream<<QString::number(voltage)<<",";
       file.flush();
       file.close();


      Interpret_b2m_result_l80[3]=voltage;

       qDebug()<<" Bat 2 from mainwindow L80 Voltage  Received="<<voltage;


}
void MainWindow::Receive_battery2_Maint_l80_asoc(int asoc)
{
     //ui->bat1_maint_result_l80_asoc->setText(QString::number(asoc));
     QFile file("Bat2_Maint_log_file.txt");
     file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
     QTextStream stream(&file);

     stream<<QString::number(asoc)<<",";
     file.flush();
     file.close();

     Interpret_b2m_result_l80[2]=asoc;

     qDebug()<<"Bat 2 from mainwindow L80 Asoc received="<<asoc;

}


void MainWindow::Receive_battery2_Maint_l80_remcap(int remcap)
{
    // ui->bat1_maint_result_l80_rempcap->setText(QString::number(remcap));
     QFile file("Bat2_Maint_log_file.txt");
     file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
     QTextStream stream(&file);

     stream<<QString::number(remcap)<<",";
     file.flush();
     file.close();

     Interpret_b2m_result_l80[1]=remcap;

     qDebug()<<" Bat 2 from mainwindow L80 Rem Cap received ="<<remcap;
}


void MainWindow::Receive_battery2_Maint_l80_cycount(int cycount)
{
   //ui->bat1_maint_result_l80_cyclecount->setText(QString::number(cycount));
   QFile file("Bat2_Maint_log_file.txt");
   file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
   QTextStream stream(&file);

   stream<<"\n\nBattery Recharged to 80%\n";
   stream<<QString::number(cycount)<<",";
   file.flush();
   file.close();

   Interpret_b2m_result_l80[0]=cycount;

   qDebug()<<" \nBat 2 from mainwindow L80 cycle count received ="<<cycount;

}
void MainWindow::Receive_battery2_Maint_l80_batstatus(int batstatus)
{

    qDebug()<<" Bat 2 from mainwindow L80  Batstatus received ="<<batstatus;
        uint8_t batterystatusarray[16];

        Interpret_b2m_result_l80[4]=batstatus;

        QFile file("Bat2_Maint_log_file.txt");
        file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
        QTextStream stream(&file);

        stream<<QString::number(batstatus)<<",";
        file.flush();
        file.close();
        if(0<= batstatus && batstatus<=65535)
        {
            for (int j=0;j<16;j++) {
                if(batstatus % 2 == 0)
                {
                    batterystatusarray[j]=0;
                }
                else {
                    batterystatusarray[j]=1;
                }
                batstatus = batstatus / 2;
            }
        }

        if(batterystatusarray[15]==1)
        {
          //  ui->bat1_maint_result_l80_bs_bit11to15->setText("Overcharged Alarm detected");
        }
        if(batterystatusarray[14]==1)
        {
          //  ui->bat1_maint_result_l80_bs_bit11to15->setText("Terminate charge Alarm detected");
        }
        if(batterystatusarray[12]==1)
        {
          //  ui->bat1_maint_result_l80_bs_bit11to15->setText("Overtemperature Alarm detected");
        }
        if(batterystatusarray[11]==1)
        {
          //  ui->bat1_maint_result_l80_bs_bit11to15->setText("Terminate discharge Alarm detected");
        }

        if(batterystatusarray[6]==1)
        {
          //  ui->bat1_maint_result_l80_bs_bit6->setText("Battery is in Discharge /Relax mode");
        }
        if(batterystatusarray[6]==0)
        {
          //  ui->bat1_maint_result_l80_bs_bit6->setText("Battery is in charge mode");

        }

        if(batterystatusarray[7]==1)
        {
          //  ui->bat1_maint_result_l80_bs_bit7->setText("Gauge Initialization is complete");
        }
        if(batterystatusarray[7]==0)
        {
         //   ui->bat1_maint_result_l80_bs_bit7->setText("Gauge Initialization is in process");
        }
        if(batterystatusarray[15]==0 || batterystatusarray[14]==0  || batterystatusarray[12]==0
                || batterystatusarray[11]==0 )
        {
          //  ui->bat1_maint_result_l80_bs_bit11to15->setText("No alarm detected");
        }



        Battery2_Result_Maint_Interpret_Voltage();
        Battery2_Result_Maint_Interpret_Temperature();
        Battery2_Result_Maint_Interpret_CycleCount();
        Battery2_Result_Maint_Interpret_Remaining_capacity();
        Battery2_Result_Maint_Interpret_asoc();
        Battery2_Result_Maint_Interpret_battery_status();


}
void MainWindow::Receive_battery2_Maint_l80_temperature(float temp)
{
        float temperature =static_cast<float>(((temp/10.0)-273.15));
      //  ui->bat1_maint_result_l80_temp->setText(QString::number(temperature));
       QFile file("Bat2_Maint_log_file.txt");
        file.open(QFile::WriteOnly | QFile::Text |QIODevice::Append);
        QTextStream stream(&file);

        stream<<QString::number(temperature)<<",";
        file.flush();
        file.close();

        Interpret_b2m_temperature[2]=temperature;

        qDebug()<<" Bat 2 from mainwindow L80 Temperature received ="<<temperature;


}

// Following are the slots when Bat2 Update Info is received during Maintenance Use Case

void MainWindow::bat2_update_voltage_maint_read(int volt)
{
   // ui->Bat1_Maint_GI_Volt->setText(QString::number(volt));

    qDebug()<<" Bat2 from mainwindow updated voltage received"<<volt;
}

void MainWindow::bat2_update_asoc_maint_read(int asoc)
{
//        ui->Bat1_Maint_GI_ASOC->setText(QString::number(asoc));
//         ui->progressBar->setValue(asoc);

    qDebug()<<"Bat2 from mainwindow Updated ASOC  Received="<<asoc;
}


void MainWindow::bat2_update_temp_maint_read(float temp)
{
//ui->Bat1_Maint_GI_Temp->setText(QString::number(temp));

   qDebug()<<"Bat2 from mainwindow Updated temp  Received="<<temp;
}

void MainWindow::bat2_update_remcap_maint_read(int rcap)
{
//ui->Bat1_Maint_GI_RC->setText(QString::number(rcap));

    qDebug()<<"Bat2 from mainwindow Updated rem cap  Received="<<rcap;
}

void MainWindow::bat2_update_cyclecount_maint_read(int count)
{
//ui->Bat1_Maint_GI_CC->setText(QString::number(count));

    qDebug()<<"Bat2 from mainwindow Updated cycle count  Received="<<count;
}





void MainWindow::bat2_update_batstatus_maint_read(int bat_status)
{
//ui->Bat1_Maint_GI_BS_bit15to11->setText(QString::number(bat_status));
//qDebug()<< "Entered BS function";
//qDebug()<<bat_status;   // Works properly

    qDebug()<<"Bat2 from mainwindow Updated batstatus  Received="<<bat_status;

uint8_t batterystatusarray_update[16];
if(0<= bat_status && bat_status<=65535)
{
    for (int j=0;j<16;j++) {
        if(bat_status % 2 == 0)
        {
            batterystatusarray_update[j]=0;
        }
        else {
            batterystatusarray_update[j]=1;
        }
        bat_status = bat_status / 2;
    }
}

if(batterystatusarray_update[15]==1)
{
   // ui->Bat1_Maint_GI_BS_bit15to11->setText("Overcharged Alarm detected");
}
if(batterystatusarray_update[14]==1)
{
   // ui->Bat1_Maint_GI_BS_bit15to11->setText("Terminate charge Alarm detected");
}
if(batterystatusarray_update[12]==1)
{
   // ui->Bat1_Maint_GI_BS_bit15to11->setText("Overtemperature Alarm detected");
}
if(batterystatusarray_update[11]==1)
{
   // ui->Bat1_Maint_GI_BS_bit15to11->setText("Terminate discharge Alarm detected");
}

if(batterystatusarray_update[6]==1)
{
   // ui->Bat1_Maint_GI_BS_bit6->setText("Battery is in Discharge /Relax mode");
}
if(batterystatusarray_update[6]==0)
{
   // ui->Bat1_Maint_GI_BS_bit6->setText("Battery is in charge mode");
  //  qDebug()<<"Entered charging mode";
}

if(batterystatusarray_update[7]==1)
{
   // ui->Bat1_Maint_GI_BS_bit7->setText("Gauge Initialization is complete");
}
if(batterystatusarray_update[7]==0)
{
  //  ui->Bat1_Maint_GI_BS_bit7->setText("Gauge Initialization is in process");
}
if(batterystatusarray_update[15]==0 || batterystatusarray_update[14]==0  || batterystatusarray_update[12]==0
        || batterystatusarray_update[11]==0 )
{
   // ui->Bat1_Maint_GI_BS_bit15to11->setText("No alarm detected\nBattery is in good condition");
}
}

// Following are the slots to interpret bat 2 maintenance use case parameters

void MainWindow::Battery2_Result_Maint_Interpret_Voltage()
{


int voltage_f80= Interpret_b2m_result_f80[3];
int voltage_m10= Interpret_b2m_result_m10[3];
int voltage_l80= Interpret_b2m_result_l80[3];






qDebug()<<"Voltage in a battery is the difference in electrical"
                                   " potential between the +ve and -ve terminals\n of the battery"
                                   " .Here the voltage is sum of measured individual cell volatges."
                                   "If this value > 16.8 V \nBMS shuts down to avoid battery explosion/release of harmful gases"
                                   " and if it reaches < 12 V \nbattery capacity would deteriorate."
                                   " Battery voltage reached "+QString::number(voltage_m10)+" mV when discharged to 10%"
                                   " \n and it was "+QString::number(voltage_l80)+" mV when battery was recharged to 80%"
                                   " which is within the safety range";



}

void MainWindow::Battery2_Result_Maint_Interpret_Temperature() // This function is to interpret bat 1 maint result - temperature
{
float temp_f80=Interpret_b2m_temperature[0];
float temp_m10=Interpret_b2m_temperature[1];
float temp_l80=Interpret_b2m_temperature[2];

if(temp_f80<temp_l80)
{
    qDebug()<<"Temperature of the battery increased from "+QString::number(temp_f80)
                                           +" °C  to "+QString::number(temp_l80)+"  °C. It is whithin the safety range."
                                           "\nThis happens because several sources such as the charger/discharger board"
                                           ",gauge surrounding\nthe battery dissipates heat into to the battery"
                                           " during the charging discharging process";



}

}

void MainWindow::Battery2_Result_Maint_Interpret_CycleCount()
{
    int cyc_f80=Interpret_b2m_result_f80[0];
    int cyc_m10=Interpret_b2m_result_m10[0];
    int cyc_l80=Interpret_b2m_result_l80[0];

    if(cyc_f80 == cyc_m10 && cyc_m10 == cyc_l80 )
    {
        qDebug()<<"Battery experiences 1 discharge cycle when, from 80%"
                                          " it is discharged to 10% and recharged\nagain to 80%. "
                                          "As we can see the no of discharge cycles battery has "
                                          "experienced is "+QString::number(cyc_l80)+" and \nthis"
                                          " value increases everytime we charge/discharge the battery"
                                         " as mentioned above";
    }

    if(cyc_f80 < cyc_l80 )
    {
        qDebug()<<"Battery experiences 1 discharge cycle when, from 80% "
                                          "it is discharged to 10% and recharged\nagain to 80%. "
                                          "As we can see the no of discharge cycles of battery increased "
                                          "from "+QString::number(cyc_f80)+" to "+QString::number(cyc_l80)+ " and \nthis"
                                          " value increases everytime we charge/discharge the battery"
                                         " as mentioned above";

    }




}

void MainWindow::Battery2_Result_Maint_Interpret_Remaining_capacity()
{

int remcap_f80= Interpret_b2m_result_f80[1];
int remcap_m10= Interpret_b2m_result_m10[1];
int remcap_l80= Interpret_b2m_result_l80[1];

qDebug()<<"Remaining Capacity(RC) is the amount of current delivered by the battery"
                                  " for a specific time"
                                  "\nperiod. The battery stores the charge while charging "
                                  ",so its remaining capacity increases and "
                                  "\nwhile discharging it delivers the charge, "
                                  "so the remaining capacity decreases"
                                  "\nWe can see the RC decreased to "+QString::number(remcap_m10)+
                                  " when bat was discharged to SoC of 10% and \nit increases again"
                                  " to "+QString::number(remcap_l80)+" when bat was charged to SoC of 80%";


}


void MainWindow::Battery2_Result_Maint_Interpret_asoc()
{

int asoc_f80=Interpret_b2m_result_f80[2];
int asoc_m10=Interpret_b2m_result_m10[2];
int asoc_l80=Interpret_b2m_result_l80[2];

qDebug()<<"State of charge (SoC) is the electric charge"
                                " present in the battery relative to its design capacity"
                                "\nDepending upon its value when can predict for how much "
                                "duration the battery would last."
                                "\nIt increases while charging and decreases while discharging the battery";
}

void MainWindow:: Battery2_Result_Maint_Interpret_battery_status()
{

int batstatus_f80=Interpret_b2m_result_f80[4];
int batstatus_m10=Interpret_b2m_result_m10[4];
int batstatus_l80=Interpret_b2m_result_l80[4];

qDebug()<<"Battery Status gives information if any alarm such as Overtemperature,"
                                     "\nOvercharge etc has been detected\nThe information about the specific flag detected if any"
                                     "could be observed in the results section";


uint8_t batterystatusarray_f80[16];
if(0<= batstatus_f80 && batstatus_f80<=65535)
{
    for (int j=0;j<16;j++) {
        if(batstatus_f80 % 2 == 0)
        {
            batterystatusarray_f80[j]=0;
        }
        else {
            batterystatusarray_f80[j]=1;
        }
        batstatus_f80 = batstatus_f80 / 2;
    }
}

uint8_t batterystatusarray_m10[16];
if(0<= batstatus_m10 && batstatus_m10<=65535)
{
    for (int j=0;j<16;j++) {
        if(batstatus_f80 % 2 == 0)
        {
            batterystatusarray_m10[j]=0;
        }
        else {
            batterystatusarray_m10[j]=1;
        }
        batstatus_m10 = batstatus_m10 / 2;
    }
}

uint8_t batterystatusarray_l80[16];
if(0<= batstatus_l80 && batstatus_l80<=65535)
{
    for (int j=0;j<16;j++) {
        if(batstatus_l80 % 2 == 0)
        {
            batterystatusarray_l80[j]=0;
        }
        else {
            batterystatusarray_l80[j]=1;
        }
        batstatus_l80 = batstatus_l80 / 2;
    }
}


if(batterystatusarray_f80[15]==0 || batterystatusarray_f80[14]==0  || batterystatusarray_f80[12]==0
        || batterystatusarray_f80[11]==0 ||
        batterystatusarray_m10[15]==0 || batterystatusarray_m10[14]==0  || batterystatusarray_m10[12]==0
                || batterystatusarray_m10[11]==0 ||
        batterystatusarray_l80[15]==0 || batterystatusarray_l80[14]==0  || batterystatusarray_l80[12]==0
                || batterystatusarray_l80[11]==0  )
{
qDebug()<<"As we can see no specific alarm was detected"
                                              " throughtout the maintenance use case";
}

// No need for else condition because if any alarm is detected during the execution of Maintenance use case
//then the Maintenance use case would be stopped immediately.The program won't reach interpretation function
// Interpretation function will be executed only when the maintenance use case worked properly
// and no battery alarm was detected.



}

void MainWindow::Battery2_Maint_Specific_Info_Interpret_RTE()
{
    int rte1,rte2;
    rte1=Interpret_b2m_rte[0];
    rte2=Interpret_b2m_rte[1];

    if(rte1>rte2)
    {
    qDebug()<<"Run time to empty gives how long the battery will last "
                                               "under a given load."
                                               "\nThis parameter decreases as we discharge the battery"
                                               "\nRTE was "+QString::number(rte1)+" min at the when battery"
                                                " discharging was started. "
                                                "\nIt decreased to "+QString::number(rte2)+" min by the end of discharge cycle";
    }
}

#include "data_processing_thread.h"
#include <QThread>
#include <QtCore>
#include <QtSerialPort>
#include <QFloat16>
#include "QDebug"

data_process::data_process(QObject *parent) : QObject(parent)
{


}

void data_process::data_from_worker(QByteArray rx)
{
    //  qDebug()<<"Entered thread data processing";
    // Program reaches here
    //    qDebug()<<rx;



    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='U' &&rx[3]=='P' &&rx[4]=='V'&&
            rx[5]=='T' && rx[6]=='S' && rx[9]=='V' &&rx[10]=='T' &&rx[11]=='U'
            && rx[12]=='P' && rx[13]=='E'  )
    {
        quint8 M=0;
        quint8 L=0;
        int v;
        M=rx[7];
        L=rx[8];
        v=((M<<8)+L);
        emit send_bat1_update_voltage_maint(v);
     //   qDebug()<<"Updated Voltage  Received="<<v;

    }

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='U' &&rx[3]=='P' &&rx[4]=='A'&&
            rx[5]=='S' && rx[6]=='S' && rx[8]=='A' && rx[9]=='S' &&rx[10]=='E' &&rx[11]=='U'
            && rx[12]=='P' && rx[13]=='E'  )
    {
        int a;
        a=rx[7];
        //  emit asocread(a);
        emit send_bat1_update_asoc_maint(a);
    //    qDebug()<<"Updated ASOC  Received="<<a;


    }

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='U' &&rx[3]=='P' &&rx[4]=='T'&&
            rx[5]=='P' && rx[6]=='S' && rx[9]=='T' &&rx[10]=='P' &&rx[11]=='U'
            && rx[12]=='P' && rx[13]=='E' )
    {
        quint8 t1=0;
        quint8 t2=0;
        float t=0;
        t1=rx[7];
        t2=rx[8];
        t=static_cast<float>(((t1<<8)+t2));
        t=static_cast<float>(((t/10.0)-273.15));
        emit send_bat1_update_temp_maint(t);
      //  qDebug()<<"Updated Temp  Received="<<t;


    }

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='U' &&rx[3]=='P' &&rx[4]=='R'&&
            rx[5]=='C' && rx[6]=='S' && rx[9]=='R' &&rx[10]=='C' &&rx[11]=='U'
            && rx[12]=='P' && rx[13]=='E'   )
    {
        quint8 r1=0;
        quint8 r2=0;
        int r;
        r1=rx[7];
        r2=rx[8];
        r=((r1<<8)+r2);
        emit send_bat1_update_remcap_maint(r);
      //  qDebug()<<"Updated Remcap  Received="<<r;


    }

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='U' &&rx[3]=='P' &&rx[4]=='C'&&
            rx[5]=='C' && rx[6]=='S' && rx[9]=='C' &&rx[10]=='C' &&rx[11]=='U'
            && rx[12]=='P' && rx[13]=='E'   )
    {
        quint8 c1=0;
        quint8 c2=0;
        int c;
        c1=rx[7];
        c2=rx[8];
        c=((c1<<8)+c2);
   //     qDebug()<<"Updated Cyc Count Received="<<c;
        emit send_bat1_update_cyccount_maint(c);
        // memset(rx_array,0,sizeof (rx_array));

    }

    //    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='G' &&rx[3]=='C' &&rx[4]=='R'   )
    //    {
    //        quint8 current1=0;
    //        quint8 current2=0;
    //        int current;
    //        current1=rx[5];
    //        current2=rx[6];
    //        current=((current1<<8)+current2);
    //     //   emit curead(current);
    //        // memset(buf2,0,sizeof (buf2));

    //    }
    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='U' &&rx[3]=='P' &&rx[4]=='B'&&
            rx[5]=='S' && rx[6]=='S' && rx[9]=='B' &&rx[10]=='S' &&rx[11]=='U'
            && rx[12]=='P' && rx[13]=='E'   )
    {
        quint8 bs1=0;
        quint8 bs2=0;
        int bstatus;
        bs1=rx[7];
        bs2=rx[8];
        bstatus=((bs1<<8)+bs2);
        emit send_bat1_update_batstatus_maint(bstatus);

     //   qDebug()<<"Updated Batstatus Received="<<bstatus;

    }

    // General Info Bat 1 - Voltage

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='G' && rx[3]=='I' &&rx[4]=='V' &&
            rx[5]=='T' && rx[6]=='S' && rx[9]=='V' &&rx[10]=='T' &&rx[11]=='G'
            && rx[12]=='I' && rx[13]=='E')
    {

        //  qDebug()<<"Entered voltage function recent";
        quint8 M=0;
        quint8 L=0;
        int v;
        M=rx[7];
        L=rx[8];
        v=((M<<8)+L);
      emit send_battery1_MaintGI_voltage(v);
        qDebug()<<"GI Voltage  Received="<<v; // This function works
    }

    // General Info Bat 1 - asoc

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='G' && rx[3]=='I' &&rx[4]=='A' &&
            rx[5]=='S' && rx[6]=='S' && rx[8]=='A' &&rx[9]=='S' &&rx[10]=='E'
            && rx[11]=='G' && rx[12]=='I' && rx[13]=='E')
    {

        int asoc;
        asoc=rx[7];
        emit send_battery1_MaintGI_asoc(asoc);
        qDebug()<<"GI Asoc received="<<asoc;


    }


    // General Info Bat 1 - Serial No

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='G' && rx[3]=='I' &&rx[4]=='S' &&
            rx[5]=='N' && rx[6]=='S' && rx[9]=='S' &&rx[10]=='N' &&rx[11]=='G'
            && rx[12]=='I' && rx[13]=='E')
    {

        quint8 sern1=rx[7];
        quint8 sern2=rx[8];
        int sernum=((sern1<<8)+sern2);
        emit send_battery1_MaintGI_serial_no(sernum);
        qDebug()<<"GI Serial No received ="<<sernum;

    }

    // General Info Bat 1 - Manufacturing date

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='G' && rx[3]=='I' &&rx[4]=='M' &&
            rx[5]=='D' && rx[6]=='S' && rx[9]=='M' &&rx[10]=='D' &&rx[11]=='G'
            && rx[12]=='I' && rx[13]=='E')
    {
        quint8 mdd1=rx[7];
        quint8 mdd2=rx[8];
        int manuf_date;
        manuf_date=((mdd1<<8)+mdd2);
        qDebug()<<" GI manuf date received ="<<manuf_date;
        uint16_t date = 0x001F & manuf_date;
        uint16_t month = 0x01E0 & manuf_date;
        month = month >> 5;
        uint16_t year = 0xFE00 & manuf_date;
        year = year>>9;
        year=year+1980;
        qDebug()<<date;
        qDebug()<<month;
        qDebug()<<year;
        emit send_battery1_MaintGI_manuf_date(manuf_date);

    }


    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='G' && rx[3]=='I' &&rx[4]=='C' &&
            rx[5]=='C' && rx[6]=='S' && rx[9]=='C' &&rx[10]=='C' &&rx[11]=='G'
            && rx[12]=='I' && rx[13]=='E')
    {
        quint8 ccc1=rx[7];
        quint8 ccc2=rx[8];
        int ccount;
        ccount=((ccc1<<8)+ccc2);
        emit send_battery1_MaintGI_cyclecount(ccount);
        qDebug()<<" GI cycle count received ="<<ccount;

    }


    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='G' && rx[3]=='I' &&rx[4]=='R' &&
            rx[5]=='C' && rx[6]=='S' && rx[9]=='R' &&rx[10]=='C' &&rx[11]=='G'
            && rx[12]=='I' && rx[13]=='E')
    {

        quint8 rcc1=rx[7];
        quint8 rcc2=rx[8];
        int remcapac=((rcc1<<8)+rcc2);
        emit send_battery1_MaintGI_RemCap(remcapac);
        qDebug()<<" GI Rem Cap received ="<<remcapac;


    }

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='G' && rx[3]=='I' &&rx[4]=='T' &&
            rx[5]=='P' && rx[6]=='S' && rx[9]=='T' &&rx[10]=='P' &&rx[11]=='G'
            && rx[12]=='I' && rx[13]=='E')
    {
                       quint8 temp1=rx[7];
                       quint8 temp2=rx[8];
                       float temperature=((temp1<<8)+temp2);
                       float temperatureGI =static_cast<float>(((temperature/10.0)-273.15));
                       emit send_battery1_MaintGI_temperature(temperature);
                        qDebug()<<" GI Temperature received ="<<temperatureGI;

    }

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='G' && rx[3]=='I' &&rx[4]=='B' &&
            rx[5]=='S' && rx[6]=='S' && rx[9]=='B' &&rx[10]=='S' &&rx[11]=='G'
            && rx[12]=='I' && rx[13]=='E')
    {

                        quint8 bs1=rx[7];
                        quint8 bs2=rx[8];
                        int bstatus=((bs1<<8)+bs2);
                        emit send_battery1_MaintGI_batstatus(bstatus);
                         qDebug()<<" GI Batstatus received ="<<bstatus;

    }

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='S' && rx[3]=='I' &&rx[4]=='B' &&
            rx[5]=='S' && rx[6]=='S' && rx[9]=='B' &&rx[10]=='S' &&rx[11]=='S'
            && rx[12]=='I' && rx[13]=='E')
    {
        quint8 bs1=rx[7];
        quint8 bs2=rx[8];
        int bstatus=((bs1<<8)+bs2);

        emit send_battery1_Maint_SpecificInfo_batstatus(bstatus);
        qDebug()<<"Bat status specific info received"<<bstatus;
    }

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='S' && rx[3]=='I' &&rx[4]=='D' &&
            rx[5]=='C' && rx[6]=='S' && rx[9]=='D' &&rx[10]=='C' &&rx[11]=='S'
            && rx[12]=='I' && rx[13]=='E')
    {
        quint8 dc1=rx[7];
        quint8 dc2=rx[8];
        int design_cap=((dc1<<8)+dc2);

    emit send_battery1_Maint_SpecificInfo_designcapacity(design_cap);
        qDebug()<<"design capacity specific info received";
    }

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='S' && rx[3]=='I' &&rx[4]=='F' &&
            rx[5]=='C' && rx[6]=='S' && rx[9]=='F' &&rx[10]=='C' &&rx[11]=='S'
            && rx[12]=='I' && rx[13]=='E')
    {

        quint8 fcc1=rx[7];
        quint8 fcc2=rx[8];
        int fcc=((fcc1<<8)+fcc2);
        emit send_battery1_Maint_SpecificInfo_fullchargecapacity(fcc);

        qDebug()<<"Full charge specific info received";
    }


    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='S' && rx[3]=='I' &&rx[4]=='R' &&
            rx[5]=='T' && rx[6]=='S' && rx[9]=='R' &&rx[10]=='T' &&rx[11]=='F'
            && rx[12]=='I' && rx[13]=='E')
    {

        quint8 rte1=rx[7];
        quint8 rte2=rx[8];
        int rte=((rte1<<8)+rte2);
        emit send_battery1_Maint_SpecificInfo_run_time_to_empty(rte);

       // qDebug()<<"RTE specific info received="<<QString::number(rte); // Works
    }

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='S' && rx[3]=='I' &&rx[4]=='R' &&
            rx[5]=='T' && rx[6]=='S' && rx[9]=='R' &&rx[10]=='T' &&rx[11]=='L'
            && rx[12]=='I' && rx[13]=='E')
    {

        quint8 rte1=rx[7];
        quint8 rte2=rx[8];
        int rte=((rte1<<8)+rte2);
        emit send_battery1_Maint_SpecificInfo_run_time_to_empty_end_of_discharge(rte);

       // qDebug()<<"RTE specific info received="<<QString::number(rte); // Works
    }







    // Following are the functions for the results of Autotest

    // Result when bat 1 is charged to 80 % in Maintenance Use Case

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='R' && rx[3]=='F' &&rx[4]=='8' &&
            rx[5]=='V' && rx[6]=='T' && rx[9]=='V' &&rx[10]=='T' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')  // Result F80 Voltage
    {


        quint8 M=0;
        quint8 L=0;
        int v;
        M=rx[7];
        L=rx[8];
        v=((M<<8)+L);
       emit send_battery1_Maint_f80_voltage(v);
        qDebug()<<" F80 Voltage  Received="<<v; // This function works
    }

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='R' && rx[3]=='F' &&rx[4]=='8' &&
            rx[5]=='A' && rx[6]=='S' && rx[8]=='A' &&rx[9]=='S' &&rx[10]=='E'
            && rx[11]=='E' && rx[12]=='N' && rx[13]=='D') // Result F80 ASOC
    {

        int asoc;
        asoc=rx[7];
        emit send_battery1_Maint_f80_asoc(asoc);
        qDebug()<<"F80 Asoc received="<<asoc;


    }

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='R' && rx[3]=='F' &&rx[4]=='8' &&
            rx[5]=='R' && rx[6]=='C' && rx[9]=='R' &&rx[10]=='C' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')     // Result F80 Remcap
    {

        quint8 rcc1=rx[7];
        quint8 rcc2=rx[8];
        int remcapac=((rcc1<<8)+rcc2);
        emit send_battery1_Maint_f80_remcap(remcapac);
        qDebug()<<" F80 Rem Cap received ="<<remcapac;


    }

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='R' && rx[3]=='F' &&rx[4]=='8' &&
            rx[5]=='C' && rx[6]=='C' && rx[9]=='C' &&rx[10]=='C' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')  // Result F80 Cycle Count
    {
        quint8 ccc1=rx[7];
        quint8 ccc2=rx[8];
        int ccount;
        ccount=((ccc1<<8)+ccc2);
        emit send_battery1_Maint_f80_cycount(ccount);
        qDebug()<<" \nF80 cycle count received ="<<ccount;

    }


    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='R' && rx[3]=='F' &&rx[4]=='8' &&
            rx[5]=='T' && rx[6]=='P' && rx[9]=='T' &&rx[10]=='P' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')    // Result F80 Temperature
    {
                       quint8 temp1=rx[7];
                       quint8 temp2=rx[8];
                       float temperature=((temp1<<8)+temp2);
                       float temperatureGI =static_cast<float>(((temperature/10.0)-273.15));
                       emit send_battery1_Maint_f80_temperature(temperature);
                        qDebug()<<" F80 Temperature received ="<<temperatureGI;

    }

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='R' && rx[3]=='F' &&rx[4]=='8' &&
            rx[5]=='B' && rx[6]=='S' && rx[9]=='B' &&rx[10]=='S' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')   // Result F80 Battery Status
    {

                        quint8 bs1=rx[7];
                        quint8 bs2=rx[8];
                        int bstatus=((bs1<<8)+bs2);
                        emit send_battery1_Maint_f80_batstatus(bstatus);
                         qDebug()<<" F80  Batstatus received ="<<bstatus;

    }

    // Result when bat 1 is discharged to 10 % in Maintenance Use Case

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='R' && rx[3]=='M' &&rx[4]=='1' &&
            rx[5]=='V' && rx[6]=='T' && rx[9]=='V' &&rx[10]=='T' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')  // Result M10 Voltage
    {


        quint8 M=0;
        quint8 L=0;
        int v;
        M=rx[7];
        L=rx[8];
        v=((M<<8)+L);
       emit send_battery1_Maint_m10_voltage(v);
        qDebug()<<" M10 Voltage  Received="<<v; // This function works
    }

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='R' && rx[3]=='M' &&rx[4]=='1' &&
            rx[5]=='A' && rx[6]=='S' && rx[8]=='A' &&rx[9]=='S' &&rx[10]=='E'
            && rx[11]=='E' && rx[12]=='N' && rx[13]=='D') // Result M10 ASOC
    {

        int asoc;
        asoc=rx[7];
        emit send_battery1_Maint_m10_asoc(asoc);
        qDebug()<<"M10 Asoc received="<<asoc;


    }

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='R' && rx[3]=='M' &&rx[4]=='1' &&
            rx[5]=='R' && rx[6]=='C' && rx[9]=='R' &&rx[10]=='C' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')     // Result M10 Remcap
    {

        quint8 rcc1=rx[7];
        quint8 rcc2=rx[8];
        int remcapac=((rcc1<<8)+rcc2);
        emit send_battery1_Maint_m10_remcap(remcapac);
        qDebug()<<" M10 Rem Cap received ="<<remcapac;


    }

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='R' && rx[3]=='M' &&rx[4]=='1' &&
            rx[5]=='C' && rx[6]=='C' && rx[9]=='C' &&rx[10]=='C' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')  // Result M10 Cycle Count
    {
        quint8 ccc1=rx[7];
        quint8 ccc2=rx[8];
        int ccount;
        ccount=((ccc1<<8)+ccc2);
        emit send_battery1_Maint_m10_cycount(ccount);
        qDebug()<<" \n M10 cycle count received ="<<ccount;

    }


    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='R' && rx[3]=='M' &&rx[4]=='1' &&
            rx[5]=='T' && rx[6]=='P' && rx[9]=='T' &&rx[10]=='P' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')    // Result M10 Temperature
    {
                       quint8 temp1=rx[7];
                       quint8 temp2=rx[8];
                       float temperature=((temp1<<8)+temp2);
                       float temperatureGI =static_cast<float>(((temperature/10.0)-273.15));
                       emit send_battery1_Maint_m10_temperature(temperature);
                        qDebug()<<" M10 Temperature received ="<<temperatureGI;

    }

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='R' && rx[3]=='M' &&rx[4]=='1' &&
            rx[5]=='B' && rx[6]=='S' && rx[9]=='B' &&rx[10]=='S' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')   // Result M10 Battery Status
    {

                        quint8 bs1=rx[7];
                        quint8 bs2=rx[8];
                        int bstatus=((bs1<<8)+bs2);
                        emit send_battery1_Maint_m10_batstatus(bstatus);
                         qDebug()<<" M10  Batstatus received ="<<bstatus;

    }


    // Result when bat 1 is Recharged to 80 % in Maintenance Use Case

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='R' && rx[3]=='L' &&rx[4]=='8' &&
            rx[5]=='V' && rx[6]=='T' && rx[9]=='V' &&rx[10]=='T' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')  // Result L80 Voltage
    {


        quint8 M=0;
        quint8 L=0;
        int v;
        M=rx[7];
        L=rx[8];
        v=((M<<8)+L);
       emit send_battery1_Maint_l80_voltage(v);
        qDebug()<<"  L80 Voltage  Received="<<v; // This function works
    }

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='R' && rx[3]=='L' &&rx[4]=='8' &&
            rx[5]=='A' && rx[6]=='S' && rx[8]=='A' &&rx[9]=='S' &&rx[10]=='E'
            && rx[11]=='E' && rx[12]=='N' && rx[13]=='D') // Result L80 ASOC
    {

        int asoc;
        asoc=rx[7];
        emit send_battery1_Maint_l80_asoc(asoc);
        qDebug()<<"L80 Asoc received="<<asoc;


    }

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='R' && rx[3]=='L' &&rx[4]=='8' &&
            rx[5]=='R' && rx[6]=='C' && rx[9]=='R' &&rx[10]=='C' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')     // Result L80 Remcap
    {

        quint8 rcc1=rx[7];
        quint8 rcc2=rx[8];
        int remcapac=((rcc1<<8)+rcc2);
        emit send_battery1_Maint_l80_remcap(remcapac);
        qDebug()<<" L80 Rem Cap received ="<<remcapac;


    }

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='R' && rx[3]=='L' &&rx[4]=='8' &&
            rx[5]=='C' && rx[6]=='C' && rx[9]=='C' &&rx[10]=='C' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')  // Result L80 Cycle Count
    {
        quint8 ccc1=rx[7];
        quint8 ccc2=rx[8];
        int ccount;
        ccount=((ccc1<<8)+ccc2);
        emit send_battery1_Maint_l80_cycount(ccount);
        qDebug()<<" \nL80 cycle count received ="<<ccount;

    }


    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='R' && rx[3]=='L' &&rx[4]=='8' &&
            rx[5]=='T' && rx[6]=='P' && rx[9]=='T' &&rx[10]=='P' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')    // Result L80 Temperature
    {
                       quint8 temp1=rx[7];
                       quint8 temp2=rx[8];
                       float temperature=((temp1<<8)+temp2);
                       float temperatureGI =static_cast<float>(((temperature/10.0)-273.15));
                       emit send_battery1_Maint_l80_temperature(temperature);
                        qDebug()<<" L80 Temperature received ="<<temperatureGI;

    }

    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='R' && rx[3]=='L' &&rx[4]=='8' &&
            rx[5]=='B' && rx[6]=='S' && rx[9]=='B' &&rx[10]=='S' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')   // Result L80 Battery Status
    {

                        quint8 bs1=rx[7];
                        quint8 bs2=rx[8];
                        int bstatus=((bs1<<8)+bs2);
                        emit send_battery1_Maint_l80_batstatus(bstatus);
                         qDebug()<<" L80  Batstatus received ="<<bstatus;

    }


   // Following are the functions that receive bat 2 maintenance
   // general information


    // General Info Bat 2 - Voltage

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='G' && rx[3]=='I' &&rx[4]=='V' &&
            rx[5]=='T' && rx[6]=='S' && rx[9]=='V' &&rx[10]=='T' &&rx[11]=='G'
            && rx[12]=='I' && rx[13]=='E')
    {

        //  qDebug()<<"Entered voltage function recent";
        quint8 M=0;
        quint8 L=0;
        int v;
        M=rx[7];
        L=rx[8];
        v=((M<<8)+L);
      emit send_battery2_MaintGI_voltage(v);
        //qDebug()<<"Bat 2 GI Voltage  Received="<<v; // This function works
    }

    // General Info Bat 2 - asoc

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='G' && rx[3]=='I' &&rx[4]=='A' &&
            rx[5]=='S' && rx[6]=='S' && rx[8]=='A' &&rx[9]=='S' &&rx[10]=='E'
            && rx[11]=='G' && rx[12]=='I' && rx[13]=='E')
    {

        int asoc;
        asoc=rx[7];
        emit send_battery2_MaintGI_asoc(asoc);
      //  qDebug()<<"Bat 2 GI Asoc received="<<asoc;


    }


    // General Info Bat 2 - Serial No

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='G' && rx[3]=='I' &&rx[4]=='S' &&
            rx[5]=='N' && rx[6]=='S' && rx[9]=='S' &&rx[10]=='N' &&rx[11]=='G'
            && rx[12]=='I' && rx[13]=='E')
    {

        quint8 sern1=rx[7];
        quint8 sern2=rx[8];
        int sernum=((sern1<<8)+sern2);
        emit send_battery2_MaintGI_serial_no(sernum);
       // qDebug()<<"Bat 2 GI Serial No received ="<<sernum;

    }

    // General Info Bat 2 - Manufacturing date

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='G' && rx[3]=='I' &&rx[4]=='M' &&
            rx[5]=='D' && rx[6]=='S' && rx[9]=='M' &&rx[10]=='D' &&rx[11]=='G'
            && rx[12]=='I' && rx[13]=='E')
    {
        quint8 mdd1=rx[7];
        quint8 mdd2=rx[8];
        int manuf_date;
        manuf_date=((mdd1<<8)+mdd2);
       // qDebug()<<" Bat 2 GI manuf date received ="<<manuf_date;
        uint16_t date = 0x001F & manuf_date;
        uint16_t month = 0x01E0 & manuf_date;
        month = month >> 5;
        uint16_t year = 0xFE00 & manuf_date;
        year = year>>9;
        year=year+1980;
//        qDebug()<<date;
//        qDebug()<<month;
//        qDebug()<<year;
        emit send_battery2_MaintGI_manuf_date(manuf_date);

    }


    //General Info Bat 2 - cyclecount

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='G' && rx[3]=='I' &&rx[4]=='C' &&
            rx[5]=='C' && rx[6]=='S' && rx[9]=='C' &&rx[10]=='C' &&rx[11]=='G'
            && rx[12]=='I' && rx[13]=='E')
    {
        quint8 ccc1=rx[7];
        quint8 ccc2=rx[8];
        int ccount;
        ccount=((ccc1<<8)+ccc2);
        emit send_battery2_MaintGI_cyclecount(ccount);
        //qDebug()<<" Bat 2 GI cycle count received ="<<ccount;

    }

    //General Info Bat 2 - Remcap
    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='G' && rx[3]=='I' &&rx[4]=='R' &&
            rx[5]=='C' && rx[6]=='S' && rx[9]=='R' &&rx[10]=='C' &&rx[11]=='G'
            && rx[12]=='I' && rx[13]=='E')
    {

        quint8 rcc1=rx[7];
        quint8 rcc2=rx[8];
        int remcapac=((rcc1<<8)+rcc2);
     emit send_battery2_MaintGI_RemCap(remcapac);
        //qDebug()<<" Bat 2 GI Rem Cap received ="<<remcapac;


    }
    //General Info Bat 2 - Temperatue

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='G' && rx[3]=='I' &&rx[4]=='T' &&
            rx[5]=='P' && rx[6]=='S' && rx[9]=='T' &&rx[10]=='P' &&rx[11]=='G'
            && rx[12]=='I' && rx[13]=='E')
    {
                       quint8 temp1=rx[7];
                       quint8 temp2=rx[8];
                       float temperature=((temp1<<8)+temp2);
                       float temperatureGI =static_cast<float>(((temperature/10.0)-273.15));
                      emit send_battery2_MaintGI_temperature(temperature);
                      //  qDebug()<<" Bat 2 GI Temperature received ="<<temperatureGI;

    }

    //General Info Bat 2 - Battery Status

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='G' && rx[3]=='I' &&rx[4]=='B' &&
            rx[5]=='S' && rx[6]=='S' && rx[9]=='B' &&rx[10]=='S' &&rx[11]=='G'
            && rx[12]=='I' && rx[13]=='E')
    {

                        quint8 bs1=rx[7];
                        quint8 bs2=rx[8];
                        int bstatus=((bs1<<8)+bs2);
                        emit send_battery2_MaintGI_batstatus(bstatus);
                      //   qDebug()<<" Bat 2 GI Batstatus received ="<<bstatus;

    }


    // Following are the functions when bat 2 maintenance
    // specific info is received

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='S' && rx[3]=='I' &&rx[4]=='B' &&
            rx[5]=='S' && rx[6]=='S' && rx[9]=='B' &&rx[10]=='S' &&rx[11]=='S'
            && rx[12]=='I' && rx[13]=='E')
    {
        quint8 bs1=rx[7];
        quint8 bs2=rx[8];
        int bstatus=((bs1<<8)+bs2);

        emit send_battery2_Maint_SpecificInfo_batstatus(bstatus);
        //qDebug()<<"\nBat2 status specific info received"<<bstatus;
    }

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='S' && rx[3]=='I' &&rx[4]=='D' &&
            rx[5]=='C' && rx[6]=='S' && rx[9]=='D' &&rx[10]=='C' &&rx[11]=='S'
            && rx[12]=='I' && rx[13]=='E')
    {
        quint8 dc1=rx[7];
        quint8 dc2=rx[8];
        int design_cap=((dc1<<8)+dc2);

    emit send_battery2_Maint_SpecificInfo_designcapacity(design_cap);
   //     qDebug()<<"Bat 2 design capacity specific info received"<<design_cap;
    }

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='S' && rx[3]=='I' &&rx[4]=='F' &&
            rx[5]=='C' && rx[6]=='S' && rx[9]=='F' &&rx[10]=='C' &&rx[11]=='S'
            && rx[12]=='I' && rx[13]=='E')
    {

        quint8 fcc1=rx[7];
        quint8 fcc2=rx[8];
        int fcc=((fcc1<<8)+fcc2);
        emit send_battery2_Maint_SpecificInfo_fullchargecapacity(fcc);

       // qDebug()<<"Bat 2 Full charge specific info received"<<fcc;
    }

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='S' && rx[3]=='I' &&rx[4]=='R' &&
            rx[5]=='T' && rx[6]=='S' && rx[9]=='R' &&rx[10]=='T' &&rx[11]=='F'
            && rx[12]=='I' && rx[13]=='E')
    {

        quint8 rte1=rx[7];
        quint8 rte2=rx[8];
        int rte=((rte1<<8)+rte2);
        emit send_battery2_Maint_SpecificInfo_run_time_to_empty(rte);

      // qDebug()<<"Bat 2 start RTE specific info received="<<QString::number(rte); // Works
    }

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='S' && rx[3]=='I' &&rx[4]=='R' &&
            rx[5]=='T' && rx[6]=='S' && rx[9]=='R' &&rx[10]=='T' &&rx[11]=='L'
            && rx[12]=='I' && rx[13]=='E')
    {

        quint8 rte1=rx[7];
        quint8 rte2=rx[8];
        int rte=((rte1<<8)+rte2);
        emit send_battery2_Maint_SpecificInfo_run_time_to_empty_end_of_discharge(rte);

      // qDebug()<<"Bat2 RTE end specific info received="<<QString::number(rte); // Works
    }


    // Following are the functions when battery 2 Maintenance
    // Autotest results are received

     // Result when bat 2 is charged to 80 % in Maintenance Use Case


    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='R' && rx[3]=='F' &&rx[4]=='8' &&
            rx[5]=='V' && rx[6]=='T' && rx[9]=='V' &&rx[10]=='T' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')  // Result bat 2 F80 Voltage
    {


        quint8 M=0;
        quint8 L=0;
        int v;
        M=rx[7];
        L=rx[8];
        v=((M<<8)+L);
       emit send_battery2_Maint_f80_voltage(v);
     //   qDebug()<<" Bat 2 F80 Voltage  Received="<<v; // This function works
    }

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='R' && rx[3]=='F' &&rx[4]=='8' &&
            rx[5]=='A' && rx[6]=='S' && rx[8]=='A' &&rx[9]=='S' &&rx[10]=='E'
            && rx[11]=='E' && rx[12]=='N' && rx[13]=='D') // Bat 2 Result F80 ASOC
    {

        int asoc;
        asoc=rx[7];
        emit send_battery2_Maint_f80_asoc(asoc);
        //qDebug()<<"Bat 2 F80 Asoc received="<<asoc;


    }

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='R' && rx[3]=='F' &&rx[4]=='8' &&
            rx[5]=='R' && rx[6]=='C' && rx[9]=='R' &&rx[10]=='C' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')     // Bat2 Result F80 Remcap
    {

        quint8 rcc1=rx[7];
        quint8 rcc2=rx[8];
        int remcapac=((rcc1<<8)+rcc2);
        emit send_battery2_Maint_f80_remcap(remcapac);
      //  qDebug()<<" Bat 2 F80 Rem Cap received ="<<remcapac;


    }

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='R' && rx[3]=='F' &&rx[4]=='8' &&
            rx[5]=='C' && rx[6]=='C' && rx[9]=='C' &&rx[10]=='C' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')  // bat2 Result F80 Cycle Count
    {
        quint8 ccc1=rx[7];
        quint8 ccc2=rx[8];
        int ccount;
        ccount=((ccc1<<8)+ccc2);
        emit send_battery2_Maint_f80_cycount(ccount);
        //qDebug()<<" \nBat 2 F80 cycle count received ="<<ccount;

    }


    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='R' && rx[3]=='F' &&rx[4]=='8' &&
            rx[5]=='T' && rx[6]=='P' && rx[9]=='T' &&rx[10]=='P' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')    // Result F80 Temperature
    {
                       quint8 temp1=rx[7];
                       quint8 temp2=rx[8];
                       float temperature=((temp1<<8)+temp2);
                       float temperatureGI =static_cast<float>(((temperature/10.0)-273.15));
                     emit send_battery2_Maint_f80_temperature(temperature);
                       // qDebug()<<" Bat 2 F80 Temperature received ="<<temperatureGI;

    }

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='R' && rx[3]=='F' &&rx[4]=='8' &&
            rx[5]=='B' && rx[6]=='S' && rx[9]=='B' &&rx[10]=='S' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')   // Bat 2 Result F80 Battery Status
    {

                        quint8 bs1=rx[7];
                        quint8 bs2=rx[8];
                        int bstatus=((bs1<<8)+bs2);
                     emit send_battery2_Maint_f80_batstatus(bstatus);
                       //  qDebug()<<" Bat 2 F80  Batstatus received ="<<bstatus;

    }


    // Result when bat 2 is discharged to 10 % in Maintenance Use Case

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='R' && rx[3]=='M' &&rx[4]=='1' &&
            rx[5]=='V' && rx[6]=='T' && rx[9]=='V' &&rx[10]=='T' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')  // bat2 Result M10 Voltage
    {


        quint8 M=0;
        quint8 L=0;
        int v;
        M=rx[7];
        L=rx[8];
        v=((M<<8)+L);
       emit send_battery2_Maint_m10_voltage(v);
      //  qDebug()<<" Bat 2 M10 Voltage  Received="<<v; // This function works
    }

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='R' && rx[3]=='M' &&rx[4]=='1' &&
            rx[5]=='A' && rx[6]=='S' && rx[8]=='A' &&rx[9]=='S' &&rx[10]=='E'
            && rx[11]=='E' && rx[12]=='N' && rx[13]=='D') // bat2 Result M10 ASOC
    {

        int asoc;
        asoc=rx[7];
        emit send_battery2_Maint_m10_asoc(asoc);
       // qDebug()<<"Bat 2 M10 Asoc received="<<asoc;


    }

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='R' && rx[3]=='M' &&rx[4]=='1' &&
            rx[5]=='R' && rx[6]=='C' && rx[9]=='R' &&rx[10]=='C' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')     // bat2 Result M10 Remcap
    {

        quint8 rcc1=rx[7];
        quint8 rcc2=rx[8];
        int remcapac=((rcc1<<8)+rcc2);
       emit send_battery2_Maint_m10_remcap(remcapac);
       // qDebug()<<" Bat 2 M10 Rem Cap received ="<<remcapac;


    }

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='R' && rx[3]=='M' &&rx[4]=='1' &&
            rx[5]=='C' && rx[6]=='C' && rx[9]=='C' &&rx[10]=='C' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')  // bat2 Result M10 Cycle Count
    {
        quint8 ccc1=rx[7];
        quint8 ccc2=rx[8];
        int ccount;
        ccount=((ccc1<<8)+ccc2);
       emit send_battery2_Maint_m10_cycount(ccount);
       // qDebug()<<" \n Bat 2 M10 cycle count received ="<<ccount;

    }


    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='R' && rx[3]=='M' &&rx[4]=='1' &&
            rx[5]=='T' && rx[6]=='P' && rx[9]=='T' &&rx[10]=='P' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')    // Bat 2 Result M10 Temperature
    {
                       quint8 temp1=rx[7];
                       quint8 temp2=rx[8];
                       float temperature=((temp1<<8)+temp2);
                       float temperatureGI =static_cast<float>(((temperature/10.0)-273.15));
                   emit send_battery2_Maint_m10_temperature(temperature);
                      //  qDebug()<<" Bat 2 M10 Temperature received ="<<temperatureGI;

    }

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='R' && rx[3]=='M' &&rx[4]=='1' &&
            rx[5]=='B' && rx[6]=='S' && rx[9]=='B' &&rx[10]=='S' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')   // Bat 2 Result M10 Battery Status
    {

                        quint8 bs1=rx[7];
                        quint8 bs2=rx[8];
                        int bstatus=((bs1<<8)+bs2);
                      emit send_battery2_Maint_m10_batstatus(bstatus);
                       // qDebug()<<" Bat 2 M10  Batstatus received ="<<bstatus;

    }

    // Result when bat 2 is Recharged to 80 % in Maintenance Use Case

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='R' && rx[3]=='L' &&rx[4]=='8' &&
            rx[5]=='V' && rx[6]=='T' && rx[9]=='V' &&rx[10]=='T' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')  // Bat 2 Result L80 Voltage
    {


        quint8 M=0;
        quint8 L=0;
        int v;
        M=rx[7];
        L=rx[8];
        v=((M<<8)+L);
     emit send_battery2_Maint_l80_voltage(v);
      //  qDebug()<<" Bat 2 L80 Voltage  Received="<<v; // This function works
    }

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='R' && rx[3]=='L' &&rx[4]=='8' &&
            rx[5]=='A' && rx[6]=='S' && rx[8]=='A' &&rx[9]=='S' &&rx[10]=='E'
            && rx[11]=='E' && rx[12]=='N' && rx[13]=='D') // Bat 2 Result L80 ASOC
    {

        int asoc;
        asoc=rx[7];
        emit send_battery2_Maint_l80_asoc(asoc);
       // qDebug()<<"Bat 2 L80 Asoc received="<<asoc;


    }

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='R' && rx[3]=='L' &&rx[4]=='8' &&
            rx[5]=='R' && rx[6]=='C' && rx[9]=='R' &&rx[10]=='C' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')     // Bat 2 Result L80 Remcap
    {

        quint8 rcc1=rx[7];
        quint8 rcc2=rx[8];
        int remcapac=((rcc1<<8)+rcc2);
       emit send_battery2_Maint_l80_remcap(remcapac);
       // qDebug()<<" Bat 2 L80 Rem Cap received ="<<remcapac;


    }

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='R' && rx[3]=='L' &&rx[4]=='8' &&
            rx[5]=='C' && rx[6]=='C' && rx[9]=='C' &&rx[10]=='C' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')  // Bat 2 Result L80 Cycle Count
    {
        quint8 ccc1=rx[7];
        quint8 ccc2=rx[8];
        int ccount;
        ccount=((ccc1<<8)+ccc2);
        emit send_battery2_Maint_l80_cycount(ccount);
        //qDebug()<<" \nBat 2 L80 cycle count received ="<<ccount;

    }


    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='R' && rx[3]=='L' &&rx[4]=='8' &&
            rx[5]=='T' && rx[6]=='P' && rx[9]=='T' &&rx[10]=='P' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')    // Result L80 Temperature
    {
                       quint8 temp1=rx[7];
                       quint8 temp2=rx[8];
                       float temperature=((temp1<<8)+temp2);
                       float temperatureGI =static_cast<float>(((temperature/10.0)-273.15));
                       emit send_battery2_Maint_l80_temperature(temperature);
                       // qDebug()<<" Bat 2 L80 Temperature received ="<<temperatureGI;

    }

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='R' && rx[3]=='L' &&rx[4]=='8' &&
            rx[5]=='B' && rx[6]=='S' && rx[9]=='B' &&rx[10]=='S' &&rx[11]=='E'
            && rx[12]=='N' && rx[13]=='D')   // Bat 2 Result L80 Battery Status
    {

                        quint8 bs1=rx[7];
                        quint8 bs2=rx[8];
                        int bstatus=((bs1<<8)+bs2);
                      emit send_battery2_Maint_l80_batstatus(bstatus);
                      //   qDebug()<<" Bat 2 L80  Batstatus received ="<<bstatus;

    }

    // Following are the functions when Bat 2 parameters
    // are updated during the Maintenance Use Case

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='U' &&rx[3]=='P' &&rx[4]=='V'&&
            rx[5]=='T' && rx[6]=='S' && rx[9]=='V' &&rx[10]=='T' &&rx[11]=='U'
            && rx[12]=='P' && rx[13]=='E'  )
    {
        quint8 M=0;
        quint8 L=0;
        int v;
        M=rx[7];
        L=rx[8];
        v=((M<<8)+L);
     emit send_bat2_update_voltage_maint(v);
       // qDebug()<<"Bat2 Updated Voltage  Received="<<v;

    }

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='U' &&rx[3]=='P' &&rx[4]=='A'&&
            rx[5]=='S' && rx[6]=='S' && rx[8]=='A' && rx[9]=='S' &&rx[10]=='E' &&rx[11]=='U'
            && rx[12]=='P' && rx[13]=='E'  )
    {
        int a;
        a=rx[7];
        //  emit asocread(a);
        emit send_bat2_update_asoc_maint(a);
       // qDebug()<<"Bat2 Updated ASOC  Received="<<a;


    }

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='U' &&rx[3]=='P' &&rx[4]=='T'&&
            rx[5]=='P' && rx[6]=='S' && rx[9]=='T' &&rx[10]=='P' &&rx[11]=='U'
            && rx[12]=='P' && rx[13]=='E' )
    {
        quint8 t1=0;
        quint8 t2=0;
        float t=0;
        t1=rx[7];
        t2=rx[8];
        t=static_cast<float>(((t1<<8)+t2));
        t=static_cast<float>(((t/10.0)-273.15));
        emit send_bat2_update_temp_maint(t);
      //  qDebug()<<"Bat2 Updated Temp  Received="<<t;


    }

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='U' &&rx[3]=='P' &&rx[4]=='R'&&
            rx[5]=='C' && rx[6]=='S' && rx[9]=='R' &&rx[10]=='C' &&rx[11]=='U'
            && rx[12]=='P' && rx[13]=='E'   )
    {
        quint8 r1=0;
        quint8 r2=0;
        int r;
        r1=rx[7];
        r2=rx[8];
        r=((r1<<8)+r2);
       emit send_bat2_update_remcap_maint(r);
       // qDebug()<<"Bat2 Updated Remcap  Received="<<r;


    }

    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='U' &&rx[3]=='P' &&rx[4]=='C'&&
            rx[5]=='C' && rx[6]=='S' && rx[9]=='C' &&rx[10]=='C' &&rx[11]=='U'
            && rx[12]=='P' && rx[13]=='E'   )
    {
        quint8 c1=0;
        quint8 c2=0;
        int c;
        c1=rx[7];
        c2=rx[8];
        c=((c1<<8)+c2);
       // qDebug()<<"Bat2 Updated Cyc Count Received="<<c;
       emit send_bat2_update_cyccount_maint(c);
        // memset(rx_array,0,sizeof (rx_array));

    }

    //    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='G' &&rx[3]=='C' &&rx[4]=='R'   )
    //    {
    //        quint8 current1=0;
    //        quint8 current2=0;
    //        int current;
    //        current1=rx[5];
    //        current2=rx[6];
    //        current=((current1<<8)+current2);
    //     //   emit curead(current);
    //        // memset(buf2,0,sizeof (buf2));

    //    }
    if(rx[0]=='2' && rx[1]=='M' && rx[2]=='U' &&rx[3]=='P' &&rx[4]=='B'&&
            rx[5]=='S' && rx[6]=='S' && rx[9]=='B' &&rx[10]=='S' &&rx[11]=='U'
            && rx[12]=='P' && rx[13]=='E'   )
    {
        quint8 bs1=0;
        quint8 bs2=0;
        int bstatus;
        bs1=rx[7];
        bs2=rx[8];
        bstatus=((bs1<<8)+bs2);
        emit send_bat2_update_batstatus_maint(bstatus);

       // qDebug()<<"Bat2 Updated Batstatus Received="<<bstatus;

    }

    // Following are the functions that receive bat 3 maintenance
    // general information


     // General Info Bat 3 - Voltage

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='G' && rx[3]=='I' &&rx[4]=='V' &&
             rx[5]=='T' && rx[6]=='S' && rx[9]=='V' &&rx[10]=='T' &&rx[11]=='G'
             && rx[12]=='I' && rx[13]=='E')
     {

         //  qDebug()<<"Entered voltage function recent";
         quint8 M=0;
         quint8 L=0;
         int v;
         M=rx[7];
         L=rx[8];
         v=((M<<8)+L);
      // emit send_battery1_MaintGI_voltage(v);
         qDebug()<<"Bat 3 GI Voltage  Received="<<v; // This function works
     }

     // General Info Bat 3 - asoc

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='G' && rx[3]=='I' &&rx[4]=='A' &&
             rx[5]=='S' && rx[6]=='S' && rx[8]=='A' &&rx[9]=='S' &&rx[10]=='E'
             && rx[11]=='G' && rx[12]=='I' && rx[13]=='E')
     {

         int asoc;
         asoc=rx[7];
      //   emit send_battery1_MaintGI_asoc(asoc);
         qDebug()<<"Bat 3 GI Asoc received="<<asoc;


     }


     // General Info Bat 3 - Serial No

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='G' && rx[3]=='I' &&rx[4]=='S' &&
             rx[5]=='N' && rx[6]=='S' && rx[9]=='S' &&rx[10]=='N' &&rx[11]=='G'
             && rx[12]=='I' && rx[13]=='E')
     {

         quint8 sern1=rx[7];
         quint8 sern2=rx[8];
         int sernum=((sern1<<8)+sern2);
        // emit send_battery1_MaintGI_serial_no(sernum);
         qDebug()<<"Bat 3 GI Serial No received ="<<sernum;

     }

     // General Info Bat 3 - Manufacturing date

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='G' && rx[3]=='I' &&rx[4]=='M' &&
             rx[5]=='D' && rx[6]=='S' && rx[9]=='M' &&rx[10]=='D' &&rx[11]=='G'
             && rx[12]=='I' && rx[13]=='E')
     {
         quint8 mdd1=rx[7];
         quint8 mdd2=rx[8];
         int manuf_date;
         manuf_date=((mdd1<<8)+mdd2);
         qDebug()<<" Bat 3 GI manuf date received ="<<manuf_date;
         uint16_t date = 0x001F & manuf_date;
         uint16_t month = 0x01E0 & manuf_date;
         month = month >> 5;
         uint16_t year = 0xFE00 & manuf_date;
         year = year>>9;
         year=year+1980;
         qDebug()<<date;
         qDebug()<<month;
         qDebug()<<year;
        // emit send_battery1_MaintGI_manuf_date(manuf_date);

     }


     //General Info Bat 3 - cyclecount

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='G' && rx[3]=='I' &&rx[4]=='C' &&
             rx[5]=='C' && rx[6]=='S' && rx[9]=='C' &&rx[10]=='C' &&rx[11]=='G'
             && rx[12]=='I' && rx[13]=='E')
     {
         quint8 ccc1=rx[7];
         quint8 ccc2=rx[8];
         int ccount;
         ccount=((ccc1<<8)+ccc2);
        // emit send_battery1_MaintGI_cyclecount(ccount);
         qDebug()<<" Bat 3 GI cycle count received ="<<ccount;

     }

     //General Info Bat 3 - Remcap
     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='G' && rx[3]=='I' &&rx[4]=='R' &&
             rx[5]=='C' && rx[6]=='S' && rx[9]=='R' &&rx[10]=='C' &&rx[11]=='G'
             && rx[12]=='I' && rx[13]=='E')
     {

         quint8 rcc1=rx[7];
         quint8 rcc2=rx[8];
         int remcapac=((rcc1<<8)+rcc2);
      //   emit send_battery1_MaintGI_RemCap(remcapac);
         qDebug()<<" Bat 3 GI Rem Cap received ="<<remcapac;


     }
     //General Info Bat 3 - Temperatue

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='G' && rx[3]=='I' &&rx[4]=='T' &&
             rx[5]=='P' && rx[6]=='S' && rx[9]=='T' &&rx[10]=='P' &&rx[11]=='G'
             && rx[12]=='I' && rx[13]=='E')
     {
                        quint8 temp1=rx[7];
                        quint8 temp2=rx[8];
                        float temperature=((temp1<<8)+temp2);
                        float temperatureGI =static_cast<float>(((temperature/10.0)-273.15));
                      //  emit send_battery1_MaintGI_temperature(temperature);
                         qDebug()<<" Bat 3 GI Temperature received ="<<temperatureGI;

     }

     //General Info Bat 3 - Battery Status

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='G' && rx[3]=='I' &&rx[4]=='B' &&
             rx[5]=='S' && rx[6]=='S' && rx[9]=='B' &&rx[10]=='S' &&rx[11]=='G'
             && rx[12]=='I' && rx[13]=='E')
     {

                         quint8 bs1=rx[7];
                         quint8 bs2=rx[8];
                         int bstatus=((bs1<<8)+bs2);
                       //  emit send_battery1_MaintGI_batstatus(bstatus);
                          qDebug()<<" Bat 3 GI Batstatus received ="<<bstatus;

     }

     // Following are the functions when bat 3 maintenance
     // specific info is received

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='S' && rx[3]=='I' &&rx[4]=='B' &&
             rx[5]=='S' && rx[6]=='S' && rx[9]=='B' &&rx[10]=='S' &&rx[11]=='S'
             && rx[12]=='I' && rx[13]=='E')
     {
         quint8 bs1=rx[7];
         quint8 bs2=rx[8];
         int bstatus=((bs1<<8)+bs2);

         //emit send_battery1_Maint_SpecificInfo_batstatus(bstatus);
         qDebug()<<"\nBat3 status specific info received"<<bstatus;
     }

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='S' && rx[3]=='I' &&rx[4]=='D' &&
             rx[5]=='C' && rx[6]=='S' && rx[9]=='D' &&rx[10]=='C' &&rx[11]=='S'
             && rx[12]=='I' && rx[13]=='E')
     {
         quint8 dc1=rx[7];
         quint8 dc2=rx[8];
         int design_cap=((dc1<<8)+dc2);

    // emit send_battery1_Maint_SpecificInfo_designcapacity(design_cap);
         qDebug()<<"Bat 3 design capacity specific info received"<<design_cap;
     }

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='S' && rx[3]=='I' &&rx[4]=='F' &&
             rx[5]=='C' && rx[6]=='S' && rx[9]=='F' &&rx[10]=='C' &&rx[11]=='S'
             && rx[12]=='I' && rx[13]=='E')
     {

         quint8 fcc1=rx[7];
         quint8 fcc2=rx[8];
         int fcc=((fcc1<<8)+fcc2);
        // emit send_battery1_Maint_SpecificInfo_fullchargecapacity(fcc);

         qDebug()<<"Bat 3 Full charge specific info received"<<fcc;
     }

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='S' && rx[3]=='I' &&rx[4]=='R' &&
             rx[5]=='T' && rx[6]=='S' && rx[9]=='R' &&rx[10]=='T' &&rx[11]=='F'
             && rx[12]=='I' && rx[13]=='E')
     {

         quint8 rte1=rx[7];
         quint8 rte2=rx[8];
         int rte=((rte1<<8)+rte2);
       //  emit send_battery1_Maint_SpecificInfo_run_time_to_empty(rte);

        qDebug()<<"Bat 3 start RTE specific info received="<<QString::number(rte); // Works
     }

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='S' && rx[3]=='I' &&rx[4]=='R' &&
             rx[5]=='T' && rx[6]=='S' && rx[9]=='R' &&rx[10]=='T' &&rx[11]=='L'
             && rx[12]=='I' && rx[13]=='E')
     {

         quint8 rte1=rx[7];
         quint8 rte2=rx[8];
         int rte=((rte1<<8)+rte2);
       //  emit send_battery1_Maint_SpecificInfo_run_time_to_empty_end_of_discharge(rte);

        qDebug()<<"Bat3 RTE end specific info received="<<QString::number(rte); // Works
     }


     // Following are the functions when battery 3 Maintenance
     // Autotest results are received

      // Result when bat 3 is charged to 80 % in Maintenance Use Case


     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='R' && rx[3]=='F' &&rx[4]=='8' &&
             rx[5]=='V' && rx[6]=='T' && rx[9]=='V' &&rx[10]=='T' &&rx[11]=='E'
             && rx[12]=='N' && rx[13]=='D')  // Result bat 3 F80 Voltage
     {


         quint8 M=0;
         quint8 L=0;
         int v;
         M=rx[7];
         L=rx[8];
         v=((M<<8)+L);
      //  emit send_battery1_Maint_f80_voltage(v);
         qDebug()<<" Bat 3 F80 Voltage  Received="<<v; // This function works
     }

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='R' && rx[3]=='F' &&rx[4]=='8' &&
             rx[5]=='A' && rx[6]=='S' && rx[8]=='A' &&rx[9]=='S' &&rx[10]=='E'
             && rx[11]=='E' && rx[12]=='N' && rx[13]=='D') // Bat 3 Result F80 ASOC
     {

         int asoc;
         asoc=rx[7];
         //emit send_battery1_Maint_f80_asoc(asoc);
         qDebug()<<"Bat 3 F80 Asoc received="<<asoc;


     }

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='R' && rx[3]=='F' &&rx[4]=='8' &&
             rx[5]=='R' && rx[6]=='C' && rx[9]=='R' &&rx[10]=='C' &&rx[11]=='E'
             && rx[12]=='N' && rx[13]=='D')     // Bat3 Result F80 Remcap
     {

         quint8 rcc1=rx[7];
         quint8 rcc2=rx[8];
         int remcapac=((rcc1<<8)+rcc2);
       //  emit send_battery1_Maint_f80_remcap(remcapac);
         qDebug()<<" Bat 3 F80 Rem Cap received ="<<remcapac;


     }

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='R' && rx[3]=='F' &&rx[4]=='8' &&
             rx[5]=='C' && rx[6]=='C' && rx[9]=='C' &&rx[10]=='C' &&rx[11]=='E'
             && rx[12]=='N' && rx[13]=='D')  // bat3 Result F80 Cycle Count
     {
         quint8 ccc1=rx[7];
         quint8 ccc2=rx[8];
         int ccount;
         ccount=((ccc1<<8)+ccc2);
       //  emit send_battery1_Maint_f80_cycount(ccount);
         qDebug()<<" \nBat 3 F80 cycle count received ="<<ccount;

     }


     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='R' && rx[3]=='F' &&rx[4]=='8' &&
             rx[5]=='T' && rx[6]=='P' && rx[9]=='T' &&rx[10]=='P' &&rx[11]=='E'
             && rx[12]=='N' && rx[13]=='D')    // Result F80 Temperature
     {
                        quint8 temp1=rx[7];
                        quint8 temp2=rx[8];
                        float temperature=((temp1<<8)+temp2);
                        float temperatureGI =static_cast<float>(((temperature/10.0)-273.15));
                      //  emit send_battery1_Maint_f80_temperature(temperature);
                         qDebug()<<" Bat 3 F80 Temperature received ="<<temperatureGI;

     }

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='R' && rx[3]=='F' &&rx[4]=='8' &&
             rx[5]=='B' && rx[6]=='S' && rx[9]=='B' &&rx[10]=='S' &&rx[11]=='E'
             && rx[12]=='N' && rx[13]=='D')   // Bat 3 Result F80 Battery Status
     {

                         quint8 bs1=rx[7];
                         quint8 bs2=rx[8];
                         int bstatus=((bs1<<8)+bs2);
                       //  emit send_battery1_Maint_f80_batstatus(bstatus);
                          qDebug()<<" Bat 3 F80  Batstatus received ="<<bstatus;

     }

     // Result when bat 3 is discharged to 10 % in Maintenance Use Case

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='R' && rx[3]=='M' &&rx[4]=='1' &&
             rx[5]=='V' && rx[6]=='T' && rx[9]=='V' &&rx[10]=='T' &&rx[11]=='E'
             && rx[12]=='N' && rx[13]=='D')  // bat3 Result M10 Voltage
     {


         quint8 M=0;
         quint8 L=0;
         int v;
         M=rx[7];
         L=rx[8];
         v=((M<<8)+L);
       // emit send_battery1_Maint_m10_voltage(v);
         qDebug()<<" Bat 3 M10 Voltage  Received="<<v; // This function works
     }

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='R' && rx[3]=='M' &&rx[4]=='1' &&
             rx[5]=='A' && rx[6]=='S' && rx[8]=='A' &&rx[9]=='S' &&rx[10]=='E'
             && rx[11]=='E' && rx[12]=='N' && rx[13]=='D') // bat3 Result M10 ASOC
     {

         int asoc;
         asoc=rx[7];
        // emit send_battery1_Maint_m10_asoc(asoc);
         qDebug()<<"Bat 3 M10 Asoc received="<<asoc;


     }

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='R' && rx[3]=='M' &&rx[4]=='1' &&
             rx[5]=='R' && rx[6]=='C' && rx[9]=='R' &&rx[10]=='C' &&rx[11]=='E'
             && rx[12]=='N' && rx[13]=='D')     // bat3 Result M10 Remcap
     {

         quint8 rcc1=rx[7];
         quint8 rcc2=rx[8];
         int remcapac=((rcc1<<8)+rcc2);
        // emit send_battery1_Maint_m10_remcap(remcapac);
         qDebug()<<" Bat 3 M10 Rem Cap received ="<<remcapac;


     }

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='R' && rx[3]=='M' &&rx[4]=='1' &&
             rx[5]=='C' && rx[6]=='C' && rx[9]=='C' &&rx[10]=='C' &&rx[11]=='E'
             && rx[12]=='N' && rx[13]=='D')  // bat3 Result M10 Cycle Count
     {
         quint8 ccc1=rx[7];
         quint8 ccc2=rx[8];
         int ccount;
         ccount=((ccc1<<8)+ccc2);
        // emit send_battery1_Maint_m10_cycount(ccount);
         qDebug()<<" \n Bat 3 M10 cycle count received ="<<ccount;

     }


     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='R' && rx[3]=='M' &&rx[4]=='1' &&
             rx[5]=='T' && rx[6]=='P' && rx[9]=='T' &&rx[10]=='P' &&rx[11]=='E'
             && rx[12]=='N' && rx[13]=='D')    // Bat 3 Result M10 Temperature
     {
                        quint8 temp1=rx[7];
                        quint8 temp2=rx[8];
                        float temperature=((temp1<<8)+temp2);
                        float temperatureGI =static_cast<float>(((temperature/10.0)-273.15));
                     //   emit send_battery1_Maint_m10_temperature(temperature);
                         qDebug()<<" Bat 3 M10 Temperature received ="<<temperatureGI;

     }

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='R' && rx[3]=='M' &&rx[4]=='1' &&
             rx[5]=='B' && rx[6]=='S' && rx[9]=='B' &&rx[10]=='S' &&rx[11]=='E'
             && rx[12]=='N' && rx[13]=='D')   // Bat 3 Result M10 Battery Status
     {

                         quint8 bs1=rx[7];
                         quint8 bs2=rx[8];
                         int bstatus=((bs1<<8)+bs2);
                       //  emit send_battery1_Maint_m10_batstatus(bstatus);
                         qDebug()<<" Bat3 M10  Batstatus received ="<<bstatus;

     }

     // Result when bat 3 is Recharged to 80 % in Maintenance Use Case

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='R' && rx[3]=='L' &&rx[4]=='8' &&
             rx[5]=='V' && rx[6]=='T' && rx[9]=='V' &&rx[10]=='T' &&rx[11]=='E'
             && rx[12]=='N' && rx[13]=='D')  // Bat 3 Result L80 Voltage
     {


         quint8 M=0;
         quint8 L=0;
         int v;
         M=rx[7];
         L=rx[8];
         v=((M<<8)+L);
      //  emit send_battery1_Maint_l80_voltage(v);
         qDebug()<<" Bat 3 L80 Voltage  Received="<<v; // This function works
     }

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='R' && rx[3]=='L' &&rx[4]=='8' &&
             rx[5]=='A' && rx[6]=='S' && rx[8]=='A' &&rx[9]=='S' &&rx[10]=='E'
             && rx[11]=='E' && rx[12]=='N' && rx[13]=='D') // Bat 3 Result L80 ASOC
     {

         int asoc;
         asoc=rx[7];
        // emit send_battery1_Maint_l80_asoc(asoc);
         qDebug()<<"Bat 3 L80 Asoc received="<<asoc;


     }

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='R' && rx[3]=='L' &&rx[4]=='8' &&
             rx[5]=='R' && rx[6]=='C' && rx[9]=='R' &&rx[10]=='C' &&rx[11]=='E'
             && rx[12]=='N' && rx[13]=='D')     // Bat 3 Result L80 Remcap
     {

         quint8 rcc1=rx[7];
         quint8 rcc2=rx[8];
         int remcapac=((rcc1<<8)+rcc2);
        // emit send_battery1_Maint_l80_remcap(remcapac);
         qDebug()<<" Bat 3 L80 Rem Cap received ="<<remcapac;


     }

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='R' && rx[3]=='L' &&rx[4]=='8' &&
             rx[5]=='C' && rx[6]=='C' && rx[9]=='C' &&rx[10]=='C' &&rx[11]=='E'
             && rx[12]=='N' && rx[13]=='D')  // Bat 3 Result L80 Cycle Count
     {
         quint8 ccc1=rx[7];
         quint8 ccc2=rx[8];
         int ccount;
         ccount=((ccc1<<8)+ccc2);
         //emit send_battery1_Maint_l80_cycount(ccount);
         qDebug()<<" \nBat 3 L80 cycle count received ="<<ccount;

     }


     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='R' && rx[3]=='L' &&rx[4]=='8' &&
             rx[5]=='T' && rx[6]=='P' && rx[9]=='T' &&rx[10]=='P' &&rx[11]=='E'
             && rx[12]=='N' && rx[13]=='D')    // Result L80 Temperature
     {
                        quint8 temp1=rx[7];
                        quint8 temp2=rx[8];
                        float temperature=((temp1<<8)+temp2);
                        float temperatureGI =static_cast<float>(((temperature/10.0)-273.15));
                    //    emit send_battery1_Maint_l80_temperature(temperature);
                         qDebug()<<" Bat 3 L80 Temperature received ="<<temperatureGI;

     }

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='R' && rx[3]=='L' &&rx[4]=='8' &&
             rx[5]=='B' && rx[6]=='S' && rx[9]=='B' &&rx[10]=='S' &&rx[11]=='E'
             && rx[12]=='N' && rx[13]=='D')   // Bat 3 Result L80 Battery Status
     {

                         quint8 bs1=rx[7];
                         quint8 bs2=rx[8];
                         int bstatus=((bs1<<8)+bs2);
                        // emit send_battery1_Maint_l80_batstatus(bstatus);
                          qDebug()<<" Bat 3 L80  Batstatus received ="<<bstatus;

     }

     // Following are the functions when Bat 3 parameters
     // are updated during the Maintenance Use Case

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='U' &&rx[3]=='P' &&rx[4]=='V'&&
             rx[5]=='T' && rx[6]=='S' && rx[9]=='V' &&rx[10]=='T' &&rx[11]=='U'
             && rx[12]=='P' && rx[13]=='E'  )
     {
         quint8 M=0;
         quint8 L=0;
         int v;
         M=rx[7];
         L=rx[8];
         v=((M<<8)+L);
       //  emit send_bat1_update_voltage_maint(v);
         qDebug()<<"Bat3 Updated Voltage  Received="<<v;

     }

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='U' &&rx[3]=='P' &&rx[4]=='A'&&
             rx[5]=='S' && rx[6]=='S' && rx[8]=='A' && rx[9]=='S' &&rx[10]=='E' &&rx[11]=='U'
             && rx[12]=='P' && rx[13]=='E'  )
     {
         int a;
         a=rx[7];
         //  emit asocread(a);
         //emit send_bat1_update_asoc_maint(a);
         qDebug()<<"Bat3 Updated ASOC  Received="<<a;


     }

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='U' &&rx[3]=='P' &&rx[4]=='T'&&
             rx[5]=='P' && rx[6]=='S' && rx[9]=='T' &&rx[10]=='P' &&rx[11]=='U'
             && rx[12]=='P' && rx[13]=='E' )
     {
         quint8 t1=0;
         quint8 t2=0;
         float t=0;
         t1=rx[7];
         t2=rx[8];
         t=static_cast<float>(((t1<<8)+t2));
         t=static_cast<float>(((t/10.0)-273.15));
        // emit send_bat1_update_temp_maint(t);
         qDebug()<<"Bat3 Updated Temp  Received="<<t;


     }

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='U' &&rx[3]=='P' &&rx[4]=='R'&&
             rx[5]=='C' && rx[6]=='S' && rx[9]=='R' &&rx[10]=='C' &&rx[11]=='U'
             && rx[12]=='P' && rx[13]=='E'   )
     {
         quint8 r1=0;
         quint8 r2=0;
         int r;
         r1=rx[7];
         r2=rx[8];
         r=((r1<<8)+r2);
        // emit send_bat1_update_remcap_maint(r);
         qDebug()<<"Bat3 Updated Remcap  Received="<<r;


     }

     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='U' &&rx[3]=='P' &&rx[4]=='C'&&
             rx[5]=='C' && rx[6]=='S' && rx[9]=='C' &&rx[10]=='C' &&rx[11]=='U'
             && rx[12]=='P' && rx[13]=='E'   )
     {
         quint8 c1=0;
         quint8 c2=0;
         int c;
         c1=rx[7];
         c2=rx[8];
         c=((c1<<8)+c2);
         qDebug()<<"Bat3 Updated Cyc Count Received="<<c;
     //    emit send_bat1_update_cyccount_maint(c);
         // memset(rx_array,0,sizeof (rx_array));

     }

     //    if(rx[0]=='1' && rx[1]=='M' && rx[2]=='G' &&rx[3]=='C' &&rx[4]=='R'   )
     //    {
     //        quint8 current1=0;
     //        quint8 current2=0;
     //        int current;
     //        current1=rx[5];
     //        current2=rx[6];
     //        current=((current1<<8)+current2);
     //     //   emit curead(current);
     //        // memset(buf2,0,sizeof (buf2));

     //    }
     if(rx[0]=='3' && rx[1]=='M' && rx[2]=='U' &&rx[3]=='P' &&rx[4]=='B'&&
             rx[5]=='S' && rx[6]=='S' && rx[9]=='B' &&rx[10]=='S' &&rx[11]=='U'
             && rx[12]=='P' && rx[13]=='E'   )
     {
         quint8 bs1=0;
         quint8 bs2=0;
         int bstatus;
         bs1=rx[7];
         bs2=rx[8];
         bstatus=((bs1<<8)+bs2);
       //  emit send_bat1_update_batstatus_maint(bstatus);

         qDebug()<<"Bat3 Updated Batstatus Received="<<bstatus;

     }


}




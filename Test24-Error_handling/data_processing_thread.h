#ifndef DATA_PROCESSING_THREAD_H
#define DATA_PROCESSING_THREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QtSerialPort>

class data_process : public QObject
{
    Q_OBJECT

public:
    explicit data_process(QObject *parent = nullptr);
    void delay(int millisecondsWait);


signals:
    // Following are the signals to update bat 1 maint parameters periodically
    void send_bat1_update_voltage_maint(int);    // during maintenance use case at specific intervals
    void send_bat1_update_asoc_maint(int);
    void send_bat1_update_temp_maint(float);
    void send_bat1_update_cyccount_maint(int);
    void send_bat1_update_remcap_maint(int);
    // void curead(int);
    void send_bat1_update_batstatus_maint(int);


    // Following are the signals to update Bat 1 General Info on GUI
    // during maintenance process

    void send_battery1_MaintGI_serial_no(int);
    void send_battery1_MaintGI_manuf_date(int);
    void send_battery1_MaintGI_cyclecount(int);
    void send_battery1_MaintGI_RemCap(int);
    void send_battery1_MaintGI_asoc(int);
    void send_battery1_MaintGI_voltage(int);
    void send_battery1_MaintGI_temperature(float);
    void send_battery1_MaintGI_batstatus(int);


    // Following are the signals to update Bat 1 Specific Info on GUI
    // during maintenance process

    void send_battery1_Maint_SpecificInfo_batstatus(int);
    void send_battery1_Maint_SpecificInfo_fullchargecapacity(int);
    void send_battery1_Maint_SpecificInfo_designcapacity(int);
    void send_battery1_Maint_SpecificInfo_run_time_to_empty(int);
    void send_battery1_Maint_SpecificInfo_run_time_to_empty_end_of_discharge(int);

    // Following are the signals to display Bat 1 Maintenance Use Case Results on GUI
    void send_battery1_Maint_f80_voltage(int);
    void send_battery1_Maint_f80_asoc(int);
    void send_battery1_Maint_f80_remcap(int);
    void send_battery1_Maint_f80_cycount(int);
    void send_battery1_Maint_f80_batstatus(int);
    void send_battery1_Maint_f80_temperature(float);

    void send_battery1_Maint_m10_voltage(int);
    void send_battery1_Maint_m10_asoc(int);
    void send_battery1_Maint_m10_remcap(int);
    void send_battery1_Maint_m10_cycount(int);
    void send_battery1_Maint_m10_batstatus(int);
    void send_battery1_Maint_m10_temperature(float);

    void send_battery1_Maint_l80_voltage(int);
    void send_battery1_Maint_l80_asoc(int);
    void send_battery1_Maint_l80_remcap(int);
    void send_battery1_Maint_l80_cycount(int);
    void send_battery1_Maint_l80_batstatus(int);
    void send_battery1_Maint_l80_temperature(float);


    // Following are the signals to update bat 2 maint parameters periodically
    void send_bat2_update_voltage_maint(int);    // during maintenance use case at specific intervals
    void send_bat2_update_asoc_maint(int);
    void send_bat2_update_temp_maint(float);
    void send_bat2_update_cyccount_maint(int);
    void send_bat2_update_remcap_maint(int);
    // void curead(int);
    void send_bat2_update_batstatus_maint(int);

    // Following are the signals to update Bat 2 General Info on GUI
    // during maintenance process

    void send_battery2_MaintGI_serial_no(int);
    void send_battery2_MaintGI_manuf_date(int);
    void send_battery2_MaintGI_cyclecount(int);
    void send_battery2_MaintGI_RemCap(int);
    void send_battery2_MaintGI_asoc(int);
    void send_battery2_MaintGI_voltage(int);
    void send_battery2_MaintGI_temperature(float);
    void send_battery2_MaintGI_batstatus(int);

    // Following are the signals to update Bat 2 Specific Info on GUI
    // during maintenance process

    void send_battery2_Maint_SpecificInfo_batstatus(int);
    void send_battery2_Maint_SpecificInfo_fullchargecapacity(int);
    void send_battery2_Maint_SpecificInfo_designcapacity(int);
    void send_battery2_Maint_SpecificInfo_run_time_to_empty(int);
    void send_battery2_Maint_SpecificInfo_run_time_to_empty_end_of_discharge(int);

    // Following are the signals to display Bat 2 Maintenance Use Case Results on GUI
    void send_battery2_Maint_f80_voltage(int);
    void send_battery2_Maint_f80_asoc(int);
    void send_battery2_Maint_f80_remcap(int);
    void send_battery2_Maint_f80_cycount(int);
    void send_battery2_Maint_f80_batstatus(int);
    void send_battery2_Maint_f80_temperature(float);

    void send_battery2_Maint_m10_voltage(int);
    void send_battery2_Maint_m10_asoc(int);
    void send_battery2_Maint_m10_remcap(int);
    void send_battery2_Maint_m10_cycount(int);
    void send_battery2_Maint_m10_batstatus(int);
    void send_battery2_Maint_m10_temperature(float);

    void send_battery2_Maint_l80_voltage(int);
    void send_battery2_Maint_l80_asoc(int);
    void send_battery2_Maint_l80_remcap(int);
    void send_battery2_Maint_l80_cycount(int);
    void send_battery2_Maint_l80_batstatus(int);
    void send_battery2_Maint_l80_temperature(float);


    // Following are the signals to update bat 3 maint parameters periodically
    void send_bat3_update_voltage_maint(int);    // during maintenance use case at specific intervals
    void send_bat3_update_asoc_maint(int);
    void send_bat3_update_temp_maint(float);
    void send_bat3_update_cyccount_maint(int);
    void send_bat3_update_remcap_maint(int);
    // void curead(int);
    void send_bat3_update_batstatus_maint(int);

    // Following are the signals to update Bat 3 General Info on GUI
    // during maintenance process

    void send_battery3_MaintGI_serial_no(int);
    void send_battery3_MaintGI_manuf_date(int);
    void send_battery3_MaintGI_cyclecount(int);
    void send_battery3_MaintGI_RemCap(int);
    void send_battery3_MaintGI_asoc(int);
    void send_battery3_MaintGI_voltage(int);
    void send_battery3_MaintGI_temperature(float);
    void send_battery3_MaintGI_batstatus(int);

    // Following are the signals to update Bat 3 Specific Info on GUI
    // during maintenance process

    void send_battery3_Maint_SpecificInfo_batstatus(int);
    void send_battery3_Maint_SpecificInfo_fullchargecapacity(int);
    void send_battery3_Maint_SpecificInfo_designcapacity(int);
    void send_battery3_Maint_SpecificInfo_run_time_to_empty(int);
    void send_battery3_Maint_SpecificInfo_run_time_to_empty_end_of_discharge(int);

    // Following are the signals to display Bat 3 Maintenance Use Case Results on GUI
    void send_battery3_Maint_f80_voltage(int);
    void send_battery3_Maint_f80_asoc(int);
    void send_battery3_Maint_f80_remcap(int);
    void send_battery3_Maint_f80_cycount(int);
    void send_battery3_Maint_f80_batstatus(int);
    void send_battery3_Maint_f80_temperature(float);

    void send_battery3_Maint_m10_voltage(int);
    void send_battery3_Maint_m10_asoc(int);
    void send_battery3_Maint_m10_remcap(int);
    void send_battery3_Maint_m10_cycount(int);
    void send_battery3_Maint_m10_batstatus(int);
    void send_battery3_Maint_m10_temperature(float);

    void send_battery3_Maint_l80_voltage(int);
    void send_battery3_Maint_l80_asoc(int);
    void send_battery3_Maint_l80_remcap(int);
    void send_battery3_Maint_l80_cycount(int);
    void send_battery3_Maint_l80_batstatus(int);
    void send_battery3_Maint_l80_temperature(float);




public slots:

    void data_from_worker(QByteArray);

};

#endif // DATA_PROCESSING_THREAD_H

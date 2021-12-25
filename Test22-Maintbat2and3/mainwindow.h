#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QWidget>
#include <QSize>
#include <QPushButton>

#include <QThread>
#include "worker.h"
#include "data_processing_thread.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QThread *thread1;  // Thread to read the data
    Worker *worker;

    QThread *thread2;  // Thread to Process the data
    data_process *process;



private slots:


    void on_close_btn_clicked();

    void on_pushButton_clicked();

    void on_minimize_btn_clicked();

    void on_left_toggle_menu_btn_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_0_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_Maintenance_clicked();

    void on_Bat1EnterMaint_button_clicked();

        void on_Bat1_Star_Auto_Test_Button_clicked();

        void on_Bat1_Maint_GI_Button_clicked();

        void on_Bat1_Maint_See_Autotestresults_clicked();

        void on_pushButton_maint_bat1_BacktoMaint_clicked();

        void on_Test_report_bat1_button_clicked();

public slots:

    void delay(int millisecondsWait);

    void bat1_update_voltage_maint_read(int);
    void bat1_update_asoc_maint_read(int);
    void bat1_update_temp_maint_read(float);
    void bat1_update_cyclecount_maint_read(int);
    void bat1_update_remcap_maint_read(int);
    //    void oncuread(int);
    void bat1_update_batstatus_maint_read(int);



    // Following are the slots when Bat1 General Info (GI) is received during Maintenance Use Case



     void Receive_battery1_MaintGI_serial_no(int);
     void Receive_battery1_MaintGI_manuf_date(int);
     void Receive_battery1_MaintGI_cyclecount(int);
     void Receive_battery1_MaintGI_RemCap(int);
     void Receive_battery1_MaintGI_asoc(int);
     void Receive_battery1_MaintGI_voltage(int);
     void Receive_battery1_MaintGI_temperature(float);
     void Receive_battery1_MaintGI_batstatus(int);


  // Following are the slots when Bat1 Specific Info is received during Maintenance Use Case

void Receive_battery1_Maint_SpecificInfo_batstatus(int);
void Receive_battery1_Maint_SpecificInfo_fullchargecapacity(int);
void Receive_battery1_Maint_SpecificInfo_designcapacity(int);
void Receive_battery1_Maint_SpecificInfo_run_time_to_empty(int);
void Receive_battery1_Maint_SpecificInfo_run_time_to_empty_end_of_discharge(int);

 // Following are the slots to dislplay Bat 1 Maintenance Use Case Results on GUI
void Receive_battery1_Maint_f80_voltage(int);
void Receive_battery1_Maint_f80_asoc(int);
void Receive_battery1_Maint_f80_remcap(int);
void Receive_battery1_Maint_f80_cycount(int);
void Receive_battery1_Maint_f80_batstatus(int);
void Receive_battery1_Maint_f80_temperature(float);

void Receive_battery1_Maint_m10_voltage(int);
void Receive_battery1_Maint_m10_asoc(int);
void Receive_battery1_Maint_m10_remcap(int);
void Receive_battery1_Maint_m10_cycount(int);
void Receive_battery1_Maint_m10_batstatus(int);
void Receive_battery1_Maint_m10_temperature(float);

void Receive_battery1_Maint_l80_voltage(int);
void Receive_battery1_Maint_l80_asoc(int);
void Receive_battery1_Maint_l80_remcap(int);
void Receive_battery1_Maint_l80_cycount(int);
void Receive_battery1_Maint_l80_batstatus(int);
void Receive_battery1_Maint_l80_temperature(float);


// Functions to Interpret the Results of Maintenance Use Case
void Battery1_Result_Maint_Interpret_Voltage();
void Battery1_Result_Maint_Interpret_Temperature();
void Battery1_Result_Maint_Interpret_CycleCount();
void Battery1_Result_Maint_Interpret_Remaining_capacity();
void Battery1_Result_Maint_Interpret_asoc();
void Battery1_Result_Maint_Interpret_battery_status();

// Function to Interpret Bat 1 Maintenance Use case Specific Info - Run time to empty
void Battery1_Maint_Specific_Info_Interpret_RTE();



// Following are the slots when Bat2 General Info (GI) is received during Maintenance Use Case



 void Receive_battery2_MaintGI_serial_no(int);
 void Receive_battery2_MaintGI_manuf_date(int);
 void Receive_battery2_MaintGI_cyclecount(int);
 void Receive_battery2_MaintGI_RemCap(int);
 void Receive_battery2_MaintGI_asoc(int);
 void Receive_battery2_MaintGI_voltage(int);
 void Receive_battery2_MaintGI_temperature(float);
 void Receive_battery2_MaintGI_batstatus(int);

 // Following are the slots when Bat2 Specific Info is received during Maintenance Use Case

void Receive_battery2_Maint_SpecificInfo_batstatus(int);
void Receive_battery2_Maint_SpecificInfo_fullchargecapacity(int);
void Receive_battery2_Maint_SpecificInfo_designcapacity(int);
void Receive_battery2_Maint_SpecificInfo_run_time_to_empty(int);
void Receive_battery2_Maint_SpecificInfo_run_time_to_empty_end_of_discharge(int);

// Following are the slots to dislplay Bat 2 Maintenance Use Case Results on GUI
void Receive_battery2_Maint_f80_voltage(int);
void Receive_battery2_Maint_f80_asoc(int);
void Receive_battery2_Maint_f80_remcap(int);
void Receive_battery2_Maint_f80_cycount(int);
void Receive_battery2_Maint_f80_batstatus(int);
void Receive_battery2_Maint_f80_temperature(float);

void Receive_battery2_Maint_m10_voltage(int);
void Receive_battery2_Maint_m10_asoc(int);
void Receive_battery2_Maint_m10_remcap(int);
void Receive_battery2_Maint_m10_cycount(int);
void Receive_battery2_Maint_m10_batstatus(int);
void Receive_battery2_Maint_m10_temperature(float);

void Receive_battery2_Maint_l80_voltage(int);
void Receive_battery2_Maint_l80_asoc(int);
void Receive_battery2_Maint_l80_remcap(int);
void Receive_battery2_Maint_l80_cycount(int);
void Receive_battery2_Maint_l80_batstatus(int);
void Receive_battery2_Maint_l80_temperature(float);

// Following are the slots when bat 2 updated info is received
// during maintenance use case

void bat2_update_voltage_maint_read(int);
void bat2_update_asoc_maint_read(int);
void bat2_update_temp_maint_read(float);
void bat2_update_cyclecount_maint_read(int);
void bat2_update_remcap_maint_read(int);
void bat2_update_batstatus_maint_read(int);

// Functions to Interpret the Results of bat 2 Maintenance Use Case
void Battery2_Result_Maint_Interpret_Voltage();
void Battery2_Result_Maint_Interpret_Temperature();
void Battery2_Result_Maint_Interpret_CycleCount();
void Battery2_Result_Maint_Interpret_Remaining_capacity();
void Battery2_Result_Maint_Interpret_asoc();
void Battery2_Result_Maint_Interpret_battery_status();

// Function to Interpret Bat 2 Maintenance Use case Specific Info - Run time to empty
void Battery2_Maint_Specific_Info_Interpret_RTE();

signals:




private:
    Ui::MainWindow *ui;
    QPropertyAnimation *animation;
    QWidget *wi;
    int *Interpret_specific_Info_maint_bat1; // Pointer to allocate memory for Specific Info (To interpret full charge capacity w.r.t design capacity)
                                              // When the interpretation of Specific Info is done the memory is deallocated

// Following variables are defined for Interpretation
// of Bat 1 Maintenance Parameters

int Interpret_b1m_result_f80[5];
int Interpret_b1m_result_m10[5];
int Interpret_b1m_result_l80[5];

float Interpret_b1m_temperature[3];

int Interpret_b1m_rte[2];

// Following variables are defined for Interpretation
// of Bat 2 Maintenance Parameters

int Interpret_b2m_result_f80[5];
int Interpret_b2m_result_m10[5];
int Interpret_b2m_result_l80[5];

float Interpret_b2m_temperature[3];

int Interpret_b2m_rte[2];

int Interpret_specific_Info_maint_bat2[2];

};

#endif // MAINWINDOW_H

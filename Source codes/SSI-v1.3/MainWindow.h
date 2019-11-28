/**************************************
Author: Yue Lin
Date: 2019/07/15
Update: 2019/07/17
Description: The mainwindow of SSI
***************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Sandwich.h"
#include "ViewDialog.h"
#include "SamplingLayerManager.h"
#include "SSHLayerManager.h"
#include "ThreadRunModel.h"
#include "ThreadSampling.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QtGui>
#include <QProgressDialog>
#include <iostream>

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Sandwich* s;
    ThreadRunModel* tRM;
    ThreadSampling* tSpl;

    // Input path of the population layer
    QString readObjectLayerPath;
    // Input path of the sampling layer
    QString readSamplingLayerPath;
    // Input path of the SSH layer
    QString readStratifiedLayerPath;

public slots:
    /* Select a value from the combo box */
    void ComboBoxValueChanged(int index);

    /* Receive the data from the Sampling Layer Manager */
    void ReceiveDataA(int code_2, QString field, QString filename, int code_3, int size);
    /* Receive the data from the SSH Layer Manager */
    void ReceiveDataB(QString field, QString filename);
    /* Start sampling, and open the progress dialog */
    void SplStart();
    /* Close the progress dialog */
    void SplEnd(int t, int code_2);
    /* Run the Sandwich model, and open the progress dialog */
    void RMStart();
    /* Close the progress dialog */
    void RMEnd();
    /* Update the progress dialog */
    void UpdateProgressDialog();

private slots:
    /* Input the population layer */
    void on_objLyr_clicked();
    /* Open the Sampling Layer Manager */
    void on_splLyr_clicked();
    /* Open the SSH Layer Manager */
    void on_stfLyr_clicked();
    /* Input the reporting layer */
    void on_rptLyr_clicked();

    /* Run the Sandwich model */
    void on_run_clicked();

    /* View the population layer */
    void on_view_1_clicked();
    /* View the sampling layer */
    void on_view_2_clicked();
    /* View the SSH layer */
    void on_view_3_clicked();
    /* View the reporting layer */
    void on_view_4_clicked();

    /* Delete the population layer */
    void on_del_1_clicked();
    /* Delete the sampling layer */
    void on_del_2_clicked();
    /* Delete the SSH layer */
    void on_del_3_clicked();
    /* Delete the reporting layer */
    void on_del_4_clicked();

private:
    Ui::MainWindow *ui;

    QProgressDialog* progress;
    QTimer* timer;
    int currentValue;

    // Sampling Layer Manager
    SamplingLayerManager* samplingLayerManager;
    // SSH Layer Manager
    SSHLayerManager* stratifiedLayerManager;
    // Layer View
    ViewDialog* viewDlg;

    /* Setup the initial value of combo box */
    void SetComboBoxValue();
};

#endif // MAINWINDOW_H

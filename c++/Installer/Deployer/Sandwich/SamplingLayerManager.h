/**************************************
Author: Yue Lin
Date: 2019/07/15
Update: 2019/07/17
Description: The Sampling Layer Manager window
***************************************/
#ifndef SAMPLINGLAYERMANAGER_H
#define SAMPLINGLAYERMANAGER_H

#include "DataOutput.h"
#include "ObjectVector.h"
#include "ObjectRatser.h"
#include "StratifiedVector.h"
#include "StratifiedRaster.h"
#include "SamplingSettings.h"
#include "Log.h"
#include "ogrsf_frmts.h"
#include "ui_samplinglayermanager.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QtGui>
#include <QDialog>
#include <vector>
#include <QString>
using namespace std;

namespace Ui {
class SamplingLayerManager;
}

class SamplingLayerManager : public QDialog
{
    Q_OBJECT

public:
    explicit SamplingLayerManager(QWidget *parent = 0);
    ~SamplingLayerManager();

    // Mark for the data type (0 for vector, 1 for raster)
    int code_1;
    // Mark if the sampling layer exists or not (0 for no, 1 for yes)
    int code_2;
    // Mark for the sampling method (1 for Simple Random Sampling, 2 for Stratified Random Sampling (equal), 3 for Stratified Random Sampling (proportional), 4 for Stratified Random Sampling (optimum))
    int code_3;

    // The selected field that denotes the weight values for each sample
    QString selectedField;

    // Sample size
    int sampleSize;

    // Input path of the population layer
    QString readObjectLayerPath;
    // Input path of the sampling layer
    QString readSamplingLayerPath;
    // Input path of the SSH layer
    QString readStratifiedLayerPath;

public slots:
    /* Get the field names of the sampling layer */
    vector<QString> GetFieldNames(QString path);

    /* Set the initial field name of combo box */
    void SetComboBoxValue();
    /* Select a field name from combo box */
    void ComboBoxValueChanged(QString field);

private:

    //Sampling Settings
    SamplingSettings* samplingSettings;

    // Collection of sampling fields
    vector<QString> fields;

private slots:

    /* Input the sampling layer */
    void on_load_clicked();
    /* Create the sampling layer */
    void on_create_clicked();

    /* Receive the data from the Sampling Settings window */
    void ReceiveData(int code_3, int sampleSize);

    /* Close this dialog */
    void on_Cancel_clicked();
    /* Finish and send back the data */
    void on_OK_clicked();

signals:
    /* Send the data to the mainwindow */
    void SendData(int code_2, QString field, QString filename, int code_3, int size);

private:
    Ui::SamplingLayerManager *ui;
};

#endif // SAMPLINGLAYERMANAGER_H

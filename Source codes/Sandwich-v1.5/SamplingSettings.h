/**************************************
Author: Yue Lin
Date: 2019/07/15
Update: 2019/07/17
Description: The Sampling Settings window
***************************************/
#ifndef SAMPLINGSETTINGS_H
#define SAMPLINGSETTINGS_H

#include "ui_samplingsettings.h"
#include <QDialog>
#include <QMessageBox>

namespace Ui {
class SamplingSettings;
}

class SamplingSettings : public QDialog
{
    Q_OBJECT

public:
    explicit SamplingSettings(QWidget *parent = 0);
    ~SamplingSettings();

    // Mark for the sampling method (1 for Simple Random Sampling, 2 for Stratified Random Sampling (equal), 3 for Stratified Random Sampling (proportional), 4 for Stratified Random Sampling (optimum))
    int code_3;

    // Population size
    int populationSize;

private:
    Ui::SamplingSettings *ui;

    /* Set the initial sampling method of the combo box */
    void SetComboBoxValue();
    /* Select a sampling method from the combo box */
    void ComboBoxValueChanged(int index);

private slots:
    /* Close this dialog */
    void on_cancel_clicked();
    /* Finish and send back the data */
    void on_OK_clicked();

signals:
    /* Send the data to the Sampling Layer Manager */
    void SendData(int code_3, int sampleSize);
};

#endif // SAMPLINGSETTINGS_H

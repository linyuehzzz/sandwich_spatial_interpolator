/**************************************
Author: Yue Lin
Date: 2019/07/15
Update: 2019/07/17
Description: The SSH Layer Manager window
***************************************/
#ifndef SSHLAYERMANAGER_H
#define SSHLAYERMANAGER_H

#include "ogrsf_frmts.h"
#include <QFileDialog>
#include <QDialog>
#include <vector>
#include <QString>
using namespace std;

namespace Ui {
class SSHLayerManager;
}

class SSHLayerManager : public QDialog
{
    Q_OBJECT

public:
    explicit SSHLayerManager(QWidget *parent = 0);
    ~SSHLayerManager();

    // Mark for data type (0 for vector, 1 for raster)
    int code_1;

    // Input path of the SSH layer
    QString readStratifiedLayerPath;

private slots:

    /* Input the SSH layer */
    void on_strInput_clicked();

    /* Finish and send back the data */
    void on_Load_clicked();
    /* Close this dialog */
    void on_Cancel_clicked();


private:
    Ui::SSHLayerManager *ui;

    // Fields of the SSH layer
    vector<QString> fields;

    /* Get all field names of the SSH layer */
    vector<QString> GetFieldNames(QString path);
    /* Set the initial field name of the combo box */
    void SetComboBoxValue();

signals:
    /* Send the data to the mainwindow */
    void SendData(QString field, QString filename);
};

#endif // SSHLAYERMANAGER_H

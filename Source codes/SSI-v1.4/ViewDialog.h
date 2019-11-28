/**************************************
Author: Yue Lin
Date: 2019/07/15
Update: 2019/07/17
Description: The View Layer window
***************************************/
#ifndef VIEWDIALOG_H
#define VIEWDIALOG_H

#include "ObjectVector.h"
#include "ObjectRatser.h"
#include "SamplingVector.h"
#include "SamplingRaster.h"
#include "StratifiedVector.h"
#include "StratifiedRaster.h"
#include "ReportingLayer.h"
#include "ui_viewdialog.h"
#include <QDialog>

namespace Ui {
class ViewDialog;
}

class ViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ViewDialog(QWidget *parent = 0);
    ~ViewDialog();

    // Population layer (vector)
    ObjectVector* objV;
    // Population layer (raster)
    ObjectRaster* objG;
    // Sampling layer (vector)
    SamplingVector* splV;
    // Sampling layer (raster)
    SamplingRaster* splG;
    // SSH layer (vector)
    StratifiedVector* stfV;
    // SSH layer (raster)
    StratifiedRaster* stfG;
    // Reporting layer
    ReportingLayer* rptLyr;

//private:
    Ui::ViewDialog *ui;
};

#endif // VIEWDIALOG_H

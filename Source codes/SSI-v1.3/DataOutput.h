/**************************************
Author: Yue Lin
Date: 2019/07/15
Update: 2019/07/17
Description: The output files of Sandwich
***************************************/
#ifndef DATAOUTPUT_H
#define DATAOUTPUT_H

#include "ReportingLayer.h"
#include "Log.h"
#include "ogrsf_frmts.h"
#include "cpl_string.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
using namespace std;

class DataOutput
{
public:
    DataOutput();
    ~DataOutput();

    // Output path of the summary report
    QString writeTXTPath;
    // Output path of the interpolated map
    QString writeSHPPath;
    // Input path of the reporting layer
    QString rptPath;

    /* Write the summary report */
    void WriteTXTFile(int code_1, ObjectVector* objV, int code_2, int code_3, int n_2, QString field, int n_3, double q, int n_4, double varianceT, int code_4);
    /* Write the interpolated map */
    void WriteSHPFile(vector<ReportingUnit *> r);
    /* Draw the output layer */
    void Draw();

};

#endif // DATAOUTPUT_H

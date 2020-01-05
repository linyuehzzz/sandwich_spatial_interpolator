/**************************************
Author: Yue Lin
Date: 2019/07/15
Update: 2019/07/17
Description: The Sandwich model
***************************************/
#ifndef SANDWICH_H
#define SANDWICH_H

#include "DataSource.h"
#include "DataOutput.h"
#include "Log.h"
#include <string>
#include <QDebug>
using namespace std;

class Sandwich
{
public:
    Sandwich();
    ~Sandwich();

    // Datasource
    DataSource* d;
    // Dataoutput
    DataOutput* o;

    // Mark for data type (0 for vector, 1 for raster)
    int code_1;
    // Mark if the sampling layer exists or not (0 for no, 1 for yes)
    int code_2;
    // Mark for the sampling method (1 for Simple Random Sampling, 2 for Stratified Random Sampling (equal), 3 for Stratified Random Sampling (proportional), 4 for Stratified Random Sampling (optimum))
    int code_3;
    // Mark if the population layer exists or not (0 for no, 1 for yes)
    int code_4;

    // Input sample size
    int inputSampleSize;

    // Sampling field
    QString weightedField;

    // Stratum ID field
    QString stratumID;

    // Input path of the population layer
    QString readObjectLayerPath;
    // Input path of the sampling layer
    QString readSamplingLayerPath;
    // Input path of the SSH layer
    QString readStratifiedLayerPath;
    //Input path of the reporting layer
    QString readReportingLayerPath;

    // Output path of the summary report
    QString writeTXTPath;
    //Output path of the interpolated map
    QString writeReportingLayerPath;

    /* Run the Sandwich model */
    void RunModel();
    /* Generate the output files */
    void WriteFile();
};

#endif // SANDWICH_H

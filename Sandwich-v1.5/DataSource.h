/**************************************
Author: Yue Lin
Date: 2019/07/15
Update: 2019/07/17
Description: The input files of Sandwich
***************************************/
#ifndef DATASOURCE_H
#define DATASOURCE_H

#include "ObjectVector.h"
#include "ObjectRatser.h"
#include "SamplingVector.h"
#include "SamplingRaster.h"
#include "StratifiedVector.h"
#include "StratifiedRaster.h"
#include "ReportingLayer.h"
#include "Log.h"
#include "ogrsf_frmts.h"
#include "gdal_priv.h"
#include <QDebug>
using namespace std;

class DataSource
{
public:
    DataSource();
    ~DataSource();

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

    /* Read the population layer */
    int ReadObjectLayer(QString readObjectLayerPath, int code);
    /* Read the sampling layer */
    int ReadSamplingLayer(QString readSamplingLayerPath, QString field, int code);
    /* Read the SSH layer */
    int ReadStratifiedLayer(QString readStratifiedLayerPath, int code, QString field);
    /* Read the reporting layer */
    int ReadReportingLayer(QString readReportingLayerPath);

    /* Distribute samples over the SSH layer */
    int SamplingV(ObjectVector* objV, int size_1, vector<KnowledgeUnit *> k, int size_2, int num, int type, QString weightedField);

private:

    /* Read the population layer (vector point) */
    int ReadObjectLayerV(QString readObjectLayerPath);
    /* Read the population layer (raster) */
    int ReadObjectLayerG(QString readObjectLayerPath);

    /* Read the sampling layer (vector point) */
    int ReadSamplingLayerV(QString readSamplingLayerPath, QString weightedField);
    /* Read the sampling layer (raster) */
    int ReadSamplingLayerG(QString readSamplingLayerPath);

    /* Read the SSH layer (vector polygon) */
    int ReadStratifiedLayerV(QString readStratifiedLayerPath, QString field);
    /* Read the SSH layer (raster) */
    int ReadStratifiedLayerG(QString readStratifiedLayerPath);

    /* Read the reporting layer (vector polygon) */
    int ReadReportingLayerV(QString readReportingLayerPath);

};

#endif // DATASOURCE_H

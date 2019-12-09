/**************************************
Author: Yue Lin
Date: 2019/07/15
Update: 2019/07/17
Description: Reporting layer
***************************************/
#ifndef REPORTINGLAYER_H
#define REPORTINGLAYER_H

#include "Point.h"
#include "StratifiedVector.h"
#include "ogrsf_frmts.h"
#include <vector>
using namespace std;

/* Reporting unit */
class ReportingUnit
{
public:
    // Location
    vector<OGRGeometry* > runit;

    // Area (km2)
    double area;

    // Sample mean
    double mean;
    // Variance of sample mean
    double varianceSM;
};


class ReportingLayer
{
public:
    ReportingLayer();
    ~ReportingLayer();

    // Collection of the reporting units
    vector<ReportingUnit* > runits;

    // Number of the reporting units
    int number;

    // Total sample variance of the map
    double VairanceT;

    // MBR of the reporting layer
    double minx;
    double miny;
    double maxx;
    double maxy;

    // dividing points
    vector<double > DivMean;
    vector<double > DivVarSM;

    /* Draw the reporting layer */
    void Draw();
    /* Draw the output layer (mean value) */
    void DrawMean();
    /* Draw the output layer (variance) */
    void DrawVar();

    /* Calculate the mean value and the variance of sample mean of each reporting unit */
    void CalculateRUValue(vector<KnowledgeUnit *> k, int size);
    /* Set dividing points of the legends */
    void SetDividingPoints();
    /* Calculate the total sample variance of the map */
    void CalculateVarianceT(vector<SamplingPt* > s, int size);

private:
    /* Calculate classification intervals */
    vector<double > EqualInterval(vector<double > data);
    /* Calculate the mean value of a reporting unit */
    double CalculateMean(vector<OGRGeometry *> r, double area, vector<KnowledgeUnit *> k, int size);
    /* Calculate the variance of sample mean of a reporting unit */
    double CalculateVarianceSM(vector<OGRGeometry *> r, double area, vector<KnowledgeUnit *> k, int size);
};

#endif // REPORTINGLAYER_H

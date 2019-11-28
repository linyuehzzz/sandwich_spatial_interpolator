/**************************************
Author: Yue Lin
Date: 2019/07/15
Update: 2019/07/17
Description: SSH layer (vector)
***************************************/
#ifndef STRATIFIEDVECTOR_H
#define STRATIFIEDVECTOR_H

#include "StratifiedLayer.h"

/* Stratum */
class KnowledgeUnit
{
public:
    // Location
    vector<OGRGeometry* > kunit;

    // Stratum ID
    int id;

    // Area (km2)
    double area;

    // Population size
    int N;
    // Population variance
    double varianceT;

    // Sample size
    int n;
    // Sample mean
    double mean;
    // Sample variance
    double variance;
    // Variance of sample mean
    double varianceSM;
};


class StratifiedVector: public StratifiedLayer
{
public:
    StratifiedVector();
    ~StratifiedVector();

    // Collection of strata
    vector<KnowledgeUnit* > kunits;

    // MBR of the SSH layer
    double minx;
    double miny;
    double maxx;
    double maxy;

    /* Add a stratum */
    void AddUnit(KnowledgeUnit* ku);

    /* Draw the SSH layer */
    void Draw();

    /* Calculate mean value and variance of sample mean of each stratum */
    void CalculateKUValue(ObjectVector* objV, vector<SamplingPt* > s, int size2, int code);

    /* Calculate the geodetector q-statistic */
    void Calculateq(vector<SamplingPt* > s, int size);

    /* Calculate the total population */
    int CalculateNT(vector<KnowledgeUnit *> k);
    /* Calculate the variance of the population */
    void CalculateVarianceT(vector<KnowledgeUnit *> k, vector<ObjectPt *> o, int size);

    /* Calculate the population size of each stratum */
    void CalculatePopulationSize(vector<KnowledgeUnit *> k, vector<ObjectPt *> o, int size);

private:
    /* Calculate the sample size of a stratum */
    int CalculateSampleSize(vector<OGRGeometry *> k, vector<SamplingPt *> s, int size);
    /* Calculate the sample mean of a stratum */
    double CalculateMean(vector<OGRGeometry *> k, vector<SamplingPt *> s, int size);
    /* Calculate the sample variance of a stratum */
    double CalculateVariance(vector<OGRGeometry* > k, double mean, vector<SamplingPt *> s, int size);
    /* Calculate the variance of sample mean of a stratum */
    double CalculateVarianceSM(int N, int n, double variance, int code);

    /* Calculate the SST (total sum of squares) */
    double CalculateSST(vector<SamplingPt* > s, int size);
    /* Calculate the SSW (within sum of squares) */
    double CalculateSSW();

};

#endif // STRATIFIEDVECTOR_H

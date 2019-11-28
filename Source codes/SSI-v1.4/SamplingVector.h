/**************************************
Author: Yue Lin
Date: 2019/07/15
Update: 2019/07/17
Description: Sampling layer (vector)
***************************************/
#ifndef SAMPLINGVECTOR_H
#define SAMPLINGVECTOR_H

#include "SamplingLayer.h"
#include "Log.h"
#include <QDebug>

class KnowledgeUnit;


/* Sample */
class SamplingPt
{
public:
    // Location
    OGRGeometry* spt;

    // Weight
    double weight;
};


class SamplingVector: public SamplingLayer
{
public:
    SamplingVector();
    ~SamplingVector();

    // Collection of samples
    vector<SamplingPt* > spts;

    // MBR of the sampling layer
    double minx;
    double miny;
    double maxx;
    double maxy;

    /* Add a sample */
    void AddPoint(SamplingPt* spt);

    /* Draw the sampling layer */
    void Draw();

    /* Simple random sampling */
    int SimpleRandomSampling(vector<ObjectPt *> o, int size, int num);
    /* Max allowable sample size for stratified random sampling (equal) */
    int MaxSampleSizeEA(vector<ObjectPt *> o, int size_1, vector<KnowledgeUnit *> k, int size_2);
    /* Stratified random sampling (equal) */
    int StratifiedSamplingEA(vector<ObjectPt *> o, int size_1, vector<KnowledgeUnit *> k, int size_2, int num);
    /* Stratified random sampling (proportional) */
    int StratifiedSamplingPA(vector<ObjectPt *> o, int size_1, vector<KnowledgeUnit *> k, int size_2, int NT, int num);
    /* Stratified random sampling (optimum) */
    int StratifiedSamplingOA(vector<ObjectPt *> o, int size_1, vector<KnowledgeUnit *> k, int size_2, int num);

private:

    /* Shuffle the array */
    void Shuffle(vector<int> a, int size, int n);

};

#endif // SAMPLINGVECTOR_H

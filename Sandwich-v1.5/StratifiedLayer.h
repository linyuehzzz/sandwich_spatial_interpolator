/**************************************
Author: Yue Lin
Date: 2019/07/15
Update: 2019/07/17
Description: SSH layer
***************************************/
#ifndef STRATIFIEDLAYER_H
#define STRATIFIEDLAYER_H

#include "Point.h"
#include "SamplingVector.h"
#include "SamplingRaster.h"
#include "ogrsf_frmts.h"
#include <vector>
using namespace std;


class StratifiedLayer
{
public:
    StratifiedLayer();
    ~StratifiedLayer();

    // The number of strata
    int number;

    // Geodetector q-statistic
    double q;
    // SST (total sum of squares)
    double SST;
    // SSW (within sum of squares)
    double SSW;

};

#endif // STRATIFIEDLAYER_H

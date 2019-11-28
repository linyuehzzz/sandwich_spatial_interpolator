/**************************************
Author: Yue Lin
Date: 2019/07/15
Update: 2019/07/17
Description: Sampling layer
***************************************/
#ifndef SAMPLINGLAYER_H
#define SAMPLINGLAYER_H

#include "Point.h"
#include "ObjectVector.h"
#include "ObjectRatser.h"
#include "ogrsf_frmts.h"
#include <QString>
#include <vector>
#include <time.h>
using namespace std;

class SamplingLayer
{
public:
    SamplingLayer();
     ~SamplingLayer();

    // Sample size
    int number;

};

#endif // SAMPLINGLAYER_H

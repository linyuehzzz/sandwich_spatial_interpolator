/**************************************
Author: Yue Lin
Date: 2019/07/15
Update: 2019/07/17
Description: SSH layer (raster)
***************************************/
#ifndef STRATIFIEDRASTER_H
#define STRATIFIEDRASTER_H

#include "StratifiedLayer.h"

class StratifiedRaster: public StratifiedLayer
{
public:
    StratifiedRaster();
    ~StratifiedRaster();

    // The raster matrix of the SSH layer
    vector<vector<double>* > grids;

    // Stratum ID
    vector<int> ids;

    // Width and length
    int nXSize;
    int nYSize;

    // The no data value of the raster data
    double noDataValue;
};

#endif // STRATIFIEDRASTER_H

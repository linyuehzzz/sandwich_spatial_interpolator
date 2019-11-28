/**************************************
Author: Yue Lin
Date: 2019/07/15
Update: 2019/07/17
Description: Population layer (raster)
***************************************/
#ifndef OBJECTRASTER_H
#define OBJECTRASTER_H

#include "ObjectLayer.h"

class ObjectRaster: public ObjectLayer
{
public:
    ObjectRaster();
    ~ObjectRaster();

    // The raster matrix of the population layer
    vector<vector<double>* > grids;

    // Width and length
    int nXSize;
    int nYSize;

    // The no data value of the raster data
    double noDataValue;
};

#endif // OBJECTRASTER_H

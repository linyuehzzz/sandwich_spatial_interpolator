/**************************************
Author: Yue Lin
Date: 2019/07/15
Update: 2019/07/17
Description: Population layer (vector)
***************************************/
#ifndef OBJECTVECTOR_H
#define OBJECTVECTOR_H

#include "ObjectLayer.h"

/* Population unit (vector point) */
class ObjectPt
{
public:
    // Location
    OGRGeometry* opt;

    // Attribute values (int)
    vector<int> valueI;
    // Attribute values (real/double)
    vector<double> valueD;

    // Weight
    double weight;
};


class ObjectVector: public ObjectLayer
{
public:
    ObjectVector();
    ~ObjectVector();

    // Collection of the population units
    vector<ObjectPt* > opts;

    // Attribute name (int)
    vector<QString > attrI;
    // Attribute number (int)
    int countI;
    // Attribute name (real/double)
    vector<QString > attrD;
    // Attribute number (real/double)
    int countD;

    // MBR of the population layer
    double minx;
    double miny;
    double maxx;
    double maxy;

    /* Add a population unit */
    void AddPoint(ObjectPt* opt);

    /* Draw the population layer */
    void Draw();
};

#endif // OBJECTVECTOR_H

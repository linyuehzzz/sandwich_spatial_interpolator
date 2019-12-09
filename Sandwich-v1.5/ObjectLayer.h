/**************************************
Author: Yue Lin
Date: 2019/07/15
Update: 2019/07/17
Description: Population layer
***************************************/
#ifndef OBJECTLAYER_H
#define OBJECTLAYER_H

#include "Point.h"
#include "ogrsf_frmts.h"
#include <glut.h>
#include <QtOpenGL/QGL>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <vector>
using namespace std;

class ObjectLayer
{
public:
    ObjectLayer();
    ~ObjectLayer();

    // Population size
    int number;

};

#endif // OBJECTLAYER_H

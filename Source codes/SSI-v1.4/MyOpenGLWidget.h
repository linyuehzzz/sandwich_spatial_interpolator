/**************************************
Author: Yue Lin
Date: 2019/07/15
Update: 2019/07/17
Description: The OpenGL widget in the Layer View window
***************************************/
#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include "ObjectVector.h"
#include "ObjectRatser.h"
#include "SamplingVector.h"
#include "SamplingRaster.h"
#include "StratifiedVector.h"
#include "StratifiedRaster.h"
#include "ReportingLayer.h"
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class QOpenGLShaderProgram;

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MyOpenGLWidget(QWidget *parent = 0);
    ~MyOpenGLWidget();

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

    // Mark which layer to be displayed
    int code;

    /* Initialize the OpenGL widget */
    void initializeGL();
    /* Create a map on the OpenGL widget */
    void paintGL();
    /* Resize the OpenGL widget */
    void resizeGL(int width, int height);

};

#endif // MYOPENGLWIDGET_H

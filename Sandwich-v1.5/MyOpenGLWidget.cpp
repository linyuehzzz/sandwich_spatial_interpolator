#include "MyOpenGLWidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{
    this->code = 0;

    this->objV = 0x00;
    this->splV = 0x00;
    this->stfV = 0x00;
    this->rptLyr = 0x00;
}

MyOpenGLWidget::~MyOpenGLWidget()
{
    if (this->objV != 0x00){
        delete objV;
        objV = 0x00;
    }

    if (this->splV != 0x00){
        delete splV;
        splV = 0x00;
    }

    if (this->stfV != 0x00){
        delete stfV;
        stfV = 0x00;
    }

    if (this->rptLyr != 0x00){
        delete rptLyr;
        rptLyr = 0x00;
    }
}


/// <summary>
/// Initialize the OpenGL widget
/// </summary>
void MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}


/// <summary>
/// Create a map on the OpenGL widget
/// </summary>
void MyOpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    if(this->code == 1)
        this->objV->Draw();
    else if(this->code == 2)
        this->splV->Draw();
    else if(this->code == 3)
        this->stfV->Draw();
    else if(this->code == 4)
        this->rptLyr->Draw();
    else if(this->code == 5)
        this->rptLyr->DrawMean();
    else if(this->code == 6)
        this->rptLyr->DrawVar();
}


/// <summary>
/// Resize the OpenGL widget
/// </summary>
/// <param name="width">    Width   </param name>
/// <param name="height">   Height  </param name>
void MyOpenGLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, (GLint)width, (GLint)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

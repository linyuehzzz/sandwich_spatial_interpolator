#include "ObjectVector.h"


ObjectVector::ObjectVector()
{
    this->maxx = 0;
    this->maxy = 0;
    this->minx = 0;
    this->miny = 0;

    this->countI = 0;
    this->countD = 0;
}


ObjectVector::~ObjectVector()
{

}


/// <summary>
/// Add a population unit
/// </summary>
/// <param name="opt">      population unit     </param name>
void ObjectVector::AddPoint(ObjectPt* opt)
{
    opts.push_back(opt);
}


/// <summary>
/// Draw the population layer
/// </summary>
void ObjectVector::Draw()
{
    glColor3f(0.5f, 0.0f, 0.5f);
    glPointSize(6);
    glBegin(GL_POINTS);
    for(int i = 0; i < number; i++)
    {
        ObjectPt* opt = opts.at(i);
        OGRPoint* p = (OGRPoint*)opt->opt;
        Point* point = new Point();
        point->x = p->getX();
        point->y = p->getY();
        int width = (int) maxx - minx;
        int height = (int) maxy - miny;
        float x = (float)((point->x - minx)/ width * 2 - 1) * 0.95;
        float y = (float)((point->y - miny)/ height * 2 - 1) * 0.95;
        glVertex2f(x, y);

        delete point;
    }
    glEnd();
}

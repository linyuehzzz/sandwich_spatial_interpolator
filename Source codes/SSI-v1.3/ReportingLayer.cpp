#include "ReportingLayer.h"

ReportingLayer::ReportingLayer()
{
    this->number = 0;
    this->VairanceT = 0;

    this->maxx = 0;
    this->maxy = 0;
    this->minx = 0;
    this->miny = 0;
}


ReportingLayer::~ReportingLayer()
{

}


/// <summary>
/// Draw the reporting layer
/// </summary>
void ReportingLayer::Draw()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor3f(0.0f, 0.3f, 0.0f);
    glLineWidth(3);
    for(int i = 0; i < number; i++)
    {
        ReportingUnit* ru = runits.at(i);
        vector<OGRGeometry* > polys = ru->runit;
        for(int j = 0; j < polys.size(); j++){
            OGRPolygon* poly = (OGRPolygon*) polys.at(j);
            OGRLinearRing* bound = poly->getExteriorRing();
            long count = bound->getNumPoints();
            glBegin(GL_LINE_STRIP);
            for(int k = 0; k < count; k++){
                Point* point = new Point();
                point->x = bound->getX(k);
                point->y = bound->getY(k);
                int width = (int) maxx - minx;
                int height = (int) maxy - miny;
                float x = (float)(point->x - minx)/ width * 2 - 1;
                float y = (float)(point->y - miny)/ height * 2 - 1;
                glVertex2f(x, y);
                delete point;
            }
            glEnd();
        }
    }
}


/// <summary>
/// Calculate the mean value and the variance of sample mean of each reporting unit
/// </summary>
/// <param name="k">        Collection of strata    </param name>
/// <param name="size">     Number of strata        </param name>
void ReportingLayer::CalculateRUValue(vector<KnowledgeUnit *> k, int size)
{
    for(int i = 0; i < this->number; i++){

        ReportingUnit* r = this->runits.at(i);

        // Mean value
        double mean = CalculateMean(r->runit, r->area, k, size);
        r->mean = mean;

        // Variance of sample mean
        double varianceSM = CalculateVarianceSM(r->runit, r->area, k, size);
        r->varianceSM = varianceSM;
    }
}


/// <summary>
/// Calculate the mean value of a reporting unit
/// </summary>
/// <param name="r">        Reporting unit              </param name>
/// <param name="area">     Area of the reporting unit  </param name>
/// <param name="k">        Collection of strata        </param name>
/// <param name="size">     Number of strata            </param name>
/// <returns>   Mean value of a reporting unit  </returns>
double ReportingLayer::CalculateMean(vector<OGRGeometry* > r, double area, vector<KnowledgeUnit *> k, int size)
{
    double sum = 0;
    double mean = 0;
    double overlap = 0;
    double overlapT = 0;

    for(int i = 0; i < size; i++){
        KnowledgeUnit* u = k.at(i);
        vector<OGRGeometry* > polys = u->kunit;
        for(int j = 0; j < polys.size(); j++){
            OGRGeometry* poly = polys.at(j);
            for(int k = 0; k < r.size(); k++){
                OGRGeometry* rr = r.at(k);
                if(poly->Intersects(rr)){
                    OGRPolygon* o = (OGRPolygon*)poly->Intersection(rr);
                    if(o != 0x00){
                        overlap = o->get_Area() / 1000000;
                        sum = sum + overlap * u->mean;
                        overlapT = overlapT + overlap;
                    }
                }
            }
        }
    }
    mean = sum/area;

    return mean;
}


/// <summary>
/// Calculate the variance of sample mean of a reporting unit
/// </summary>
/// <param name="r">        Reporting unit              </param name>
/// <param name="area">     Area of the reporting unit  </param name>
/// <param name="k">        Collection of strata        </param name>
/// <param name="size">     Number of strata            </param name>
/// <returns>       Variance of sample mean of a reporting unit     </returns>
double ReportingLayer::CalculateVarianceSM(vector<OGRGeometry *> r, double area, vector<KnowledgeUnit *> k, int size)
{
    double varianceSM = 0;
    double overlap = 0;
    double overlapT = 0;

    for(int i = 0; i < size; i++){
        KnowledgeUnit* u = k.at(i);
        vector<OGRGeometry* > polys = u->kunit;
        for(int j = 0; j < polys.size(); j++){
            OGRGeometry* poly = polys.at(j);
            for(int k = 0; k < r.size(); k++){
                OGRGeometry* rr = r.at(k);
                if(poly->Intersects(rr)){
                    OGRPolygon* o = (OGRPolygon*)poly->Intersection(rr);
                    if(o != 0x00){
                        overlap = o->get_Area() / 1000000;
                        varianceSM = varianceSM + pow(overlap/area, 2) * u->varianceSM;
                        overlapT = overlapT + overlap;
                    }
                }
            }
        }
    }
    return varianceSM;
}


/// <summary>
/// Calculate the total sample variance of the map
/// </summary>
/// <param name="s">        Collection of samples   </param name>
/// <param name="size">     Sample size             </param name>
/// <returns>               Total sample variance   </returns>
void ReportingLayer::CalculateVarianceT(vector<SamplingPt* > s, int size)
{
    int count = 0;
    double sum = 0;
    double mean = 0;
    double VarianceT = 0;

    // Mean
    for(int i = 0; i < size; i++){

        SamplingPt* p = s.at(i);
        sum = sum + p->weight;
        count++;
    }
    mean = sum/count;

    // Total sample variance
    for(int i = 0; i < size; i++){

        SamplingPt* p = s.at(i);
        VarianceT = VarianceT + pow(p->weight - mean, 2);
    }

    VarianceT = VarianceT/count;
    this->VairanceT = VarianceT;
}

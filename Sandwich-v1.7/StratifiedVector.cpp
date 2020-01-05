#include "StratifiedVector.h"

StratifiedVector::StratifiedVector()
{
    this->maxx = 0;
    this->maxy = 0;
    this->minx = 0;
    this->miny = 0;
}


StratifiedVector::~StratifiedVector()
{

}


/// <summary>
/// Add a stratum
/// </summary>
/// <param name="spt">  stratum   </param name>
void StratifiedVector::AddUnit(KnowledgeUnit* ku)
{
    kunits.push_back(ku);
}


/// <summary>
/// Draw the SSH layer
/// </summary>
void StratifiedVector::Draw()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor3f(0.7f, 0.0f, 0.0f);
    glLineWidth(3);
    for(int i = 0; i < number; i++)
    {
        KnowledgeUnit* ku = kunits.at(i);
        vector<OGRGeometry* > polys = ku->kunit;
        for(unsigned int j = 0; j < polys.size(); j++){
            OGRPolygon* poly = (OGRPolygon*)polys.at(j);
            OGRLinearRing* bound = poly->getExteriorRing();
            long long count = bound->getNumPoints();
            glBegin(GL_LINE_STRIP);
            for(long long j = 0; j < count; j++){
                Point* point = new Point();
                point->x = bound->getX(j);
                point->y = bound->getY(j);
                int width = (int) maxx - minx;
                int height = (int) maxy - miny;
                float x = (float)((point->x - minx)/ width * 2 - 1) * 0.95;
                float y = (float)((point->y - miny)/ height * 2 - 1) * 0.95;
                glVertex2f(x,y);
                delete point;
            }
            glEnd();
        }
    }
}


/// <summary>
/// Calculate mean value and variance of sample mean of each stratum
/// </summary>
/// <param name="objV">     Population layer        </param name>
/// <param name="s">        Collection of samples   </param name>
/// <param name="size1">    Sample size             </param name>
/// <param name="code">     Mark if the population layer exists or not  </param name>
void StratifiedVector::CalculateKUValue(ObjectVector* objV, vector<SamplingPt *> s, int size2, int code)
{
    if(code == 1){
        vector<ObjectPt *> o = objV->opts;
        int size1 = objV->number;
        //Calculate the population size of each stratum
        CalculatePopulationSize(this->kunits, o, size1);

        for(int i = 0; i < this->number; i++){
            KnowledgeUnit* k = this->kunits.at(i);
            // Calculate the sample size of a stratum
            int count2 = CalculateSampleSize(k->kunit, s, size2);
            k->n = count2;
            // Calculate the sample mean of a stratum
            double mean = CalculateMean(k->kunit, s, size2);
            k->mean = mean;
            // Calculate the sample variance of a stratum
            double variance = CalculateVariance(k->kunit, k->mean, s, size2);
            k->variance = variance;
            // Calculate the variance of sample mean of a stratum
            double varianceSM = CalculateVarianceSM(k->N, k->n, k->variance, code);
            k->varianceSM = varianceSM;
        }
    }else{
        for(int i = 0; i < this->number; i++){
            KnowledgeUnit* k = this->kunits.at(i);
            // Calculate the sample size of a stratum
            int count2 = CalculateSampleSize(k->kunit, s, size2);
            k->n = count2;
            // Calculate the sample mean of a stratum
            double mean = CalculateMean(k->kunit, s, size2);
            k->mean = mean;
            // Calculate the sample variance of a stratum
            double variance = CalculateVariance(k->kunit, k->mean, s, size2);
            k->variance = variance;
            // Calculate the variance of sample mean of a stratum
            double varianceSM = CalculateVarianceSM(k->N, k->n, k->variance, code);
            k->varianceSM = varianceSM;
        }
    }

}


/// <summary>
/// Calculate the population size of each stratum
/// </summary>
/// <param name="k">    Collection of strata    </param name>
/// <param name="o">    Collection of samples   </param name>
/// <param name="size"> Sample size             </param name>
void StratifiedVector::CalculatePopulationSize(vector<KnowledgeUnit* > k, vector<ObjectPt *> o, int size)
{
    for(int a = 0; a < number; a++){
        KnowledgeUnit* ku = k.at(a);
        vector<OGRGeometry* > polys = ku->kunit;
        int count = 0;
        for(unsigned int i = 0; i < polys.size(); i++){
            OGRGeometry* poly = polys.at(i);
            for(int j = 0; j < size; j++){

                ObjectPt* p = o.at(j);
                OGRGeometry* pt = p->opt;
                if(pt->Intersects(poly))
                    count++;
            }
        }
        ku->N = count;
    }
}


/// <summary>
/// Calculate the sample size of a stratum
/// </summary>
/// <param name="k">    Stratum                 </param name>
/// <param name="s">    Collection of samples   </param name>
/// <param name="size"> Sample size             </param name>
/// <returns>       Sample size of a stratum    </returns>
int StratifiedVector::CalculateSampleSize(vector<OGRGeometry* > k,vector<SamplingPt *> s, int size)
{
    int count = 0;
    for(unsigned int i = 0; i < k.size(); i++){
        OGRGeometry* poly = k.at(i);
        for(int j = 0; j < size; j++){
            SamplingPt* p = s.at(j);
            OGRGeometry* pt = p->spt;
            if(pt->Intersects(poly))
                count++;
        }
    }

    return count;
}


/// <summary>
/// Calculate the sample mean of a stratum
/// </summary>
/// <param name="k">    Stratum                 </param name>
/// <param name="s">    Collection of samples   </param name>
/// <param name="size"> Sample size             </param name>
/// <returns>       Sample mean of a stratum    </returns>
double StratifiedVector::CalculateMean(vector<OGRGeometry* > k,vector<SamplingPt *> s, int size)
{
    double sum = 0;
    int count = 0;
    double mean = 0;

    for(unsigned int i = 0; i < k.size(); i++){
        OGRGeometry* poly = k.at(i);
        for(int j = 0; j < size; j++){

            SamplingPt* p = s.at(j);
            OGRGeometry* pt = p->spt;

            if(pt->Intersects(poly)){
                sum = sum + p->weight;
                count++;
            }
        }
    }
    mean = sum/count;

    return mean;
}


/// <summary>
/// Calculate the sample variance of a stratum
/// </summary>
/// <param name="k">    Stratum                     </param name>
/// <param name="mean"> Sample mean of the stratum  </param name>
/// <param name="s">    Collection of samples       </param name>
/// <param name="size"> Sample size                 </param name>
/// <returns>   Sample variance of a stratum        </returns>
double StratifiedVector::CalculateVariance(vector<OGRGeometry* > k, double mean, vector<SamplingPt *> s, int size)
{
    int count = 0;
    double sum = 0;
    double variance = 0;

    for(unsigned int i = 0; i < k.size(); i++){
        OGRGeometry* poly = k.at(i);
        for(int j = 0; j < size; j++){

            SamplingPt* p = s.at(j);
            OGRGeometry* pt = p->spt;

            if(pt->Intersects(poly)){
                sum = sum + pow(p->weight - mean, 2);
                count++;
            }
        }
    }
    variance = sum / (count-1);

    return variance;
}


/// <summary>
/// Calculate the variance of sample mean of a stratum
/// </summary>
/// <param name="N">        Population size in the stratum  </param name>
/// <param name="n">        Sample size in the stratum      </param name>
/// <param name="variance"> Sample variance of the stratum  </param name>
/// <param name="code">     Mark if the population layer exists or not      </param name>
/// <returns>   Variance of sample mean of a stratum    </returns>
double StratifiedVector::CalculateVarianceSM(int N, int n, double variance, int code)
{
    double VarianceSM = 0;
    if(code == 1)
        VarianceSM = (N - n) * variance/(N * n);
    else if(code == 0)
        VarianceSM = variance/n;

    return VarianceSM;
}


/// <summary>
/// Calculate the geodetector q-statistic
/// <param name="s">    Collection of samples       </param name>
/// <param name="size"> Sample size                 </param name>
void StratifiedVector::Calculateq(vector<SamplingPt* > s, int size)
{

    double SST = CalculateSST(s, size);
    this->SST = SST;

    double SSW = CalculateSSW();
    this->SSW = SSW;

    double q = 1 - SSW/SST;
    this->q = q;
}


/// <summary>
/// Calculate the SST (total sum of squares)
/// </summary>
/// <param name="s">    Collection of samples       </param name>
/// <param name="size"> Sample size                 </param name>
/// <returns>   SST     </returns>
double StratifiedVector::CalculateSST(vector<SamplingPt *> s, int size)
{
    int count = 0;
    double sum = 0;
    double mean = 0;
    double SST = 0;

    //计算平均值
    for(int i = 0; i < size; i++){

        SamplingPt* p = s.at(i);
        sum = sum + p->weight;
        count++;
    }
    mean = sum/count;

    //计算SST
    for(int i = 0; i < size; i++){

        SamplingPt* p = s.at(i);
        SST = SST + pow(p->weight - mean, 2);
    }

    return SST;
}


/// <summary>
/// Calculate the SSW (within sum of squares)
/// </summary>
/// <returns>   SSW     </returns>
double StratifiedVector::CalculateSSW()
{
    double SSW = 0;
    for(int i = 0; i < this->number; i++){

        KnowledgeUnit* k = this->kunits.at(i);
        SSW = SSW + k->variance * k->n;
    }

    return SSW;
}


/// <summary>
/// Calculate the total population
/// </summary>
/// <returns>   Total population    </returns>
int StratifiedVector::CalculateNT(vector<KnowledgeUnit *> k)
{
    int NT = 0;

    for(int i = 0; i < this->number; i++){

        KnowledgeUnit* ku = k.at(i);
        NT = NT + ku->N;

    }
    return NT;
}


/// <summary>
/// Calculate the variance of the population
/// </summary>
/// <param name="mean"> Sample mean of the stratum  </param name>
/// <param name="s">    Collection of samples       </param name>
/// <param name="size"> Sample size                 </param name>
void StratifiedVector::CalculateVarianceT(vector<KnowledgeUnit* > k, vector<ObjectPt *> o, int size)
{
    int count = 0;
    double sum_1 = 0;
    double mean = 0;
    double sum_2 = 0;
    double varianceT = 0;

    // Mean
    for(int a = 0; a < number; a++){
        KnowledgeUnit* ku = k.at(a);
        vector<OGRGeometry* > polys = ku->kunit;
        for(unsigned int i = 0; i < polys.size(); i++){
            OGRGeometry* poly = polys.at(i);
            for(int j = 0; j < size; j++){
                ObjectPt* p = o.at(j);
                OGRGeometry* pt = p->opt;
                if(pt->Intersects(poly)){
                    sum_1 = sum_1 + p->weight;
                    count++;
                }
            }
        }
        mean = sum_1 / count;

        // Variance
        for(unsigned int i = 0; i < polys.size(); i++){
            OGRGeometry* poly = polys.at(i);
            for(int j = 0; j < size; j++){
                ObjectPt* p = o.at(j);
                OGRGeometry* pt = p->opt;
                if(pt->Intersects(poly)){
                    sum_2 = sum_2 + pow(p->weight - mean, 2);
                }
            }
        }
        varianceT = sum_2 / (count-1);
        ku->varianceT = varianceT;
    }
}

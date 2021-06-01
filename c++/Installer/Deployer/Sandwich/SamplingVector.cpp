#include "StratifiedVector.h"

SamplingVector::SamplingVector()
{
    this->maxx = 0;
    this->maxy = 0;
    this->minx = 0;
    this->miny = 0;

    logInit();
}

SamplingVector::~SamplingVector()
{

}


/// <summary>
/// Add a sample
/// </summary>
/// <param name="spt">  Sample  </param name>
void SamplingVector::AddPoint(SamplingPt* spt)
{
    spts.push_back(spt);
}


/// <summary>
/// Draw the sampling layer
/// </summary>
void SamplingVector::Draw()
{
    glColor3f(1.0f, 0.0f, 1.0f);
    glPointSize(6);
    glBegin(GL_POINTS);
    for(int i = 0; i < number; i++)
    {
        SamplingPt* spt = spts.at(i);
        OGRPoint* p = (OGRPoint*)spt->spt;
        Point* point = new Point();
        point->x = p->getX();
        point->y = p->getY();
        int width = (int) maxx - minx;
        int height = (int) maxy - miny;
        float x = (float)((point->x - minx)/ width * 2 - 1) * 0.95;
        float y = (float)((point->y - miny)/ height * 2 - 1) * 0.95;
        glVertex2f(x,y);

        delete point;
    }
    glEnd();
}


/// <summary>
/// Shuffle the array
/// </summary>
/// <param name="a">    Array               </param name>
/// <param name="size"> Array size          </param name>
/// <param name="n">    Shuffling count     </param name>
void SamplingVector::Shuffle(vector<int > a, int size, int n)
{
    int p1, p2, tmp;
    while(n--){
        p1 = rand() % (size + 1);
        p2 = rand() % (size + 1);
        tmp = a.at(p1);
        a.at(p1) = a.at(p2);
        a.at(p2) = tmp;
    }
}


/// <summary>
/// Simple random sampling
/// </summary>
/// <param name="o">    Collection of population units  </param name>
/// <param name="size"> Number of the population units  </param name>
/// <param name="num">  Sample size                     </param name>
int SamplingVector::SimpleRandomSampling(vector<ObjectPt *> o, int size, int num)
{
    qInfo()<< "Simple random sampling...";

    int t = 999;
    if(num <= size){

        // Initialize the array
        vector<int > a;
        srand((unsigned)time(NULL));
        for(int i = 0; i <= size; i++)
            a.push_back(i);

        // Shuffle
        this->Shuffle(a, size, 2000);

        // Create the sampling layer
        for(int i = 0; i < num; i++){
            SamplingPt* sp = new SamplingPt();
            ObjectPt* opt = o.at(a.at(i));
            sp->spt = opt->opt;
            sp->weight = opt->weight;
            this->AddPoint(sp);
        }
        t = 1;
    }else{
        qCritical()<< "The sampling number has exceeded the population size.";
        t = 0;
    }
    return t;
}


/// <summary>
/// Max allowable sample size for stratified random sampling (equal)
/// </summary>
/// <param name="o">        Collection of population units      </param name>
/// <param name="size">     Number of the population units      </param name>
/// <param name="k">        Collection of strata            </param name>
/// <param name="size_2">   Number of strata                </param name>
/// <returns>   Max allowable sample size   </returns>
int SamplingVector::MaxSampleSizeEA(vector<ObjectPt *> o, int size_1, vector<KnowledgeUnit *> k, int size_2)
{
    int nmax = 0;
    int count = 0;
    OGRGeometry* poly;
    ObjectPt* p;
    OGRGeometry* pt;

    KnowledgeUnit* ku = k.at(0);
    vector<OGRGeometry* > polys = ku->kunit;
    for(int c = 0; c < polys.size(); c++){
        poly = polys.at(c);
        for(int d = 0; d < size_1; d++){
            p = o.at(d);
            pt = p->opt;
            if(pt->Intersects(poly))
                count++;
        }
    }
    nmax = count;

    for(int b = 1; b < size_2; b++){
        ku = k.at(b);
        polys = ku->kunit;
        count = 0;
        for(int c = 0; c < polys.size(); c++){
            poly = polys.at(c);
            for(int d = 0; d < size_1; d++){
                p = o.at(d);
                pt = p->opt;
                if(pt->Intersects(poly))
                    count++;
            }
        }
        if(nmax > count)
            nmax = count;
    }

    return nmax;
}


/// <summary>
/// Stratified random sampling (equal)
/// </summary>
/// <param name="o">        Collection of population units      </param name>
/// <param name="size">     Number of the population units      </param name>
/// <param name="k">        Collection of strata            </param name>
/// <param name="size_2">   Number of strata                </param name>
/// <param name="num">      Sample size                     </param name>
int SamplingVector::StratifiedSamplingEA(vector<ObjectPt *> o, int size_1, vector<KnowledgeUnit *> k, int size_2, int num)
{  
    qInfo()<< "Stratified random sampling (equal allocation)...";

    int t = 999;

    // Calculate the max allowable sample size
    int nmax = MaxSampleSizeEA(o, size_1, k, size_2);

    int totalNum = 0;
    int count = 0;
    int remainder = 0;
    int n = num / size_2;

    if(num <= size_1 && n <= nmax){

        totalNum = n * size_2;
        remainder = num - totalNum;
        int m = 0;

        if(remainder != 0){ // When not divisible
            for(int b = 0; b < size_2; b++){

                KnowledgeUnit* ku = k.at(b);
                vector<OGRGeometry*> polys = ku->kunit;

                // Calculate the population size in each stratum
                count = 0;
                for(int c = 0; c < polys.size(); c++){
                    OGRGeometry* poly = polys.at(c);
                    for(int d = 0; d < size_1; d++){
                        ObjectPt* p = o.at(d);
                        OGRGeometry* pt = p->opt;
                        if(pt->Intersects(poly))
                            count++;
                    }
                }

                // Initialize the array
                int q = 0;
                vector<int >a(count + 1);
                for(int c = 0; c < polys.size(); c++){
                    OGRGeometry* poly = polys.at(c);
                    srand((unsigned)time(NULL));
                    for(int d = 0; d < size_1; d++){
                        ObjectPt* p = o.at(d);
                        OGRGeometry* pt = p->opt;
                        if(pt->Intersects(poly)){
                            a.at(q) = d;
                            q++;
                        }
                    }
                }

                // Shuffle
                this->Shuffle(a, count, 2000);

                // Create the sampling layer
                if(n + 1 <= count && m < remainder){
                    for(int d = 0; d < n + 1; d++){
                        SamplingPt* sp = new SamplingPt();
                        ObjectPt* opt = o.at(a.at(d));
                        sp->spt = opt->opt;
                        sp->weight = opt->weight;
                        this->AddPoint(sp);
                    }
                    m++;
                }
                else{
                    for(int d = 0; d < n; d++){
                        SamplingPt* sp = new SamplingPt();
                        ObjectPt* opt = o.at(a.at(d));
                        sp->spt = opt->opt;
                        sp->weight = opt->weight;
                        this->AddPoint(sp);
                    }
                }
            }
        }
        else{   // When divisible
            for(int b = 0; b < size_2; b++){

                KnowledgeUnit* ku = k.at(b);
                vector<OGRGeometry*> polys = ku->kunit;

                // Calculate the population size in each stratum
                count = 0;
                for(int c = 0; c < polys.size(); c++){
                    OGRGeometry* poly = polys.at(c);
                    for(int d = 0; d < size_1; d++){
                        ObjectPt* p = o.at(d);
                        OGRGeometry* pt = p->opt;
                        if(pt->Intersects(poly))
                            count++;
                    }
                }

                // Initialize the array
                int q = 0;
                vector<int >a(count + 1);
                for(int c = 0; c < polys.size(); c++){
                    OGRGeometry* poly = polys.at(c);
                    srand((unsigned)time(NULL));
                    for(int d = 0; d < size_1; d++){
                        ObjectPt* p = o.at(d);
                        OGRGeometry* pt = p->opt;
                        if(pt->Intersects(poly)){
                            a.at(q) = d;
                            q++;
                        }
                    }
                }

                // Shuffle
                this->Shuffle(a, count, 2000);

                // Create the sampling layer
                for(int d = 0; d < n; d++){
                    SamplingPt* sp = new SamplingPt();
                    ObjectPt* opt = o.at(a.at(d));
                    sp->spt = opt->opt;
                    sp->weight = opt->weight;
                    this->AddPoint(sp);
                }
            }
        }
        t = 1;
    }else{
        qCritical()<< "The sampling number has exceeded the maximum allowable sample size.";
        t = 2;
    }
    return t;
}


/// <summary>
/// Stratified random sampling (proportional)
/// </summary>
/// <param name="o">        Collection of population units      </param name>
/// <param name="size_1">     Number of the population units      </param name>
/// <param name="k">        Collection of strata            </param name>
/// <param name="size_2">   Number of strata                </param name>
/// <param name="num">      Sample size                     </param name>
int SamplingVector::StratifiedSamplingPA(vector<ObjectPt *> o, int size_1, vector<KnowledgeUnit *> k, int size_2, int NT, int num)
{
    qInfo()<< "Stratified random sampling (proportional allocation)...";

    int t = 999;
    int n = 0;
    int count = 0;
    int totalNum = 0;

    if(num <= size_1){

        for(int i = 0; i < size_2; i++){
            KnowledgeUnit* ku = k.at(i);
            n = num * ku->N / NT;
            totalNum = totalNum + n;
        }

        int remainder = num - totalNum;
        int m = 0;
        OGRGeometry* poly;

        if(remainder != 0){

            for(int b = 0; b < size_2; b++){

                KnowledgeUnit* ku = k.at(b);
                vector<OGRGeometry* > polys = ku->kunit;
                n = num * ku->N / NT;

                // Calculate the population size in each stratum
                count = 0;
                for(int c = 0; c < polys.size(); c++){
                    poly = polys.at(c);
                    for(int d = 0; d < size_1; d++){
                        ObjectPt* p = o.at(d);
                        OGRGeometry* pt = p->opt;
                        if(pt->Intersects(poly))
                            count++;
                    }
                }

                // Initialize the array
                int q = 0;
                vector<int >a(count + 1);
                for(int c = 0; c < polys.size(); c++){
                    poly = polys.at(c);
                    srand((unsigned)time(NULL));
                    for(int d = 0; d < size_1; d++){
                        ObjectPt* p = o.at(d);
                        OGRGeometry* pt = p->opt;
                        if(pt->Intersects(poly)){
                            a.at(q) = d;
                            q++;
                        }
                    }
                }

                // Shuffle
                this->Shuffle(a, count, 2000);

                // Create the sampling layer
                if(n + 1 <= count && m < remainder){
                    for(int d = 0; d < n + 1; d++){
                        SamplingPt* sp = new SamplingPt();
                        ObjectPt* opt = o.at(a.at(d));
                        sp->spt = opt->opt;
                        sp->weight = opt->weight;
                        this->AddPoint(sp);
                    }
                    m++;
                }
                else{
                    for(int d = 0; d < n; d++){
                        SamplingPt* sp = new SamplingPt();
                        ObjectPt* opt = o.at(a.at(d));
                        sp->spt = opt->opt;
                        sp->weight = opt->weight;
                        this->AddPoint(sp);
                    }
                }
            }
        }
        else{
            for(int b = 0; b < size_2; b++){

                KnowledgeUnit* ku = k.at(b);
                vector<OGRGeometry*> polys = ku->kunit;
                n = num * ku->N / NT;

                // Calculate the population size in each stratum
                count = 0;
                for(int c = 0; c < polys.size(); c++){
                    poly = polys.at(c);
                    for(int d = 0; d < size_1; d++){
                        ObjectPt* p = o.at(d);
                        OGRGeometry* pt = p->opt;
                        if(pt->Intersects(poly))
                            count++;
                    }
                }

                // Initialize the array
                int q = 0;
                vector<int >a(count + 1);
                for(int c = 0; c < polys.size(); c++){
                    poly = polys.at(c);
                    srand((unsigned)time(NULL));
                    for(int d = 0; d < size_1; d++){
                        ObjectPt* p = o.at(d);
                        OGRGeometry* pt = p->opt;
                        if(pt->Intersects(poly)){
                            a.at(q) = d;
                            q++;
                        }
                    }
                }

                // Shuffle
                this->Shuffle(a, count, 2000);

                // Create the sampling layer
                for(int d = 0; d < n; d++){
                    SamplingPt* sp = new SamplingPt();
                    ObjectPt* opt = o.at(a.at(d));
                    sp->spt = opt->opt;
                    sp->weight = opt->weight;
                    this->AddPoint(sp);
                }
            }
        }
        t = 1;
    }else{
        qCritical()<< "The sampling number has exceeded the population size.";
        t = 0;
    }
    return t;
}


/// <summary>
/// Stratified random sampling (optimum)
/// </summary>
/// <param name="o">        Collection of population units      </param name>
/// <param name="size_1">     Number of the population units      </param name>
/// <param name="k">        Collection of strata            </param name>
/// <param name="size_2">   Number of strata                </param name>
/// <param name="num">      Sample size                     </param name>
int SamplingVector::StratifiedSamplingOA(vector<ObjectPt *> o, int size_1, vector<KnowledgeUnit *> k, int size_2, int num)
{
    qInfo()<< "Stratified random sampling (optimum allocation)...";

    int t = 999;
    int n = 0;
    int count = 0;
    int totalNum = 0;
    double sum = 0;

    // Calculate the max allowable sample size
    int nmax = MaxSampleSizeEA(o, size_1, k, size_2);
    int ss = 0;

    for(int i = 0; i < size_2; i++){
        KnowledgeUnit* ku = k.at(i);
        sum = sum + ku->N * pow(ku->varianceT, 0.5);
    }
    for(int i = 0; i < size_2; i++){
        KnowledgeUnit* ku = k.at(i);
        ss = ku->N * pow(ku->varianceT, 0.5) * num / sum;
        if(ss > nmax)
            break;
    }
    if(ss > nmax){
        qCritical()<< "The sampling number has exceeded the maximum allowable sample size.";
        t = 2;
        return t;
    }

    if(num <= size_1){

        for(int i = 0; i < size_2; i++){
            KnowledgeUnit* ku = k.at(i);
            totalNum = totalNum + ku->N * pow(ku->varianceT, 0.5) * num / sum;
        }

        int remainder = num - totalNum;
        int m = 0;
        OGRGeometry* poly;

        if(remainder != 0){

            for(int b = 0; b < size_2; b++){

                KnowledgeUnit* ku = k.at(b);
                vector<OGRGeometry*> polys = ku->kunit;
                n = ku->N * pow(ku->varianceT, 0.5) * num / sum;

                // Calculate the population size in each stratum
                count = 0;
                for(int c = 0; c < polys.size(); c++){
                    poly = polys.at(c);
                    for(int d = 0; d < size_1; d++){
                        ObjectPt* p = o.at(d);
                        OGRGeometry* pt = p->opt;
                        if(pt->Intersects(poly))
                            count++;
                    }
                }

                // Initialize the array
                int q = 0;
                vector<int >a(count + 1);
                for(int c = 0; c < polys.size(); c++){
                    poly = polys.at(c);
                    srand((unsigned)time(NULL));
                    for(int d = 0; d < size_1; d++){
                        ObjectPt* p = o.at(d);
                        OGRGeometry* pt = p->opt;
                        if(pt->Intersects(poly)){
                            a.at(q) = d;
                            q++;
                        }
                    }
                }

                // Shuffle
                this->Shuffle(a, count, 2000);

                // Create the sampling layer
                if(n + 1 <= count && m < remainder){
                    for(int d = 0; d < n + 1; d++){
                        SamplingPt* sp = new SamplingPt();
                        int temp = a.at(d);
                        ObjectPt* opt = o.at(temp);
                        sp->spt = opt->opt;
                        sp->weight = opt->weight;
                        this->AddPoint(sp);
                    }
                    m++;
                }else{
                    for(int d = 0; d < n; d++){
                        SamplingPt* sp = new SamplingPt();
                        int temp = a.at(d);
                        ObjectPt* opt = o.at(temp);
                        sp->spt = opt->opt;
                        sp->weight = opt->weight;
                        this->AddPoint(sp);
                    }
                }
            }
        }
        else{
            for(int b = 0; b < size_2; b++){

                KnowledgeUnit* ku = k.at(b);
                vector<OGRGeometry*> polys = ku->kunit;
                n = ku->N * pow(ku->varianceT, 0.5) * num / sum;

                // Calculate the population size in each stratum
                count = 0;
                for(int c = 0; c < polys.size(); c++){
                    poly = polys.at(c);
                    for(int d = 0; d < size_1; d++){
                        ObjectPt* p = o.at(d);
                        OGRGeometry* pt = p->opt;
                        if(pt->Intersects(poly))
                            count++;
                    }
                }

                // Initialize the array
                int q = 0;
                vector<int >a(count + 1);
                for(int c = 0; c < polys.size(); c++){
                    poly = polys.at(c);
                    srand((unsigned)time(NULL));
                    for(int d = 0; d < size_1; d++){
                        ObjectPt* p = o.at(d);
                        OGRGeometry* pt = p->opt;
                        if(pt->Intersects(poly)){
                            a.at(q) = d;
                            q++;
                        }
                    }
                }

                // Shuffle
                this->Shuffle(a, count, 2000);

                // Create the sampling layer
                for(int d = 0; d < n; d++){
                    SamplingPt* sp = new SamplingPt();
                    int temp = a.at(d);
                    ObjectPt* opt = o.at(temp);
                    sp->spt = opt->opt;
                    sp->weight = opt->weight;
                    this->AddPoint(sp);
                }
            }
        }
        t = 1;
    }else{
        qCritical()<< "The sampling number has exceeded the population size.";
        t = 0;
    }
    return t;
}

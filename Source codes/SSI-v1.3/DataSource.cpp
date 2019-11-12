#include "DataSource.h"

DataSource::DataSource()
{
    this->objG = 0x00;
    this->objV = 0x00;
    this->splG = 0x00;
    this->splV = 0x00;
    this->stfG = 0x00;
    this->stfV = 0x00;
    this->rptLyr = 0x00;

    logInit();
}


DataSource::~DataSource()
{
    if (this->objV != 0x00){
        delete objV;
        objV = 0x00;
    }
    if (this->objG != 0x00){
        delete objG;
        objG = 0x00;
    }

    if (this->splV != 0x00){
        delete splV;
        splV = 0x00;
    }
    if (this->splG != 0x00){
        delete splG;
        splG = 0x00;
    }

    if (this->stfV!= 0x00){
        delete stfV;
        stfV = 0x00;
    }
    if (this->stfG!= 0x00){
        delete stfG;
        stfG = 0x00;
    }

    if (this->rptLyr != 0x00){
        delete rptLyr;
        rptLyr = 0x00;
    }
}


/// <summary>
/// Read the population layer
/// </summary>
/// <param name="readObjectLayerPath">  Input path of the population layer  </param name>
/// <param name="code">                 Mark for data type                  </param name>
int DataSource::ReadObjectLayer(QString readObjectLayerPath, int code)
{
    qInfo()<< "Reading object layer...";

    int k = 999;
    if(code == 0){
        this->objV = new ObjectVector();
        k = this->ReadObjectLayerV(readObjectLayerPath);
    }
    else if(code == 1){
        this->objG = new ObjectRaster();
        k = this->ReadObjectLayerG(readObjectLayerPath);
    }
    return k;
}


/// <summary>
/// Read the population layer (vector point)
/// </summary>
/// <param name="readObjectLayerPath">  Input path of the population layer  </param name>
int DataSource::ReadObjectLayerV(QString readObjectLayerPath)
{
    int k = 999;
    string str = readObjectLayerPath.toStdString();
    const char* path = str.c_str();

    GDALAllRegister();
    GDALDataset* poDS;
    poDS = (GDALDataset*) GDALOpenEx(path, GDAL_OF_VECTOR, NULL, NULL, NULL);
    if(poDS == NULL){
        qCritical()<< "The input object layer was empty.";
        GDALClose(poDS);
        return k;
    }

    // Get the MBR of the population layer
    OGRLayer* poLayer = poDS->GetLayer(0);
    OGREnvelope* poEnvelope = new OGREnvelope();
    poLayer->GetExtent(poEnvelope);
    double minx = poEnvelope->MinX;
    this->objV->minx = minx;
    double miny = poEnvelope->MinY;
    this->objV->miny = miny;
    double maxx = poEnvelope->MaxX;
    this->objV->maxx = maxx;
    double maxy = poEnvelope->MaxY;
    this->objV->maxy = maxy;
    delete poEnvelope;

    // Get the metadata
    poLayer->ResetReading();
    this->objV->number =(int) poLayer->GetFeatureCount();
    OGRFeatureDefn* poFDefn = poLayer->GetLayerDefn();

    int count_1 = 0;
    int count_2 = 0;
    for(int iField = 0; iField < poFDefn->GetFieldCount(); iField++){
        OGRFieldDefn* poFieldDefn = poFDefn->GetFieldDefn(iField);
        if(poFieldDefn->GetType() == OFTInteger){
            const char* ch = poFieldDefn->GetNameRef();
            QString str = QString(QLatin1String(ch));
            this->objV->attrI.push_back(str);
            count_1++;
        }
        else if(poFieldDefn->GetType() == OFTReal){
            const char* ch = poFieldDefn->GetNameRef();
            QString str = QString(QLatin1String(ch));
            this->objV->attrD.push_back(str);
            count_2++;
        }
    }
    this->objV->countI = count_1;
    this->objV->countD = count_2;

    OGRFeature* poFeature;
    while((poFeature = poLayer->GetNextFeature()) != NULL){
        ObjectPt* op = new ObjectPt();
        int I = 0;
        double D = 0;
        // Get the attribute
        for(int iField = 0; iField < poFDefn->GetFieldCount(); iField++){
            OGRFieldDefn* poFieldDefn = poFDefn->GetFieldDefn(iField);
            if(poFieldDefn->GetType() == OFTInteger){
                I = poFeature->GetFieldAsInteger(iField);
                op->valueI.push_back(I);
            }else if(poFieldDefn->GetType() == OFTReal){
                D = poFeature->GetFieldAsInteger(iField);
                op->valueD.push_back(D);
            }
        }

        // Get the geometry
        OGRGeometry* poGeometry = poFeature->GetGeometryRef();
        if(poGeometry != NULL
                && wkbFlatten(poGeometry->getGeometryType()) == wkbPoint){
            OGRPoint* poPoint = new OGRPoint();
            poPoint = (OGRPoint* ) poGeometry;
            op->opt = poPoint;
            k = 1;
        }else{
            qCritical()<< "Geometry of the object layer was not point.";
            k = 0;
            return k;
        }

        objV->AddPoint(op);
    }
    GDALClose(poDS);
    return k;
}


/// <summary>
/// Read the population layer (raster)
/// </summary>
/// <param name="readObjectLayerPath">  Input path of the population layer  </param name>
int DataSource::ReadObjectLayerG(QString readObjectLayerPath)
{
    int k = 999;
    string str = readObjectLayerPath.toStdString();
    const char* path = str.c_str();

    // Open the raster file
    GDALAllRegister();
    GDALDataset *poDataset = (GDALDataset *)GDALOpen(path, GA_ReadOnly);
    if(poDataset == NULL){
        qCritical()<< "The input object layer was empty.";
        return k;
    }

    // Get the bands ofthe raster
    if(poDataset->GetRasterCount() != 1){
        qCritical()<< "The input object layer should contain 1 band.";
        k = 2;
        return k;
    }
    GDALRasterBand* poBand = poDataset->GetRasterBand(1);
    double noDataValue = poBand->GetNoDataValue();
    objG->noDataValue = noDataValue;

    // Read the raster data
    int nXSize = poBand->GetXSize();
    objG->nXSize = nXSize;
    int nYSize = poBand->GetYSize();
    objG->nYSize = nYSize;
    if(nXSize != 0 && nYSize != 0){
        for(int i = 0; i < nYSize; i++){
            double* pafScanline = (double* ) CPLMalloc(sizeof(double)* nXSize);
            poBand->RasterIO(GF_Read, 0, i, nXSize, 1, pafScanline, nXSize, 1, GDT_Float64, 0, 0);

            vector<double>* gX = new vector<double>();
            for(int j = 0; j < nXSize; j++){
                double v = *(pafScanline + j);
                gX->push_back(v);
            }
            objG->grids.push_back(gX);
            CPLFree(pafScanline);
        }
        k = 1;
    }
    GDALClose(poDataset);
    return k;
}


/// <summary>
/// Read the sampling layer
/// </summary>
/// <param name="readSamplingLayerPath">    Input path of the sampling layer    </param name>
/// <param name="weightedField">            Sampling field                      </param name>
/// <param name="code">                     Mark for data type                  </param name>
int DataSource::ReadSamplingLayer(QString readSamplingLayerPath, QString field, int code)
{
    qInfo()<< "Reading sampling layer...";

    int k = 999;
    if(code == 0){
        this->splV = new SamplingVector();
        k = this->ReadSamplingLayerV(readSamplingLayerPath, field);
    }
    else if(code == 1){
        this->splG = new SamplingRaster();
        k = this->ReadSamplingLayerG(readSamplingLayerPath);
    }
    return k;
}


/// <summary>
/// Read the sampling layer (vector point)
/// </summary>
/// <param name="readSamplingLayerPath">    Input path of the sampling layer    </param name>
/// <param name="weightedField">            Sampling field                      </param name>
int DataSource::ReadSamplingLayerV(QString readSamplingLayerPath, QString weightedField)
{
    int k = 999;
    string str = readSamplingLayerPath.toStdString();
    const char* path = str.c_str();

    GDALAllRegister();
    GDALDataset* poDS;
    poDS = (GDALDataset*) GDALOpenEx(path, GDAL_OF_VECTOR, NULL, NULL, NULL);
    if(poDS == NULL){
        qCritical()<< "The input sampling layer was empty.";
        GDALClose(poDS);
        return k;
    }

    // Get the MBR of the sampling layer
    OGRLayer* poLayer = poDS->GetLayer(0);
    OGREnvelope* poEnvelope = new OGREnvelope();
    poLayer->GetExtent(poEnvelope);
    double minx = poEnvelope->MinX;
    this->splV->minx = minx;
    double miny = poEnvelope->MinY;
    this->splV->miny = miny;
    double maxx = poEnvelope->MaxX;
    this->splV->maxx = maxx;
    double maxy = poEnvelope->MaxY;
    this->splV->maxy = maxy;
    delete poEnvelope;

    poLayer->ResetReading();
    this->splV->number =(int) poLayer->GetFeatureCount();
    OGRFeature* poFeature;
    while((poFeature = poLayer->GetNextFeature()) != NULL){
        SamplingPt* sp = new SamplingPt();

        // Get the attributes
        string field =  weightedField.toStdString();
        if(field.empty() == FALSE){
            OGRFeatureDefn* poFDefn = poLayer->GetLayerDefn();
            int iField;
            for(iField = 0; iField < poFDefn->GetFieldCount(); iField++){
                OGRFieldDefn* poFieldDefn = poFDefn->GetFieldDefn(iField);
                if(poFieldDefn->GetNameRef() == field){
                    if(poFieldDefn->GetType() == OFTInteger){
                        sp->weight = (double)poFeature->GetFieldAsInteger(iField);break;}
                    else if(poFieldDefn->GetType() == OFTReal){
                        sp->weight = poFeature->GetFieldAsDouble(iField);break;}
                }
            }
        }

        // Get the geometry
        OGRGeometry* poGeometry = poFeature->GetGeometryRef();
        if(poGeometry != NULL
                && wkbFlatten(poGeometry->getGeometryType()) == wkbPoint){
            OGRPoint* poPoint = new OGRPoint();
            poPoint = (OGRPoint* ) poGeometry;

            sp->spt = poPoint;
        }
        else{
            qCritical()<< "Geometry of the sampling layer was not point.";
            k = 0;
            return k;
        }

        k = 1;
        splV->AddPoint(sp);
    }
    GDALClose(poDS);
    return k;
}


/// <summary>
/// Read the sampling layer (raster)
/// </summary>
/// <param name="readSamplingLayerPath">    Input path of the sampling layer    </param name>
int DataSource::ReadSamplingLayerG(QString readSamplingLayerPath)
{
    int k = 999;
    return k;
}


/// <summary>
/// Distribute samples over the SSH layers
/// </summary>
/// <param name="objV">             Population layer        </param name>
/// <param name="size_1">           Population size         </param name>
/// <param name="k">                Collection of strata    </param name>
/// <param name="size_2">           Number of strata        </param name>
/// <param name="num">              Sample size             </param name>
/// <param name="type">             Sampling method         </param name>
/// <param name="weightedField">    Sampling field          </param name>
int DataSource::SamplingV(ObjectVector* objV, int size_1, vector<KnowledgeUnit *> k, int size_2, int num, int type, QString weightedField)
{
    int t = 999;
    // Setup the sampling weight
    int m = 0;
    int i, j;
    for(i = 0; i < objV->countI; i++){
        QString str = objV->attrI.at(i);
        if(str == weightedField){
            m = i + 1;
            break;
        }
    }
    if(m != 0){
        for(j = 0; j < objV->number; j++){
            ObjectPt* pt = objV->opts.at(j);
            pt->weight = pt->valueI.at(m - 1);
        }
    }else{
        for(i = 0; i < objV->countD; i++){
            QString str = objV->attrD.at(i);
            if(str == weightedField){
                m = i + 1;
                break;
            }
        }
        if(m != 0){
            for(j = 0; j < objV->number; j++){
                ObjectPt* pt = objV->opts.at(j);
                pt->weight = pt->valueD.at(m - 1);
            }
        }else{
            qCritical()<< "No available sampling field.";
            return t;
        }
    }

    // Generate the sampling layer
    this->splV = new SamplingVector();
    if(type == 1){
        this->splV->number = num;
        t = this->splV->SimpleRandomSampling(objV->opts, size_1, num);
    }
    else if(type == 2){
        this->splV->number = num;
        t = this->splV->StratifiedSamplingEA(objV->opts, size_1, k, size_2, num);
    }
    else if(type == 3){
        this->splV->number = num;
        this->stfV->CalculatePopulationSize(k, objV->opts, size_1);
        int NT = this->stfV->CalculateNT(k);
        t = this->splV->StratifiedSamplingPA(objV->opts, size_1, k, size_2, NT, num);
    }
    else if(type == 4){
        this->splV->number = num;
        this->stfV->CalculatePopulationSize(k, objV->opts, size_1);
        this->stfV->CalculateVarianceT(k, objV->opts, size_1);
        t = this->splV->StratifiedSamplingOA(objV->opts, size_1, k, size_2, num);
    }
    else{
        qCritical()<< "Failed to identify the sampling method.";
        return t;
    }

    // Get the MBR of the sampling layer
    if(t == 1){
        SamplingPt* sp = splV->spts.at(0);
        OGRPoint* p = (OGRPoint*)sp->spt;
        double minx = p->getX();
        double miny = p->getY();
        double maxx = p->getX();
        double maxy = p->getY();
        for(int i = 1; i < num; i++){
            sp = splV->spts.at(i);
            p = (OGRPoint*)sp->spt;
            double x = p->getX();
            double y = p->getY();

            if(minx > x)
                minx = x;
            if(maxx < x)
                maxx = x;
            if(miny > y)
                miny = y;
            if(maxy < y)
                maxy = y;
        }
        splV->maxx = maxx;
        splV->maxy = maxy;
        splV->minx = minx;
        splV->miny = miny;
    }

    return t;
}


/// <summary>
/// Read the SSH layer
/// </summary>
/// <param name="code">                         Mark for data type              </param name>
/// <param name="readStratifiedLayerPath">      Input path of the SSH layer     </param name>
int DataSource::ReadStratifiedLayer(QString readStratifiedLayerPath, int code, QString field)
{
    qInfo()<< "Reading stratified layer...";

    int k = 999;
    if(code == 0){
        this->stfV = new StratifiedVector();
        k = this->ReadStratifiedLayerV(readStratifiedLayerPath, field);
    }
    else if(code == 1){
        this->stfG = new StratifiedRaster();
        k = this->ReadStratifiedLayerG(readStratifiedLayerPath);
    }
    return k;
}


/// <summary>
/// Read the SSH layer (vector)
/// </summary>
/// <param name="readStratifiedLayerPath">      Input path of the SSH layer     </param name>
int DataSource::ReadStratifiedLayerV(QString readStratifiedLayerPath, QString field)
{
    int k = 999;
    string str = readStratifiedLayerPath.toStdString();
    const char* path = str.c_str();

    GDALAllRegister();
    GDALDataset* poDS;
    poDS = (GDALDataset*) GDALOpenEx(path, GDAL_OF_VECTOR, NULL, NULL, NULL);
    if(poDS == NULL){
        qCritical()<< "The input stratified layer was empty.";
        GDALClose(poDS);
        return k;
    }

    // Get the MBR of the SSH layer
    OGRLayer* poLayer = poDS->GetLayer(0);
    OGREnvelope* poEnvelope = new OGREnvelope();
    poLayer->GetExtent(poEnvelope);
    double minx = poEnvelope->MinX;
    this->stfV->minx = minx;
    double miny = poEnvelope->MinY;
    this->stfV->miny = miny;
    double maxx = poEnvelope->MaxX;
    this->stfV->maxx = maxx;
    double maxy = poEnvelope->MaxY;
    this->stfV->maxy = maxy;
    delete poEnvelope;

    poLayer->ResetReading();

    // Initialize
    vector<int> ids;
    int id = 0;
    OGRFeature* poFeature = poLayer->GetNextFeature();
    OGRGeometry* poGeometry = poFeature->GetGeometryRef();
    if(poGeometry != NULL
            && wkbFlatten(poGeometry->getGeometryType()) == wkbPolygon){
        string f =  field.toStdString();
        if(f.empty() == FALSE){
            OGRFeatureDefn* poFDefn = poLayer->GetLayerDefn();
            int iField;
            for(iField = 0; iField < poFDefn->GetFieldCount(); iField++){
                OGRFieldDefn* poFieldDefn = poFDefn->GetFieldDefn(iField);
                string s = poFieldDefn->GetNameRef();
                if(s == f){
                    if(poFieldDefn->GetType() == OFTInteger){
                        id = poFeature->GetFieldAsInteger(iField);break;}
                }
            }
        }
        KnowledgeUnit* ku = new KnowledgeUnit();
        // Get the stratum ID
        ku->id = id;
        // Get the geometry
        OGRPolygon* poPolygon = new OGRPolygon();
        poPolygon = (OGRPolygon* ) poGeometry;
        ku->kunit.push_back(poPolygon);
        ku->area = poPolygon->get_Area() / 1000000;
        stfV->AddUnit(ku);
        ids.push_back(id);
    }else if(poGeometry != NULL
             && wkbFlatten(poGeometry->getGeometryType()) == wkbMultiPolygon){
        string f =  field.toStdString();
        if(f.empty() == FALSE){
            OGRFeatureDefn* poFDefn = poLayer->GetLayerDefn();
            int iField;
            for(iField = 0; iField < poFDefn->GetFieldCount(); iField++){
                OGRFieldDefn* poFieldDefn = poFDefn->GetFieldDefn(iField);
                string s = poFieldDefn->GetNameRef();
                if(s == f){
                    if(poFieldDefn->GetType() == OFTInteger){
                        id = poFeature->GetFieldAsInteger(iField);break;}
                }
            }
        }
        KnowledgeUnit* ku = new KnowledgeUnit();
        // Get the stratum ID
        ku->id = id;
        // Get the geometry
        OGRMultiPolygon* pMulPolygon = (OGRMultiPolygon*)poGeometry;
        for(int i = 0; i < pMulPolygon->getNumGeometries(); i++){
            OGRPolygon* poPolygon = new OGRPolygon();
            poPolygon = (OGRPolygon* )pMulPolygon->getGeometryRef(i);
            ku->kunit.push_back(poPolygon);
            ku->area = ku->area + poPolygon->get_Area() / 1000000;
        }
        stfV->AddUnit(ku);
        ids.push_back(id);
    }else{
        qCritical()<< "Geometry of the stratified layer was not polygon.";
        k = 0;
        return k;
    }

    // Read the SSH layer
    while((poFeature = poLayer->GetNextFeature()) != NULL){
        poGeometry = poFeature->GetGeometryRef();

        if(poGeometry != NULL
                && wkbFlatten(poGeometry->getGeometryType()) == wkbPolygon){
            string f =  field.toStdString();
            if(f.empty() == FALSE){
                OGRFeatureDefn* poFDefn = poLayer->GetLayerDefn();
                int iField;
                for(iField = 0; iField < poFDefn->GetFieldCount(); iField++){
                    OGRFieldDefn* poFieldDefn = poFDefn->GetFieldDefn(iField);
                    string s = poFieldDefn->GetNameRef();
                    if(s == f){
                        if(poFieldDefn->GetType() == OFTInteger){
                            id = poFeature->GetFieldAsInteger(iField);break;}
                    }
                }
            }
            // Check if the statum ID exists
            int ret;
            for(ret = 0; ret < ids.size(); ret++){
                if(ids.at(ret) == id)
                    break;
            }
            if(ret == ids.size()){  //Not
                KnowledgeUnit* ku = new KnowledgeUnit();
                // Get the statum ID
                ku->id = id;
                // Get the geometry
                OGRPolygon* poPolygon = new OGRPolygon();
                poPolygon = (OGRPolygon* ) poGeometry;
                ku->kunit.push_back(poPolygon);
                ku->area = poPolygon->get_Area() / 1000000;
                stfV->AddUnit(ku);
                ids.push_back(id);
            }else{
                KnowledgeUnit* ku = stfV->kunits.at(ret);
                // Get the geometry
                OGRPolygon* poPolygon = new OGRPolygon();
                poPolygon = (OGRPolygon* ) poGeometry;
                ku->kunit.push_back(poPolygon);
                ku->area = ku->area + poPolygon->get_Area() / 1000000;
            }
            k = 1;
        }else if(poGeometry != NULL
                 && wkbFlatten(poGeometry->getGeometryType()) == wkbMultiPolygon){
            string f =  field.toStdString();
            if(f.empty() == FALSE){
                OGRFeatureDefn* poFDefn = poLayer->GetLayerDefn();
                int iField;
                for(iField = 0; iField < poFDefn->GetFieldCount(); iField++){
                    OGRFieldDefn* poFieldDefn = poFDefn->GetFieldDefn(iField);
                    string s = poFieldDefn->GetNameRef();
                    if(s == f){
                        if(poFieldDefn->GetType() == OFTInteger){
                            id = poFeature->GetFieldAsInteger(iField);break;}
                    }
                }
            }
            // Check if the statum ID exists
            int ret;
            for(ret = 0; ret < ids.size(); ret++){
                if(ids.at(ret) == id)
                    break;
            }
            if(ret == ids.size()){
                KnowledgeUnit* ku = new KnowledgeUnit();
                // Get the statum ID
                ku->id = id;
                // Get the geometry
                OGRMultiPolygon* pMulPolygon = (OGRMultiPolygon*)poGeometry;
                for(int i = 0; i < pMulPolygon->getNumGeometries(); i++){
                    OGRPolygon* poPolygon = new OGRPolygon();
                    poPolygon = (OGRPolygon* )pMulPolygon->getGeometryRef(i);
                    ku->kunit.push_back(poPolygon);
                    ku->area = ku->area + poPolygon->get_Area() / 1000000;
                }
                stfV->AddUnit(ku);
                ids.push_back(id);
            }else{
                KnowledgeUnit* ku = stfV->kunits.at(ret);
                // Get the geometry
                OGRMultiPolygon* pMulPolygon = (OGRMultiPolygon*)poGeometry;
                for(int i = 0; i < pMulPolygon->getNumGeometries(); i++){
                    OGRPolygon* poPolygon = new OGRPolygon();
                    poPolygon = (OGRPolygon* )pMulPolygon->getGeometryRef(i);
                    ku->kunit.push_back(poPolygon);
                    ku->area = ku->area + poPolygon->get_Area() / 1000000;
                }
            }
            k = 1;
        }else{
            qCritical()<< "Geometry of the stratified layer was not polygon.";
            k = 0;
            return k;
        }
    }

    this->stfV->number = ids.size();
    GDALClose(poDS);
    return k;
}


/// <summary>
/// Read the SSH layer (raster)
/// </summary>
/// <param name="readStratifiedLayerPath">      Input path of the SSH layer     </param name>
int DataSource::ReadStratifiedLayerG(QString readStratifiedLayerPath)
{
    int k = 999;
    string str = readStratifiedLayerPath.toStdString();
    const char* path = str.c_str();

    // Open the raster data
    GDALAllRegister();
    GDALDataset *poDataset = (GDALDataset *)GDALOpen(path, GA_ReadOnly);
    if(poDataset == NULL){
        qCritical()<< "The input stratified layer was empty.";
        return k;
    }

    // Get the bands
    if(poDataset->GetRasterCount() != 1){
        qCritical()<< "The input stratified layer should contain 1 band.";
        k = 2;
        return k;
    }
    GDALRasterBand* poBand = poDataset->GetRasterBand(1);
    double noDataValue = poBand->GetNoDataValue();
    stfG->noDataValue = noDataValue;

    // Read the raster data
    int nXSize = poBand->GetXSize();
    stfG->nXSize = nXSize;
    int nYSize = poBand->GetYSize();
    stfG->nYSize = nYSize;

    if(nXSize != 0 && nYSize != 0){
        double v = noDataValue; // Initialize the raster values
        vector<int> ids;
        ids.push_back(v); // Initialize the stratum ID
        for(int i = 0; i < nYSize; i++){
            double* pafScanline = (double* ) CPLMalloc(sizeof(double)* nXSize);
            poBand->RasterIO(GF_Read, 0, i, nXSize, 1, pafScanline, nXSize, 1, GDT_Float64, 0, 0);

            vector<double>* gX = new vector<double>();
            for(int j = 0; j < nXSize; j++){
                v = *(pafScanline + j);
                gX->push_back(v);

                int ret;
                for(ret = 0; ret < ids.size(); ret++){
                    if(ids.at(ret) == v)
                        break;
                }
                if(ret == ids.size())  // Current stratum ID does not exist
                    ids.push_back(v);
            }
            stfG->grids.push_back(gX);
            CPLFree(pafScanline);
        }
        k = 1;
        stfG->ids = ids;
    }
    GDALClose(poDataset);
    return k;
}


/// <summary>
/// Read the reporting layer
/// </summary>
/// <param name="readReportingLayerPath">   Input path of the reporting layer     </param name>
int DataSource::ReadReportingLayer(QString readReportingLayerPath)
{
    qInfo()<< "Reading reporting layer...";

    int k = 999;
    this->rptLyr = new ReportingLayer();
    k = this->ReadReportingLayerV(readReportingLayerPath);

    return k;
}


/// <summary>
/// Read the reporting layer (vector)
/// </summary>
/// <param name="readReportingLayerPath">   Input path of the reporting layer     </param name>
int DataSource::ReadReportingLayerV(QString readReportingLayerPath)
{
    int k = 999;
    string str = readReportingLayerPath.toStdString();
    const char* path = str.c_str();

    GDALAllRegister();
    GDALDataset* poDS;
    poDS = (GDALDataset*) GDALOpenEx(path, GDAL_OF_VECTOR, NULL, NULL, NULL);
    if(poDS == NULL){
        qCritical()<< "The input reporting layer was empty.";
        GDALClose(poDS);
        return k;
    }

    // Get the MBR of the reporting layer
    OGRLayer* poLayer = poDS->GetLayer(0);
    OGREnvelope* poEnvelope = new OGREnvelope();
    poLayer->GetExtent(poEnvelope);
    double minx = poEnvelope->MinX;
    this->rptLyr->minx = minx;
    double miny = poEnvelope->MinY;
    this->rptLyr->miny = miny;
    double maxx = poEnvelope->MaxX;
    this->rptLyr->maxx = maxx;
    double maxy = poEnvelope->MaxY;
    this->rptLyr->maxy = maxy;
    delete poEnvelope;

    poLayer->ResetReading();
    this->rptLyr->number = (int) poLayer->GetFeatureCount();
    OGRFeature* poFeature;
    while((poFeature = poLayer->GetNextFeature()) != NULL){
        OGRGeometry* poGeometry = poFeature->GetGeometryRef();
        if(poGeometry != NULL
                && wkbFlatten(poGeometry->getGeometryType()) == wkbPolygon){
            // Get the geometry
            ReportingUnit* ru = new ReportingUnit();
            OGRPolygon* poPolygon = new OGRPolygon();
            poPolygon = (OGRPolygon* ) poGeometry;

            ru->runit.push_back(poPolygon);
            ru->area = poPolygon->get_Area() / 1000000;

            rptLyr->runits.push_back(ru);
            k = 1;
        }else if(poGeometry != NULL
                 && wkbFlatten(poGeometry->getGeometryType()) == wkbMultiPolygon){
            // Get the geometry
            ReportingUnit* ru = new ReportingUnit();
            OGRMultiPolygon* pMulPolygon = (OGRMultiPolygon*)poGeometry;
            for(int i = 0; i < pMulPolygon->getNumGeometries(); i++){
                OGRPolygon* poPolygon = new OGRPolygon();
                poPolygon = (OGRPolygon* )pMulPolygon->getGeometryRef(i);
                ReportingUnit* ru = new ReportingUnit();
                ru->runit.push_back(poPolygon);
                ru->area = ru->area + poPolygon->get_Area() / 1000000;
            }
            rptLyr->runits.push_back(ru);
            k = 1;
        }else{
            qCritical()<< "Geometry of the reporting layer was not polygon.";
            k = 0;
            return k;
        }
    }
    GDALClose(poDS);
    return k;
}

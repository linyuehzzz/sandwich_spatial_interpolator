#include "DataOutput.h"

DataOutput::DataOutput()
{
    logInit();
}

DataOutput::~DataOutput()
{

}

/// <summary>
/// Write the summary report
/// </summary>
/// <param name="code_1">   Mark for the data type                      </param name>
/// <param name="objV">     Population layer                            </param name>
/// <param name="code_2">   Mark if the sampling layer exists or not    </param name>
/// <param name="code_3">   Mark for the sampling method                </param name>
/// <param name="n_2">      Sample size                                 </param name>
/// <param name="field">    Sampling field                              </param name>
/// <param name="n_3">      Number of strata                            </param name>
/// <param name="q">        Geodetector q-statistic                     </param name>
/// <param name="n_4">      Number of the reporting units               </param name>
/// <param name="varianceT">    The total variance of sample            </param name>
/// <param name="code_4">   Mark if the population layer exists or not  </param name>
void DataOutput::WriteTXTFile(int code_1, ObjectVector *objV, int code_2, int code_3, int n_2, QString field, int n_3, double q, int n_4, double varianceT, int code_4)
{
    qInfo()<< "Writing summary of outputs...";

    string str = this->writeTXTPath.toStdString();
    const char* path = str.c_str();
    QFile file(path);
    if (!file.open(QFile::WriteOnly | QIODevice::Text)) {
        qCritical()<< "Failed to open the output txt file.";
        return ;
    }
    QTextStream out(&file);

    // Local time
    QDateTime local(QDateTime::currentDateTime());
    QString localTime = local.toString("yyyy-MM-dd:hh:mm:ss");
    out << "Sandwich << " << localTime.toStdString().c_str()<< endl;
    out << "----------------------------------------------------------------------------------------------" << endl;
    out << "*****************SUMMARY OF LAYERS*****************" << endl;
    out << "----------------------------------------------------------------------------------------------" << endl << endl;

    // Data type
    if(code_1 == 0)
        out << "DATA TYPE:  Vector" << endl;
    else if(code_1 == 1)
        out << "DATA TYPE:  Raster" << endl << endl;

    // Population layer
    if(code_4 == 1){
        out << "POPULATION LAYER " << endl;
        out << "Population size:  " << objV->number << endl;
    }else
        out << "POPULATION LAYER: NONE " << endl;
    out << "-------------------------------------------------------------------" << endl;

    // Sampling layer
    out << "SAMPLING LAYER " << endl;
    if(code_2 == 0){
        out << "Input option:   Create" << endl;
        if(code_3 == 1)
            out << "Sampling method:    Simple random sampling" << endl;
        else if(code_3 == 2)
            out << "Sampling method:    Stratified random sampling (equal allocation)" << endl;
        else if(code_3 == 3)
            out << "Sampling method:    Stratified random sampling (proportion allocation)" << endl;
        else if(code_3 == 4)
            out << "Sampling method:    Stratified random sampling (optimum allocation)" << endl;
    }
    else if(code_2 == 1)
        out << "Input option:   Load" << endl;
    out << "Sampling weight:    " << field.toStdString().c_str() << endl;
    out << "Sample size:    " << n_2 << endl;
    out << "Total variance of samples: " << varianceT << endl;
    out << "-------------------------------------------------------------------" << endl;

    // SSH layer
    out << "SSH LAYER " << endl;
    out << "Number of strata: " << n_3 << endl;
    out << "Geodetector q-statistic:    " << q << endl;
    out << "-------------------------------------------------------------------" << endl;

    // Reporting layer
    out << "REPORTING LAYER " << endl;
    out << "Number of the reporting units: " << n_4 << endl << endl << endl;
}


/// <summary>
/// Write the interpolated map
/// </summary>
/// <param name="r">    Collection of the reporting units      </param name>
void DataOutput::WriteSHPFile(vector<ReportingUnit *> r)
{
    GDALAllRegister();
    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "YES");

    const char* pszDriverName = "ESRI Shapefile";
    GDALDriver* poDriver = GetGDALDriverManager()->GetDriverByName(pszDriverName);

    string str_1 = this->writeSHPPath.toStdString();
    const char* path_1 = str_1.c_str();
    GDALDataset* poDS = poDriver->Create(path_1, 0, 0, 0, GDT_Unknown, NULL);

    string str_2 = this->rptPath.toStdString();
    const char* path_2 = str_2.c_str();
    GDALDataset* poSrc = (GDALDataset*) GDALOpenEx(path_2, GDAL_OF_VECTOR, NULL, NULL, NULL);
    OGRLayer* poLayer = poSrc->GetLayer(0);

    char** papszOptions = nullptr;
    poDS->CopyLayer(poLayer, "s", papszOptions);

    OGRLayer* outputLayer = poDS->GetLayer(0);
    OGRFieldDefn* fieldM = new OGRFieldDefn("Mean", OFTReal);
    OGRFieldDefn* fieldV = new OGRFieldDefn("VarSM", OFTReal);
    outputLayer->CreateField(fieldM,1);
    outputLayer->CreateField(fieldV,1);

    outputLayer->ResetReading();
    OGRFeature* feature = nullptr;
    while((feature = outputLayer->GetNextFeature()) != nullptr)
    {
        int id = feature->GetFID();
        ReportingUnit * ru = r.at(id);
        feature->SetField("Mean", ru->mean);
        feature->SetField("VarSM", ru->varianceSM);
        outputLayer->SetFeature(feature);
    }

    GDALClose(poDS);
}


/// <summary>
/// Draw the output layer
/// </summary>
void DataOutput::Draw()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor3f(0.7f, 0.0f, 0.0f);
    glLineWidth(3);
    for(int i = 0; i < number; i++)
    {
        ReportingUnit* ku = kunits.at(i);
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
                float x = (float)(point->x - minx)/ width * 2 - 1;
                float y = (float)(point->y - miny)/ height * 2 - 1;
                glVertex2f(x,y);
                delete point;
            }
            glEnd();
        }
    }
}

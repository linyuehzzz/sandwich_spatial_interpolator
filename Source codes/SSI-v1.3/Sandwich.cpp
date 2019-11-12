#include "Sandwich.h"

Sandwich::Sandwich()
{
    this->code_1 = 999;
    this->code_2 = 999;
    this->code_3 = 999;
    this->code_4 = 0;

    this->inputSampleSize = 0;

    this->d = new DataSource();
    this->o = new DataOutput();
    logInit();
}


Sandwich::~Sandwich()
{
    if (this->d != 0x00){
        delete d;
        d = 0x00;
    }
    if (this->o != 0x00){
        delete o;
        o = 0x00;
    }
}


/// <summary>
/// Run the Sandwich model
/// </summary>
void Sandwich::RunModel()
{
    qInfo()<< "'Sandwich' model starting...";

    if(this->code_1 == 0){

        // Calculate mean value and variance of sample mean of each stratum
        d->stfV->CalculateKUValue(d->objV, d->splV->spts, d->splV->number, this->code_4);
        // Calculate the geodetector q-statistic
        d->stfV->Calculateq(d->splV->spts, d->splV->number);

        // Calculate the mean value and the variance of sample mean of each reporting unit
        d->rptLyr->CalculateRUValue(d->stfV->kunits, d->stfV->number);
        d->rptLyr->CalculateVarianceT(d->splV->spts, d->splV->number);
    }
    else if(this->code_1 == 1){

    }
    else{
        qCritical()<< "Undefined object data type.";
        return ;
    }
}


/// <summary>
/// Generate the output files
/// </summary>
void Sandwich::WriteFile()
{
    o->rptPath = readReportingLayerPath;
    o->writeSHPPath = writeReportingLayerPath;
    o->writeTXTPath = writeTXTPath;

    o->WriteSHPFile(d->rptLyr->runits);
    o->WriteTXTFile(code_1, d->objV, code_2, code_3, d->splV->number, weightedField, d->stfV->number, d->stfV->q, d->rptLyr->number, d->rptLyr->VairanceT, code_4);

    qInfo()<< "'Sandwich' model finished";
}

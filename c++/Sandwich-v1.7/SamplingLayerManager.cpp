#include "SamplingLayerManager.h"

SamplingLayerManager::SamplingLayerManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SamplingLayerManager)
{
    ui->setupUi(this);

    this->code_1 = 999;
    this->code_2 = 999;
    this->code_3 = 999;

    this->sampleSize = 0;

    ui->splFields->setEnabled(FALSE);
    connect(ui->splFields, SIGNAL(activated(QString)), this, SLOT(ComboBoxValueChanged(QString)));
}

SamplingLayerManager::~SamplingLayerManager()
{
    delete ui;
}


/// <summary>
/// Input the sampling layer
/// </summary>
void SamplingLayerManager::on_load_clicked()
{
    this->code_2 = 1;

    QString filename;
    if(this->code_1 == 0){
        filename = QFileDialog::getOpenFileName(this,tr("Sampling layer"),"",tr("Vector data (*.shp)"));
        this->readSamplingLayerPath = filename;

        ui->splFields->setEnabled(TRUE);
        this->fields = GetFieldNames(filename);
        SetComboBoxValue();
    }else if(this->code_1 == 1){
        filename = QFileDialog::getOpenFileName(this,tr("Sampling layer"),"",tr("Vector data (*.shp)"));
        this->readSamplingLayerPath = filename;

        ui->splFields->setEnabled(TRUE);
        this->fields = GetFieldNames(filename);
        SetComboBoxValue();
    }
}


/// <summary>
/// Get the field names of the sampling layer
/// </summary>
/// <param name="path">     Input path of the sampling layer    </param name>
/// <returns>       Collection of field names     </returns>
vector<QString> SamplingLayerManager::GetFieldNames(QString path)
{
    string str = path.toStdString();
    const char* filename = str.c_str();

    vector<QString> v;
    GDALAllRegister();
    GDALDataset* poDS;
    poDS = (GDALDataset*) GDALOpenEx(filename, GDAL_OF_VECTOR, NULL, NULL, NULL);
    if(poDS == NULL){
        GDALClose(poDS);
        return vector<QString>();
    }

    OGRLayer* poLayer = poDS->GetLayer(0);
    poLayer->ResetReading();
    OGRFeatureDefn* poFDefn = poLayer->GetLayerDefn();
    for(int iField = 0; iField < poFDefn->GetFieldCount(); iField++){
        OGRFieldDefn* poFieldDefn = poFDefn->GetFieldDefn(iField);
        if(poFieldDefn->GetType() == OFTInteger || poFieldDefn->GetType() == OFTReal){
            const char* ch = poFieldDefn->GetNameRef();
            QString str = QString(QLatin1String(ch));
            v.push_back(str);
        }
    }
    GDALClose(poDS);
    return v;
}


/// <summary>
/// Set the initial field name of combo box
/// </summary>
void SamplingLayerManager::SetComboBoxValue()
{
    ui->splFields->clear();
    int size = this->fields.size();
    for(int i = 0; i < size; i++){
        QString field = fields.at(i);
        string str = field.toStdString();
        const char* item = str.c_str();
        ui->splFields->addItem(item);
    }
    this->selectedField = ui->splFields->currentText();
}


/// <summary>
/// Select a field name from combo box
/// </summary>
/// <param name="field">    Field name  </param name>
void SamplingLayerManager::ComboBoxValueChanged(QString field)
{
    this->selectedField = field;
}


/// <summary>
/// Create the sampling layer
/// </summary>
void SamplingLayerManager::on_create_clicked()
{
    this->code_2 = 0;

    if(code_1 == 0){
        if(this->readObjectLayerPath.isEmpty() || this->readStratifiedLayerPath.isEmpty())
            QMessageBox::warning(this,tr("Warning"),tr("Please input both the population layer and the SSH layer first."));
        else{
            // Connect the signal and slot
            this->samplingSettings = new SamplingSettings(this);
            connect(this->samplingSettings, SIGNAL(SendData(int, int)), this, SLOT(ReceiveData(int, int)));
            this->samplingSettings->show();
        }
    }else if(code_1 == 1){
        if(this->readObjectLayerPath.isEmpty() || this->readStratifiedLayerPath.isEmpty())
            QMessageBox::warning(this,tr("Warning"),tr("Please input both the population layer and the SSH layer first."));
        else{
            // Connect the signal and slot
            this->samplingSettings = new SamplingSettings(this);
            connect(this->samplingSettings, SIGNAL(SendData(int, int)), this, SLOT(ReceiveData(int, int)));
            this->samplingSettings->show();
        }
    }

}


/// <summary>
/// Close this dialog
/// </summary>
void SamplingLayerManager::on_Cancel_clicked()
{
    this->reject();
}


/// <summary>
/// Receive the data from the Sampling Settings window
/// </summary>
/// <param name="code_3">       Mark for sampling method        </param name>
/// <param name="sampleSize">   Sample size                     </param name>
void SamplingLayerManager::ReceiveData(int code_3, int sampleSize)
{
    this->code_3 = code_3;
    this->sampleSize = sampleSize;

    if(code_1 == 0){
        QString filename;
        ui->splFields->setEnabled(TRUE);
        filename = this->readObjectLayerPath;
        this->fields = GetFieldNames(filename);
        SetComboBoxValue();
    }
}


/// <summary>
/// Finish and send back the data
/// </summary>
void SamplingLayerManager::on_OK_clicked()
{
    int code_2 = this->code_2;
    QString field = this->selectedField;
    QString filename = this->readSamplingLayerPath;
    int code_3 = this->code_3;
    int size = this->sampleSize;

    if(code_2 != 0 && code_2 != 1)
        QMessageBox::warning(this,tr("Warning"),tr("Please choose an input option of the sampling layer."));
    else if(code_2 == 0){
        if(size == 0)
            QMessageBox::warning(this,tr("Warning"),tr("Please input the sampling size."));
        else{
            emit SendData(code_2, field, filename, code_3, size);
            this->accept();
        }
    }else{
        if(filename.isEmpty())
            QMessageBox::warning(this,tr("Warning"),tr("Please load the sampling layer."));
        else{
            emit SendData(code_2, field, filename, code_3, size);
            this->accept();
        }
    }
}

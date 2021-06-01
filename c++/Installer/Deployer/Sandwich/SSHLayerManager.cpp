#include "SSHLayerManager.h"
#include "ui_sshlayermanager.h"

SSHLayerManager::SSHLayerManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SSHLayerManager)
{
    ui->setupUi(this);

    ui->StratumID->setEnabled(FALSE);
}

SSHLayerManager::~SSHLayerManager()
{
    delete ui;
}


/// <summary>
/// Input the SSH layer
/// </summary>
void SSHLayerManager::on_strInput_clicked()
{
    QString filename;
    if(this->code_1 == 0){
        filename = QFileDialog::getOpenFileName(this,tr("SSH layer"),"",tr("Vector data (*.shp)"));
        this->readStratifiedLayerPath = filename;

        ui->StratumID->setEnabled(TRUE);
        this->fields = GetFieldNames(filename);
        SetComboBoxValue();
    }else{
        filename = QFileDialog::getOpenFileName(this,tr("SSH layer"),"",tr("Raster data (*.tif)"));
        this->readStratifiedLayerPath = filename;
    }
}


/// <summary>
/// Get all field names of the SSH layer
/// </summary>
/// <param name="path">     Input path of the SSH layer     </param name>
vector<QString> SSHLayerManager::GetFieldNames(QString path)
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
        if(poFieldDefn->GetType() == OFTInteger){
            const char* ch = poFieldDefn->GetNameRef();
            QString str = QString(QLatin1String(ch));
            v.push_back(str);
        }
    }
    GDALClose(poDS);
    return v;
}


/// <summary>
/// Set the initial field name of the combo box
/// </summary>
void SSHLayerManager::SetComboBoxValue()
{
    ui->StratumID->clear();
    int size = this->fields.size();
    for(int i = 0; i < size; i++){
        QString field = fields.at(i);
        string str = field.toStdString();
        const char* item = str.c_str();
        ui->StratumID->addItem(item);
    }
}


/// <summary>
/// Finish and send back the data
/// </summary>
void SSHLayerManager::on_Load_clicked()
{
    QString field = ui->StratumID->currentText();
    QString filename = this->readStratifiedLayerPath;

    emit SendData(field, filename);
    this->accept();

}


/// <summary>
/// Close this dialog
/// </summary>
void SSHLayerManager::on_Cancel_clicked()
{
    this->reject();
}

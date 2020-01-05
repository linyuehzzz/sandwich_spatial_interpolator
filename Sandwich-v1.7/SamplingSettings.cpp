#include "SamplingSettings.h"

SamplingSettings::SamplingSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SamplingSettings)
{
    ui->setupUi(this);

    this->code_3 = 999;
    this->populationSize = 0;

    SetComboBoxValue();
}

SamplingSettings::~SamplingSettings()
{
    delete ui;
}


/// <summary>
/// Set the initial sampling method of the combo box
/// </summary>
void SamplingSettings::SetComboBoxValue()
{
    ui->splMethod->addItem("Simple random sampling");
    ui->splMethod->addItem("Stratified random sampling (equal allocation)");
    ui->splMethod->addItem("Stratified random sampling (proportion allocation)");
    ui->splMethod->addItem("Stratified random sampling (optimum allocation)");
}


/// <summary>
/// Close this dialog
/// </summary>
void SamplingSettings::on_cancel_clicked()
{
    this->reject();
}


/// <summary>
/// Finish and send back the data
/// </summary>
void SamplingSettings::on_OK_clicked()
{
    int code_3 = ui->splMethod->currentIndex() + 1;
    int sampleSize = ui->splSize->text().toInt();
    emit SendData(code_3, sampleSize);
    this->accept();
}

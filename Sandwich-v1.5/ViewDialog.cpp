#include "ViewDialog.h"


ViewDialog::ViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewDialog)
{
    ui->setupUi(this);
}

ViewDialog::~ViewDialog()
{

    delete ui;
}

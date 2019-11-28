#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize the buttons
    ui->view_1->setEnabled(FALSE);
    ui->view_2->setEnabled(FALSE);
    ui->view_3->setEnabled(FALSE);
    ui->view_4->setEnabled(FALSE);
    ui->del_1->setEnabled(FALSE);
    ui->del_2->setEnabled(FALSE);
    ui->del_3->setEnabled(FALSE);
    ui->del_4->setEnabled(FALSE);

    // Setup the background color
    QPalette pal(ui->centralWidget->palette());
    pal.setColor(QPalette::Background, Qt::white); // white
    ui->centralWidget->setAutoFillBackground(true);
    ui->centralWidget->setPalette(pal);
    ui->centralWidget->show();

    // Initialize the model
    s = new Sandwich();
    tRM = NULL;
    tSpl = NULL;

    SetComboBoxValue();
    connect(ui->objType, SIGNAL(activated(int)), this, SLOT(ComboBoxValueChanged(int)));

    this->samplingLayerManager = new SamplingLayerManager(this);
    connect(this->samplingLayerManager, SIGNAL(SendData(int, QString, QString, int, int)), this, SLOT(ReceiveDataA(int, QString, QString, int, int)));

    this->stratifiedLayerManager = new SSHLayerManager(this);
    connect(this->stratifiedLayerManager, SIGNAL(SendData(QString, QString)), this, SLOT(ReceiveDataB(QString, QString)));
}


MainWindow::~MainWindow()
{
    delete ui;

    if(s != 0x00){
        delete s;
        s = 0x00;
    }
}


/// <summary>
/// Setup the initial value of combo box
/// </summary>
void MainWindow::SetComboBoxValue()
{
    ui->objType->addItem("Vector");
    ui->objType->addItem("Raster");
    s->code_1 = 0;  // default: vector
}


/// <summary>
/// Select a value from the combo box
/// </summary>
/// <param name="index">    Index  </param name>
void MainWindow::ComboBoxValueChanged(int index)
{
    if(index == 0)
        s->code_1 = 0;  // vector
    if(index == 1)
        s->code_1 = 1;  // raster
}


/// <summary>
/// Input the population layer
/// </summary>
void MainWindow::on_objLyr_clicked()
{
    QString filename;
    int k = 999;
    if(s->code_1 == 0){
        filename = QFileDialog::getOpenFileName(this,tr("Population layer"),"",tr("Vector data (*.shp)"));
        if(filename.isEmpty() == FALSE){
            s->readObjectLayerPath = filename;
            this->readObjectLayerPath = filename;
            k = this->s->d->ReadObjectLayer(this->readObjectLayerPath, s->code_1);
            s->code_4 = 1;
            if(k == 1){
                this->viewDlg = new ViewDialog(this);
                this->viewDlg->ui->openGLWidget->code = 1;
                this->viewDlg->ui->openGLWidget->objV = new ObjectVector();
                this->viewDlg->ui->openGLWidget->objV = s->d->objV;
                ui->view_1->setEnabled(TRUE);
                ui->del_1->setEnabled(TRUE);
                this->viewDlg->show();
            }
            else if(k == 0)
                QMessageBox::warning(this,tr("Warning"),tr("When the data type is VECTOR, geometry of the population layer should be POINT."));
            else if(k == 999)
                QMessageBox::warning(this,tr("Warning"),tr("Failed to open the population layer."));
        }
    }
    else if(s->code_1 == 1){
        filename = QFileDialog::getOpenFileName(this,tr("Population layer"),"",tr("Raster data (*.tif)"));
        if(filename.isEmpty() == FALSE){
            s->readObjectLayerPath = filename;
            this->readObjectLayerPath = filename;
            k = this->s->d->ReadObjectLayer(this->readObjectLayerPath, s->code_1);
            s->code_4 = 1;
            if(k == 1){
                this->viewDlg = new ViewDialog(this);
//                this->viewDlg->ui->openGLWidget->code = 5;
//                this->viewDlg->ui->openGLWidget->objG = new ObjectRaster();
//                this->viewDlg->ui->openGLWidget->objG = s->d->objG;
//                ui->view_1->setEnabled(TRUE);
//                this->viewDlg->show();
            }
            else if(k == 2)
                QMessageBox::warning(this,tr("Warning"),tr("The population layer should have SINGLE band (grey)."));
            else if(k == 999)
                QMessageBox::warning(this,tr("Warning"),tr("Failed to open the population layer."));
        }
    }
    else
        QMessageBox::warning(this,tr("Warning"),tr("Please select the data type."));
}


/// <summary>
/// pen the Sampling Layer Manager
/// </summary>
void MainWindow::on_splLyr_clicked()
{
    if(s->code_1 != 0 && s->code_1 != 1){
         QMessageBox::warning(this,tr("Warning"),tr("Please select the data type."));
    }else{
        this->samplingLayerManager->code_1 = s->code_1;
        if(s->readObjectLayerPath.isEmpty() == FALSE)
            this->samplingLayerManager->readObjectLayerPath = this->readObjectLayerPath;

        if(s->readStratifiedLayerPath.isEmpty() == FALSE)
            this->samplingLayerManager->readStratifiedLayerPath = this->readStratifiedLayerPath;
        this->samplingLayerManager->show();
    }
}


/// <summary>
/// Receive the data from the Sampling Layer Manager
/// </summary>
/// <param name="code_2">   Mark if the sampling layer exists or not    </param name>
/// <param name="field">    Sampling field                              </param name>
/// <param name="filename"> Input path of the sampling layer            </param name>
/// <param name="code_3">   Sampling method                             </param name>
/// <param name="size">     Sample size                                 </param name>
void MainWindow::ReceiveDataA(int code_2, QString field, QString filename, int code_3, int size)
{
    s->weightedField = field;
    s->readSamplingLayerPath = filename;
    s->code_3 = code_3;
    s->inputSampleSize = size;
    int t = 999;
    if(code_2 == 0){
        // Sampling
        tSpl = new ThreadSampling();
        tSpl->s = s;
        tSpl->size = size;
        tSpl->code_2 = code_2;
        tSpl->code_3 = code_3;
        tSpl->field = field;
        connect(tSpl, SIGNAL(SplStart()), this, SLOT(SplStart()));
        connect(tSpl, SIGNAL(SplEnd(int, int)), this, SLOT(SplEnd(int, int)));
        tSpl->start();
    }
    else if(code_2 == 1){
        if(filename.isEmpty() == FALSE){
            //Read the sampling layer
            s->code_2 = code_2;
            t = this->s->d->ReadSamplingLayer(filename, field, s->code_1);
            if(t == 1){
                this->viewDlg = new ViewDialog(this);
                this->viewDlg->ui->openGLWidget->code = 2;
                this->viewDlg->ui->openGLWidget->splV = new SamplingVector();
                this->viewDlg->ui->openGLWidget->splV = s->d->splV;
                ui->view_2->setEnabled(TRUE);
                ui->del_2->setEnabled(TRUE);
                this->viewDlg->show();
            }
            else if(t == 0)
                QMessageBox::warning(this,tr("Warning"),tr("When the data type is VECTOR, geometry of the sampling layer should be POINT."));
            else if(t == 999)
                QMessageBox::warning(this,tr("Warning"),tr("Failed to open the sampling layer."));
        }
    }
}


/// <summary>
/// Start sampling, and open the progress dialog
/// </summary>
void MainWindow::SplStart()
{
    progress = new QProgressDialog(this);
    progress->setWindowTitle(tr("Status"));
    progress->setLabelText(QStringLiteral("Sampling..."));
    progress->setCancelButton(0);
    progress->setModal(true);
    progress->setRange(0,100);
    progress->setMinimumDuration(0);

    timer = new QTimer();
    currentValue = 0;
    progress->setValue(currentValue);
    connect(timer, SIGNAL(timeout()), this, SLOT(UpdateProgressDialog()));
    timer->start(100);
}


/// <summary>
/// Close the progress dialog
/// </summary>
void MainWindow::SplEnd(int t, int code_2)
{
    timer->stop();
    if(currentValue != 100)
        currentValue = 100;
    progress->setValue(currentValue);
    progress->close();
    if(t == 1){
        this->viewDlg = new ViewDialog(this);
        this->viewDlg->ui->openGLWidget->code = 2;
        this->viewDlg->ui->openGLWidget->splV = new SamplingVector();
        this->viewDlg->ui->openGLWidget->splV = s->d->splV;
        ui->view_2->setEnabled(TRUE);
        ui->del_2->setEnabled(TRUE);
        this->viewDlg->show();
        s->code_2 = code_2;
    }
    else if(t == 2)
        QMessageBox::warning(this,tr("Warning"),tr("The input sample size should NOT exceed the maximum allowable sample size."));
    else if(t == 0)
        QMessageBox::warning(this,tr("Warning"),tr("The input sample size should NOT exceed the maximum allowable sample size."));
    else if(t == 999)
        QMessageBox::warning(this,tr("Warning"),tr("Failed to identify the sampling method or sampling field."));

}


/// <summary>
/// Input the SSH layer
/// </summary>
void MainWindow::on_stfLyr_clicked()
{
    if(s->code_1 != 0 && s->code_1 != 1){
         QMessageBox::warning(this,tr("Warning"),tr("Please select the data type."));
    }
    else if(s->code_1 == 0){
        this->stratifiedLayerManager->code_1 = s->code_1;
        this->stratifiedLayerManager->show();
    }else{
        this->stratifiedLayerManager->code_1 = s->code_1;
        this->stratifiedLayerManager->show();
    }
}


/// <summary>
/// Receive the data from the SSH Layer Manager
/// </summary>
/// <param name="field">        Stratum ID field                </param name>
/// <param name="filename">     Input path of the SSH layer     </param name>
void MainWindow::ReceiveDataB(QString field, QString filename)
{
    s->stratumID = field;
    s->readStratifiedLayerPath = filename;

    int k = 999;
    if(s->code_1 == 0){
        if(filename.isEmpty() == FALSE){
            this->readStratifiedLayerPath = filename;
            k = s->d->ReadStratifiedLayer(this->readStratifiedLayerPath, s->code_1, s->stratumID);
            if(k == 1){
                this->viewDlg = new ViewDialog(this);
                this->viewDlg->ui->openGLWidget->code = 3;
                this->viewDlg->ui->openGLWidget->stfV = new StratifiedVector();
                this->viewDlg->ui->openGLWidget->stfV = s->d->stfV;
                ui->view_3->setEnabled(TRUE);
                ui->del_3->setEnabled(TRUE);
                this->viewDlg->show();
            }
            else if(k == 0)
                QMessageBox::warning(this,tr("Warning"),tr("When the data type is VECTOR, geometry of the stratified layer should be POLYGON (or MultiPolygon)."));
            else if(k == 999)
                QMessageBox::warning(this,tr("Warning"),tr("Failed to open the SSH layer."));
        }
    }
    else if(s->code_1 == 1){
        if(filename.isEmpty() == FALSE){
            this->readStratifiedLayerPath = filename;
            k = this->s->d->ReadStratifiedLayer(this->readStratifiedLayerPath, s->code_1, s->stratumID);
            if(k == 1){
//                this->viewDlg = new ViewDialog(this);
//                this->viewDlg->ui->openGLWidget->code = 3;
//                this->viewDlg->ui->openGLWidget->stfG = new StratifiedRaster();
//                this->viewDlg->ui->openGLWidget->stfG = s->d->stfG;
//                ui->view_3->setEnabled(TRUE);
//                this->viewDlg->show();
            }
            else if(k == 2)
                QMessageBox::warning(this,tr("Warning"),tr("The SSH layer should have SINGLE band (grey)."));
            else if(k == 999)
                QMessageBox::warning(this,tr("Warning"),tr("Failed to open the SSH layer."));
        }
    }
    else
        QMessageBox::warning(this,tr("Warning"),tr("Please select the data type."));
}


/// <summary>
/// Input the reporting layer
/// </summary>
void MainWindow::on_rptLyr_clicked()
{
    int k = 999;
    QString filename;
    if(s->code_1 == 0 || s->code_1 == 1){
        filename = QFileDialog::getOpenFileName(this,tr("Reporting layer"),"",tr("Vector data (*.shp)"));
        if(filename.isEmpty() == FALSE){
            s->readReportingLayerPath = filename;
            k = s->d->ReadReportingLayer(filename);
            if(k == 1){
                this->viewDlg = new ViewDialog(this);
                this->viewDlg->ui->openGLWidget->code = 4;
                this->viewDlg->ui->openGLWidget->rptLyr = new ReportingLayer();
                this->viewDlg->ui->openGLWidget->rptLyr = s->d->rptLyr;
                ui->view_4->setEnabled(TRUE);
                ui->del_4->setEnabled(TRUE);
                this->viewDlg->show();
            }
            else if(k == 0)
                QMessageBox::warning(this,tr("Warning"),tr("Geometry of the reporting layer should be POLYGON (or MultiPolygon)."));
            else if(k == 999)
                QMessageBox::warning(this,tr("Warning"),tr("Failed to open the reporting layer."));
        }
    }else if(s->code_1 == 999)
        QMessageBox::warning(this,tr("Warning"),tr("Please select the data type."));
}


/// <summary>
/// Run the Sandwich model
/// </summary>
void MainWindow::on_run_clicked()
{
    QString dic, txtFile, shpFile;
    if(s->code_4 == 0){
        if(s->code_2 == 999)
            QMessageBox::warning(this,tr("Warning"),tr("Please input at lease one population layer or a sampling layer."));
        else if(s->readStratifiedLayerPath.isEmpty() == TRUE)
            QMessageBox::warning(this,tr("Warning"),tr("Please input the SSH layer."));
        else if(s->readReportingLayerPath.isEmpty() == TRUE)
            QMessageBox::warning(this,tr("Warning"),tr("Please input the reporting layer."));
        else{
            dic = QFileDialog::getExistingDirectory(this,tr("Sandwich output"));
            txtFile = dic + "/Sandwich Summary.txt";
            shpFile = dic + "/Sandwich Mapping.shp";
            if(dic.isEmpty() == FALSE){
                s->writeTXTPath = txtFile;
                s->writeReportingLayerPath = shpFile;
                tRM = new ThreadRunModel();
                tRM->s = s;
                connect(tRM, SIGNAL(RMStart()), this, SLOT(RMStart()));
                connect(tRM, SIGNAL(RMEnd()), this, SLOT(RMEnd()));
                tRM->start();
                this->viewDlg->ui->openGLWidget->code = 5;
                this->viewDlg->ui->openGLWidget->rptLyr = new ReportingLayer();
                this->viewDlg->ui->openGLWidget->rptLyr = s->d->rptLyr;

                //legend 1
                QLabel* legend1_img = new QLabel(this->viewDlg);
                legend1_img->resize(30, 15);
                legend1_img->move(600, 19);
                legend1_img->setAlignment(Qt::AlignLeft);
                legend1_img->setScaledContents(true);
                legend1_img->setPixmap(QPixmap(":/res/legend1.png"));

                QLabel* legend1_text = new QLabel(this->viewDlg);
                legend1_text->move(600, 19);
                legend1_text->setAlignment(Qt::AlignLeft);
                legend1_text->setScaledContents(true);
                legend1_text->setText("This is text");

                this->viewDlg->show();

                //this->viewDlg2->ui->openGLWidget->code = 6;
                //this->viewDlg2->ui->openGLWidget->rptLyr = new ReportingLayer();
                //this->viewDlg2->ui->openGLWidget->rptLyr = s->d->rptLyr;
                //this->viewDlg2->show();
            }
        }
    }else{
        if(s->code_2 == 999)
            QMessageBox::warning(this,tr("Warning"),tr("Please set the sampling layer."));
        else if(s->readStratifiedLayerPath.isEmpty() == TRUE)
            QMessageBox::warning(this,tr("Warning"),tr("Please input the SSH layer."));
        else if(s->readReportingLayerPath.isEmpty() == TRUE)
            QMessageBox::warning(this,tr("Warning"),tr("Please input the reporting layer."));
        else{
            dic = QFileDialog::getExistingDirectory(this,tr("Sandwich output"));
            txtFile = dic + "/Sandwich Summary.txt";
            shpFile = dic + "/Sandwich Mapping.shp";
            if(dic.isEmpty() == FALSE){
                s->writeTXTPath = txtFile;
                s->writeReportingLayerPath = shpFile;
                tRM = new ThreadRunModel();
                tRM->s = s;
                connect(tRM, SIGNAL(RMStart()), this, SLOT(RMStart()));
                connect(tRM, SIGNAL(RMEnd()), this, SLOT(RMEnd()));
                tRM->start();
            }
        }
    }
}


/// <summary>
/// Run the Sandwich model, and open the progress dialog
/// </summary>
void MainWindow::RMStart()
{
    progress = new QProgressDialog(this);
    progress->setWindowTitle(tr("Status"));
    progress->setLabelText(QStringLiteral("Sandwich model processing..."));
    progress->setCancelButton(0);
    progress->setModal(true);
    progress->setRange(0,100);
    progress->setMinimumDuration(0);

    timer = new QTimer();
    currentValue = 0;
    progress->setValue(currentValue);
    connect(timer, SIGNAL(timeout()), this, SLOT(UpdateProgressDialog()));
    timer->start(100);
}


/// <summary>
/// Update the progress dialog
/// </summary>
void MainWindow::UpdateProgressDialog()
{
    currentValue++;
    if(currentValue == 100 )
        currentValue = 0;
    progress->setValue(currentValue);
    QCoreApplication::processEvents();
    if(progress->wasCanceled())
        return;
}


/// <summary>
/// Close the progress dialog
/// </summary>
void MainWindow::RMEnd()
{
    timer->stop();
    if(currentValue != 100)
        currentValue = 100;
    progress->setValue(currentValue);//进度达到最大值
    progress->close();
    QMessageBox::information(this, tr("Status"), tr("Successfully conducted the model!"), QMessageBox::Ok);
}


/// <summary>
/// View the population layer
/// </summary>
void MainWindow::on_view_1_clicked()
{
    if(s->code_1 == 0){
        this->viewDlg->ui->openGLWidget->code = 1;
        this->viewDlg->ui->openGLWidget->objV = new ObjectVector();
        this->viewDlg->ui->openGLWidget->objV = s->d->objV;
        this->viewDlg->show();
    }
}


/// <summary>
/// View the sampling layer
/// </summary>
void MainWindow::on_view_2_clicked()
{
    if(s->code_1 == 0){
        this->viewDlg->ui->openGLWidget->code = 2;
        this->viewDlg->ui->openGLWidget->splV = new SamplingVector();
        this->viewDlg->ui->openGLWidget->splV = s->d->splV;
        this->viewDlg->show();
    }
}


/// <summary>
/// View the SSH layer
/// </summary>
void MainWindow::on_view_3_clicked()
{
    if(s->code_1 == 0){
        this->viewDlg->ui->openGLWidget->code = 3;
        this->viewDlg->ui->openGLWidget->stfV = new StratifiedVector();
        this->viewDlg->ui->openGLWidget->stfV = s->d->stfV;
        this->viewDlg->show();
    }
}


/// <summary>
/// View the reporting layer
/// </summary>
void MainWindow::on_view_4_clicked()
{
    if(s->code_1 == 0){
        this->viewDlg->ui->openGLWidget->code = 4;
        this->viewDlg->ui->openGLWidget->rptLyr = new ReportingLayer();
        this->viewDlg->ui->openGLWidget->rptLyr = s->d->rptLyr;
        this->viewDlg->show();
    }
}


/// <summary>
/// Delete the population layer
/// </summary>
void MainWindow::on_del_1_clicked()
{
    s->readObjectLayerPath.clear();
    if (s->d->objV != 0x00){
        delete s->d->objV;
        s->d->objV = 0x00;
    }
    s->code_4 = 0;
    ui->view_1->setEnabled(FALSE);
    ui->del_1->setEnabled(FALSE);
}


/// <summary>
/// Delete the sampling layer
/// </summary>
void MainWindow::on_del_2_clicked()
{
    s->readSamplingLayerPath.clear();
    if (s->d->splV != 0x00){
        delete s->d->splV;
        s->d->splV = 0x00;
    }
    s->code_2 = 999;
    s->code_3 = 999;

    ui->view_2->setEnabled(FALSE);
    ui->del_2->setEnabled(FALSE);
}


/// <summary>
/// Delete the SSH layer
/// </summary>
void MainWindow::on_del_3_clicked()
{
    s->readStratifiedLayerPath.clear();
    if (s->d->stfV != 0x00){
        delete s->d->stfV;
        s->d->stfV = 0x00;
    }

    ui->view_3->setEnabled(FALSE);
    ui->del_3->setEnabled(FALSE);
}


/// <summary>
/// Delete the reporting layer
/// </summary>
void MainWindow::on_del_4_clicked()
{
    s->readReportingLayerPath.clear();
    if (s->d->rptLyr != 0x00){
        delete s->d->rptLyr;
        s->d->rptLyr = 0x00;
    }

    ui->view_4->setEnabled(FALSE);
    ui->del_4->setEnabled(FALSE);
}

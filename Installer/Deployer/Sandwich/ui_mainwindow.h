/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QComboBox *objType;
    QLabel *label;
    QPushButton *run;
    QGroupBox *groupBox;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *objLyr;
    QPushButton *rptLyr;
    QPushButton *view_3;
    QPushButton *view_4;
    QPushButton *view_1;
    QPushButton *view_2;
    QPushButton *splLyr;
    QPushButton *stfLyr;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *del_1;
    QPushButton *del_2;
    QPushButton *del_3;
    QPushButton *del_4;
    QGraphicsView *graphicsView;
    QLabel *label_6;
    QLabel *label_7;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(521, 846);
        QFont font;
        font.setFamily(QStringLiteral("Verdana"));
        font.setPointSize(10);
        font.setBold(false);
        font.setWeight(50);
        MainWindow->setFont(font);
        MainWindow->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(false);
        font1.setWeight(50);
        centralWidget->setFont(font1);
        objType = new QComboBox(centralWidget);
        objType->setObjectName(QStringLiteral("objType"));
        objType->setGeometry(QRect(270, 10, 180, 35));
        objType->setFont(font1);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 10, 171, 35));
        label->setFont(font1);
        run = new QPushButton(centralWidget);
        run->setObjectName(QStringLiteral("run"));
        run->setGeometry(QRect(170, 630, 211, 40));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(19, 60, 481, 551));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 300, 150, 30));
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 40, 150, 30));
        label_3->setAlignment(Qt::AlignCenter);
        objLyr = new QPushButton(groupBox);
        objLyr->setObjectName(QStringLiteral("objLyr"));
        objLyr->setGeometry(QRect(40, 70, 150, 150));
        objLyr->setAutoFillBackground(false);
        objLyr->setStyleSheet(QLatin1String("QPushButton#objLyr{border-image: url(:/res/ObjectLayer-01.png);}\n"
"QPushButton#objLyr:hover{border-image:url(:/res/ObjectLayer-02.png)}"));
        objLyr->setIconSize(QSize(150, 150));
        rptLyr = new QPushButton(groupBox);
        rptLyr->setObjectName(QStringLiteral("rptLyr"));
        rptLyr->setGeometry(QRect(290, 330, 150, 150));
        rptLyr->setStyleSheet(QLatin1String("QPushButton#rptLyr{border-image: url(:/res/ReportingLayer-01.png);}\n"
"QPushButton#rptLyr:hover{border-image: url(:/res/ReportingLayer-02.png)}"));
        view_3 = new QPushButton(groupBox);
        view_3->setObjectName(QStringLiteral("view_3"));
        view_3->setGeometry(QRect(40, 490, 71, 40));
        view_4 = new QPushButton(groupBox);
        view_4->setObjectName(QStringLiteral("view_4"));
        view_4->setGeometry(QRect(290, 490, 71, 40));
        view_1 = new QPushButton(groupBox);
        view_1->setObjectName(QStringLiteral("view_1"));
        view_1->setGeometry(QRect(40, 230, 71, 40));
        view_2 = new QPushButton(groupBox);
        view_2->setObjectName(QStringLiteral("view_2"));
        view_2->setGeometry(QRect(290, 230, 71, 40));
        splLyr = new QPushButton(groupBox);
        splLyr->setObjectName(QStringLiteral("splLyr"));
        splLyr->setGeometry(QRect(290, 70, 150, 150));
        splLyr->setStyleSheet(QLatin1String("QPushButton#splLyr{border-image: url(:/res/SamplingLayer-01.png);}\n"
"QPushButton#splLyr:hover{border-image:url(:/res/SamplingLayer-02.png)}"));
        stfLyr = new QPushButton(groupBox);
        stfLyr->setObjectName(QStringLiteral("stfLyr"));
        stfLyr->setGeometry(QRect(40, 330, 150, 150));
        stfLyr->setStyleSheet(QLatin1String("QPushButton#stfLyr{border-image: url(:/res/StratifiedLayer-01.png);}\n"
"QPushButton#stfLyr:hover{border-image: url(:/res/StratifiedLayer-02.png)}"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(290, 40, 150, 30));
        label_4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(290, 300, 150, 30));
        label_5->setAlignment(Qt::AlignCenter);
        del_1 = new QPushButton(groupBox);
        del_1->setObjectName(QStringLiteral("del_1"));
        del_1->setGeometry(QRect(120, 230, 71, 40));
        del_2 = new QPushButton(groupBox);
        del_2->setObjectName(QStringLiteral("del_2"));
        del_2->setGeometry(QRect(370, 230, 71, 40));
        del_3 = new QPushButton(groupBox);
        del_3->setObjectName(QStringLiteral("del_3"));
        del_3->setGeometry(QRect(120, 490, 71, 40));
        del_4 = new QPushButton(groupBox);
        del_4->setObjectName(QStringLiteral("del_4"));
        del_4->setGeometry(QRect(370, 490, 71, 40));
        label_2->raise();
        label_3->raise();
        rptLyr->raise();
        view_3->raise();
        view_4->raise();
        view_1->raise();
        view_2->raise();
        splLyr->raise();
        stfLyr->raise();
        label_4->raise();
        label_5->raise();
        objLyr->raise();
        del_1->raise();
        del_2->raise();
        del_3->raise();
        del_4->raise();
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(10, 686, 50, 50));
        graphicsView->setStyleSheet(QStringLiteral("border-image: url(:/res/sandwich.png);"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(70, 686, 441, 110));
        QFont font2;
        font2.setPointSize(7);
        label_6->setFont(font2);
        label_6->setWordWrap(true);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(70, 793, 441, 51));
        label_7->setFont(font2);
        label_7->setWordWrap(true);
        MainWindow->setCentralWidget(centralWidget);
        groupBox->raise();
        objType->raise();
        label->raise();
        run->raise();
        graphicsView->raise();
        label_6->raise();
        label_7->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Sandwich", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Data type", Q_NULLPTR));
        run->setText(QApplication::translate("MainWindow", "Run and Export", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Input layers", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "SSH Layer", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Population Layer", Q_NULLPTR));
        objLyr->setText(QString());
        rptLyr->setText(QString());
        view_3->setText(QApplication::translate("MainWindow", "View", Q_NULLPTR));
        view_4->setText(QApplication::translate("MainWindow", "View", Q_NULLPTR));
        view_1->setText(QApplication::translate("MainWindow", "View", Q_NULLPTR));
        view_2->setText(QApplication::translate("MainWindow", "View", Q_NULLPTR));
        splLyr->setText(QString());
        stfLyr->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "Sampling Layer", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Reporting Layer", Q_NULLPTR));
        del_1->setText(QApplication::translate("MainWindow", "Delete", Q_NULLPTR));
        del_2->setText(QApplication::translate("MainWindow", "Delete", Q_NULLPTR));
        del_3->setText(QApplication::translate("MainWindow", "Delete", Q_NULLPTR));
        del_4->setText(QApplication::translate("MainWindow", "Delete", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "Please add this reference in your study when applying SSI: Wang, J.-F., Haining, R., Liu, T.-J., Li, L.-F., & Jiang, C.-S. (2013). Sandwich Estimation for Multi-Unit Reporting on a Stratified Heterogeneous Surface. Environment and Planning A: Economy and Space, 45(10), 2515\342\200\2232534. https://doi.org/10.1068/a44710", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Developers: Yue Lin, liny@lreis.ac.cn; Chengdong Xu, xucd@lreis.ac.cn; Jinfeng Wang, wangjf@lreis.ac.cn", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

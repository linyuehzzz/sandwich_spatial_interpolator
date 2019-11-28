/********************************************************************************
** Form generated from reading UI file 'samplinglayermanager.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAMPLINGLAYERMANAGER_H
#define UI_SAMPLINGLAYERMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SamplingLayerManager
{
public:
    QGroupBox *groupBox;
    QPushButton *create;
    QGraphicsView *graphicsView_2;
    QPushButton *load;
    QGraphicsView *graphicsView;
    QComboBox *splFields;
    QLabel *label;
    QPushButton *OK;
    QPushButton *Cancel;

    void setupUi(QDialog *SamplingLayerManager)
    {
        if (SamplingLayerManager->objectName().isEmpty())
            SamplingLayerManager->setObjectName(QStringLiteral("SamplingLayerManager"));
        SamplingLayerManager->resize(417, 337);
        QFont font;
        font.setFamily(QStringLiteral("Verdana"));
        SamplingLayerManager->setFont(font);
        SamplingLayerManager->setStyleSheet(QStringLiteral(""));
        groupBox = new QGroupBox(SamplingLayerManager);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 20, 381, 171));
        create = new QPushButton(groupBox);
        create->setObjectName(QStringLiteral("create"));
        create->setGeometry(QRect(40, 110, 120, 40));
        create->setFont(font);
        create->setStyleSheet(QStringLiteral(""));
        graphicsView_2 = new QGraphicsView(groupBox);
        graphicsView_2->setObjectName(QStringLiteral("graphicsView_2"));
        graphicsView_2->setGeometry(QRect(250, 40, 57, 50));
        graphicsView_2->setStyleSheet(QStringLiteral("border-image: url(:/res/Load-01.png);"));
        load = new QPushButton(groupBox);
        load->setObjectName(QStringLiteral("load"));
        load->setGeometry(QRect(220, 110, 120, 40));
        load->setFont(font);
        load->setStyleSheet(QStringLiteral(""));
        graphicsView = new QGraphicsView(groupBox);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(70, 30, 60, 60));
        graphicsView->setStyleSheet(QStringLiteral("border-image: url(:/res/Create-01.png)"));
        splFields = new QComboBox(SamplingLayerManager);
        splFields->setObjectName(QStringLiteral("splFields"));
        splFields->setGeometry(QRect(160, 210, 241, 35));
        label = new QLabel(SamplingLayerManager);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 210, 161, 35));
        OK = new QPushButton(SamplingLayerManager);
        OK->setObjectName(QStringLiteral("OK"));
        OK->setGeometry(QRect(90, 270, 80, 40));
        Cancel = new QPushButton(SamplingLayerManager);
        Cancel->setObjectName(QStringLiteral("Cancel"));
        Cancel->setGeometry(QRect(250, 270, 80, 40));

        retranslateUi(SamplingLayerManager);

        QMetaObject::connectSlotsByName(SamplingLayerManager);
    } // setupUi

    void retranslateUi(QDialog *SamplingLayerManager)
    {
        SamplingLayerManager->setWindowTitle(QApplication::translate("SamplingLayerManager", "Sampling Layer Manager", 0));
        groupBox->setTitle(QApplication::translate("SamplingLayerManager", "Input options", 0));
        create->setText(QApplication::translate("SamplingLayerManager", "Create", 0));
        load->setText(QApplication::translate("SamplingLayerManager", "Load", 0));
        label->setText(QApplication::translate("SamplingLayerManager", "Sampling field", 0));
        OK->setText(QApplication::translate("SamplingLayerManager", "OK", 0));
        Cancel->setText(QApplication::translate("SamplingLayerManager", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class SamplingLayerManager: public Ui_SamplingLayerManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAMPLINGLAYERMANAGER_H

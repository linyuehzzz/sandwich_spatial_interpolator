/********************************************************************************
** Form generated from reading UI file 'stratifiedlayermanager.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STRATIFIEDLAYERMANAGER_H
#define UI_STRATIFIEDLAYERMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SSHLayerManager
{
public:
    QPushButton *Load;
    QPushButton *Cancel;
    QGroupBox *groupBox;
    QComboBox *StratumID;
    QPushButton *strInput;
    QLabel *label;

    void setupUi(QDialog *SSHLayerManager)
    {
        if (SSHLayerManager->objectName().isEmpty())
            SSHLayerManager->setObjectName(QStringLiteral("SSHLayerManager"));
        SSHLayerManager->resize(490, 281);
        QFont font;
        font.setFamily(QStringLiteral("Verdana"));
        SSHLayerManager->setFont(font);
        Load = new QPushButton(SSHLayerManager);
        Load->setObjectName(QStringLiteral("Load"));
        Load->setGeometry(QRect(120, 220, 80, 40));
        Cancel = new QPushButton(SSHLayerManager);
        Cancel->setObjectName(QStringLiteral("Cancel"));
        Cancel->setGeometry(QRect(300, 220, 80, 40));
        groupBox = new QGroupBox(SSHLayerManager);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 20, 471, 171));
        StratumID = new QComboBox(groupBox);
        StratumID->setObjectName(QStringLiteral("StratumID"));
        StratumID->setGeometry(QRect(180, 110, 281, 35));
        strInput = new QPushButton(groupBox);
        strInput->setObjectName(QStringLiteral("strInput"));
        strInput->setGeometry(QRect(180, 40, 121, 40));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 110, 141, 35));

        retranslateUi(SSHLayerManager);

        QMetaObject::connectSlotsByName(SSHLayerManager);
    } // setupUi

    void retranslateUi(QDialog *SSHLayerManager)
    {
        SSHLayerManager->setWindowTitle(QApplication::translate("SSHLayerManager", "Stratified Layer Manager", 0));
        Load->setText(QApplication::translate("SSHLayerManager", "Load", 0));
        Cancel->setText(QApplication::translate("SSHLayerManager", "Cancel", 0));
        groupBox->setTitle(QApplication::translate("SSHLayerManager", "Stratified layer settings", 0));
        strInput->setText(QApplication::translate("SSHLayerManager", "Input", 0));
        label->setText(QApplication::translate("SSHLayerManager", "Stratum ID", 0));
    } // retranslateUi

};

namespace Ui {
    class SSHLayerManager: public Ui_SSHLayerManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STRATIFIEDLAYERMANAGER_H

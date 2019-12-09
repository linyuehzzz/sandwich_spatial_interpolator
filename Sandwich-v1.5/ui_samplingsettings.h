/********************************************************************************
** Form generated from reading UI file 'samplingsettings.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAMPLINGSETTINGS_H
#define UI_SAMPLINGSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SamplingSettings
{
public:
    QPushButton *OK;
    QPushButton *cancel;
    QGroupBox *groupBox;
    QComboBox *splMethod;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *splSize;

    void setupUi(QDialog *SamplingSettings)
    {
        if (SamplingSettings->objectName().isEmpty())
            SamplingSettings->setObjectName(QStringLiteral("SamplingSettings"));
        SamplingSettings->resize(800, 319);
        QFont font;
        font.setFamily(QStringLiteral("Verdana"));
        SamplingSettings->setFont(font);
        OK = new QPushButton(SamplingSettings);
        OK->setObjectName(QStringLiteral("OK"));
        OK->setGeometry(QRect(300, 240, 80, 40));
        cancel = new QPushButton(SamplingSettings);
        cancel->setObjectName(QStringLiteral("cancel"));
        cancel->setGeometry(QRect(460, 240, 80, 40));
        groupBox = new QGroupBox(SamplingSettings);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(30, 50, 741, 161));
        splMethod = new QComboBox(groupBox);
        splMethod->setObjectName(QStringLiteral("splMethod"));
        splMethod->setGeometry(QRect(200, 40, 511, 35));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 40, 181, 35));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 100, 181, 35));
        splSize = new QLineEdit(groupBox);
        splSize->setObjectName(QStringLiteral("splSize"));
        splSize->setGeometry(QRect(200, 100, 511, 35));

        retranslateUi(SamplingSettings);

        QMetaObject::connectSlotsByName(SamplingSettings);
    } // setupUi

    void retranslateUi(QDialog *SamplingSettings)
    {
        SamplingSettings->setWindowTitle(QApplication::translate("SamplingSettings", "Sampling Settings", 0));
        OK->setText(QApplication::translate("SamplingSettings", "OK", 0));
        cancel->setText(QApplication::translate("SamplingSettings", "Cancel", 0));
        groupBox->setTitle(QApplication::translate("SamplingSettings", "Sampling settings", 0));
        label->setText(QApplication::translate("SamplingSettings", "Sampling method", 0));
        label_2->setText(QApplication::translate("SamplingSettings", "Sample size", 0));
    } // retranslateUi

};

namespace Ui {
    class SamplingSettings: public Ui_SamplingSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAMPLINGSETTINGS_H

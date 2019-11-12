/********************************************************************************
** Form generated from reading UI file 'viewdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWDIALOG_H
#define UI_VIEWDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <myopenglwidget.h>

QT_BEGIN_NAMESPACE

class Ui_ViewDialog
{
public:
    MyOpenGLWidget *openGLWidget;

    void setupUi(QDialog *ViewDialog)
    {
        if (ViewDialog->objectName().isEmpty())
            ViewDialog->setObjectName(QStringLiteral("ViewDialog"));
        ViewDialog->resize(610, 503);
        openGLWidget = new MyOpenGLWidget(ViewDialog);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(19, 19, 571, 471));

        retranslateUi(ViewDialog);

        QMetaObject::connectSlotsByName(ViewDialog);
    } // setupUi

    void retranslateUi(QDialog *ViewDialog)
    {
        ViewDialog->setWindowTitle(QApplication::translate("ViewDialog", "Layer View", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ViewDialog: public Ui_ViewDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWDIALOG_H

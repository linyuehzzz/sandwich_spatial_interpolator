#-------------------------------------------------
#
# Project created by QtCreator 2019-01-30T10:01:10
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sandwich
TEMPLATE = app


SOURCES += main.cpp\
    DataOutput.cpp \
    DataSource.cpp \
    Log.cpp \
    MainWindow.cpp \
    MyOpenGLWidget.cpp \
    ObjectRaster.cpp \
    ObjectLayer.cpp \
    ObjectVector.cpp \
    Point.cpp \
    ReportingLayer.cpp \
    SamplingRaster.cpp \
    SamplingLayerManager.cpp \
    SamplingLayer.cpp \
    SamplingVector.cpp \
    SamplingSettings.cpp \
    Sandwich.cpp \
    StratifiedRaster.cpp \
    StratifiedLayer.cpp \
    StratifiedVector.cpp \
    ViewDialog.cpp \
    ThreadSampling.cpp \
    ThreadRunModel.cpp \
    SSHLayerManager.cpp

HEADERS  += \
    DataOutput.h \
    DataSource.h \
    Log.h \
    MainWindow.h \
    MyOpenGLWidget.h \
    ObjectRatser.h \
    ObjectLayer.h \
    ObjectVector.h \
    Point.h \
    ReportingLayer.h \
    SamplingRaster.h \
    SamplingLayer.h \
    SamplingLayerManager.h \
    SamplingSettings.h \
    SamplingVector.h \
    Sandwich.h \
    StratifiedLayer.h \
    StratifiedRaster.h \
    ViewDialog.h \
    StratifiedVector.h \
    ui_mainwindow.h \
    ThreadSampling.h \
    ThreadRunModel.h \
    SSHLayerManager.h

FORMS    += mainwindow.ui \
    samplinglayermanager.ui \
    samplingsettings.ui \
    viewdialog.ui \
    sshlayermanager.ui

RESOURCES += \
    src.qrc

RC_ICONS = "sandwich.ico"

unix|win32: LIBS += -L$$PWD/../gdal_2.1.1/lib/ -lgdal_i

INCLUDEPATH += $$PWD/../gdal_2.1.1/include
DEPENDPATH += $$PWD/../gdal_2.1.1/include

#include "Log.h"
#include <QString>
#include <QLoggingCategory>
#include <QIODevice>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QDateTime>
#include <QMutex>
#include <QRegExp>
#include <QApplication>

static QString logDirectory;
static QString logFileName;
static QMutex mutex;
static QFile file;
static QTextStream textStream;


/// <summary>
/// New MessageHandler
/// </summary>
void OutputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString text;
    switch(type)
    {
    case QtDebugMsg:
        text = QString("");
        break;
    case QtInfoMsg:
        text = QString("");
        break;
    case QtWarningMsg:
        text = QString("[Warning]");
        break;
    case QtCriticalMsg:
        text = QString("[Critical]");
        break;
    case QtFatalMsg:
        text = QString("[Fatal]");
    }
    text.append(QString(" [%1] ").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));
    text.append(QString(" [%1: Line: %2] ").arg(QString(context.file)).arg(context.line));
    text.append(QString(" [Function: %1] ").arg(QString(context.function)));

    mutex.lock();
    file.setFileName(logFileName);
    file.open(QIODevice::WriteOnly | QIODevice::Append |QIODevice::Text);
    textStream.setDevice(&file);
    textStream << text << endl << QString("%1").arg(msg) << endl;
    file.close();
    mutex.unlock();
}


/// <summary>
/// Create log
/// </summary>
void logInit()
{
    logDirectory  = QApplication::applicationDirPath();
    QDir dir(logDirectory);
    if(!dir.exists())
        dir.mkdir(logDirectory);
    logFileName = logDirectory + (QApplication::applicationName()+".log");

    /* Install the MessageHandler */
    qInstallMessageHandler(OutputMessage);
}

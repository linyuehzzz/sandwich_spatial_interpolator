/**************************************
Author: Yue Lin
Date: 2019/07/15
Update: 2019/07/17
Description: The thread for running the Sandwich model
***************************************/
#ifndef THREADRUNMODEL_H
#define THREADRUNMODEL_H

#include "Sandwich.h"
#include <QThread>
#include <QObject>

class ThreadRunModel: public QThread
{
    Q_OBJECT

public:
    ThreadRunModel(QObject *parent = 0);
    ~ThreadRunModel();

    // The Sandwich model
    Sandwich* s;

    /* Run the Sandwich model */
    void run() override;

signals:
    /*  The signal to start running the model */
    void RMStart();
    /*  The signal to stop running the model */
    void RMEnd();
};

#endif // THREADRUNMODEL_H

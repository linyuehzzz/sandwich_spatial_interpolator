/**************************************
Author: Yue Lin
Date: 2019/07/15
Update: 2019/07/17
Description: The thread for sampling
***************************************/
#ifndef THREADSAMPLING_H
#define THREADSAMPLING_H

#include "Sandwich.h"
#include <QThread>
#include <QObject>
#include <QString>

class ThreadSampling: public QThread
{
    Q_OBJECT

public:
    ThreadSampling(QObject *parent = 0);
    ~ThreadSampling();

    // The Sandwich model
    Sandwich* s;
    // Sample size
    int size;
    // Mark if the sampling layer exists or not (0 for no, 1 for yes)
    int code_2;
    // Mark for the sampling method (1 for Simple Random Sampling, 2 for Stratified Random Sampling (equal), 3 for Stratified Random Sampling (proportional), 4 for Stratified Random Sampling (optimum))
    int code_3;
    // Sampling field
    QString field;

    /* Sampling */
    void run() override;

signals:
    /*  The signal to start sampling */
    void SplStart();
    /*  The signal to stop sampling */
    void SplEnd(int t, int code_2);
};

#endif // THREADSAMPLING_H

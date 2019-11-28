#include "ThreadSampling.h"

ThreadSampling::ThreadSampling(QObject *parent)
    :QThread(parent)
{
    this->s = new Sandwich();
    this->size = 0;
    this->code_2 = 999;
    this->code_3 = 999;
}


ThreadSampling::~ThreadSampling()
{
    s = NULL;
}


void ThreadSampling::run()
{
    emit SplStart();
    int t = s->d->SamplingV(s->d->objV, s->d->objV->number, s->d->stfV->kunits, s->d->stfV->number, size, code_3, field);
    emit SplEnd(t, this->code_2);
}

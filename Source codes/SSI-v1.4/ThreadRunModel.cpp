#include "ThreadRunModel.h"

ThreadRunModel::ThreadRunModel(QObject *parent)
    :QThread(parent)
{
    this->s = new Sandwich();
}


ThreadRunModel::~ThreadRunModel()
{
    s = NULL;
}


void ThreadRunModel::run()
{
    emit RMStart();
    s->RunModel();
    s->WriteFile();
    emit RMEnd();
}

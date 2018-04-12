#include "client.h"
#include "workerthread.h"
#include <QDebug>

Client::Client(QObject *parent) :
    QObject(parent)
{
}

void Client::startWorkInAThread(){

    WorkerThread *myWorker = new WorkerThread(this);

    connect( myWorker, &WorkerThread::resultReady, this, &Client::handleResult);
    connect( myWorker, &WorkerThread::finished, myWorker, &QObject::deleteLater);

    myWorker->start();
}

void Client::handleResult(const QString &s){

    qDebug() << "This is the result from Worker: " + s;
}

#include "workerthread.h"
#include <QDebug>

WorkerThread::WorkerThread(QObject *parent) :
    QThread(parent)
{
}

void WorkerThread::run() {

    for(int i=0; i<5; i++){

        qDebug() << i << "\n";
        sleep(1);
    }

    emit resultReady("Ready!");
}

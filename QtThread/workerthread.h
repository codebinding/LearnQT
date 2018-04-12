#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>

class WorkerThread : public QThread
{
    Q_OBJECT
    void run();
public:
    explicit WorkerThread(QObject *parent = 0);

signals:
    void resultReady(const QString &);
public slots:

};

#endif // WORKERTHREAD_H

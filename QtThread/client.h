#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    void startWorkInAThread();

signals:

public slots:
    void handleResult(const QString &);
};

#endif // CLIENT_H

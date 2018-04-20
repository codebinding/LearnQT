#ifndef SLOT_H
#define SLOT_H

#include <QObject>

class Slot : public QObject
{
    Q_OBJECT

public:
    Slot();

public slots:
    void ProcessSignal();
};

#endif // SLOT_H

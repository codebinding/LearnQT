#include <QCoreApplication>
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client *myClient = new Client();
    myClient->startWorkInAThread();
    myClient->startWorkInAThread();

    return a.exec();
}

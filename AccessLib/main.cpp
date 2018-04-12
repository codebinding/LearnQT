#include <QCoreApplication>
#include <iostream>
#include "client.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Client client;

    cout << "Result: " << client.Add(11, 4) << endl;

    return a.exec();
}

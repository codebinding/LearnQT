#include <QCoreApplication>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    string inputString;
    ifstream inputFile;
    inputFile.open("Input");
    if(inputFile){

        while( !inputFile.eof() ){

            getline(inputFile, inputString);

            cout << inputString << endl;
        }
    }
    else{

        cout << "Failed to open file" << endl;
    }

    return a.exec();
}

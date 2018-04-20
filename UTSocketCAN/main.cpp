#include <QCoreApplication>
#include "canframe.h"
#include "socketcan.h"
#include "canexception.h"
#include "slot.h"
#include <iostream>
#include <list>

int main(int argc, char *argv[]){

    QCoreApplication a(argc, argv);

    SocketCAN *my_socket = new SocketCAN(8);
    CANFrame8 *my_frame = new CANFrame8();

    std::list<int> my_filter = {0x001, 0x002};

    Slot *my_slot = new Slot();
    QObject::connect(my_socket, SIGNAL(CatchIt()), my_slot, SLOT(ProcessSignal()));

    try{

        my_socket->Open("can0", my_filter);

        int my_id = 0x123;

        ulong my_data = 0x1122334455667700l;
        my_frame->SetFrame(my_id, my_data);

        my_frame->SetFrame(my_id, 2, 2, 0x0f);

//        uint8_t *data = new uint8_t(8);

//        data[0] = 0x00;
//        data[1] = 0x01;
//        data[2] = 0x02;
//        data[3] = 0x03;
//        data[4] = 0x04;
//        data[5] = 0x05;
//        data[6] = 0x06;
//        data[7] = 0x07;
//        my_frame->SetFrame(0x88, data);

        std::cout << my_frame->ToString() << std::endl;

        my_socket->WriteSocket(*my_frame);

        std::cout << "Waiting ..." << std::endl;
    }
    catch(CANException& e){

        std::cout << e.Message() << std::endl;
    }

    return a.exec();
}

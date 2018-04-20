#include "slot.h"

#include <iostream>

Slot::Slot()
{

}

void Slot::ProcessSignal(){

    std::cout << "Received signal!!" << std::endl;
}

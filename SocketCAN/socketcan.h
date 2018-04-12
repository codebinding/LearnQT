#ifndef SOCKETCAN_H
#define SOCKETCAN_H

#include <string>
#include "canframe.h"

class SocketCAN
{

public:
    SocketCAN(const int data_length);
    virtual ~SocketCAN();

    void Open(std::string interface_name);
    void WriteFrame(CANFrame8& frame);
    void ReadFrame(CANFrame8& frame);

    bool IsValid() const { return m_sock != -1; }

private:
    const int k_data_length;
    int m_sock;
};
#endif // SOCKETCAN_H

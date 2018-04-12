#include "socketcan.h"
#include "canexception.h"

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include "inttypes.h"

SocketCAN::SocketCAN(const int data_length)
    :k_data_length(data_length),
      m_sock(-1)
{
}

SocketCAN::~SocketCAN(){

    if( IsValid() ){

        ::close( m_sock );
    }
}

void SocketCAN::Open(std::string interface_name){

    struct ifreq my_ifr;
    struct sockaddr_can my_addr;

    m_sock = ::socket(PF_CAN, SOCK_RAW, CAN_RAW);

    if( !IsValid() ){

        throw CANException("error while opening socket");
    }

    ::strcpy(my_ifr.ifr_ifrn.ifrn_name, interface_name.c_str());
    ::ioctl(m_sock, SIOCGIFINDEX, &my_ifr);

    my_addr.can_family = AF_CAN;
    my_addr.can_ifindex = my_ifr.ifr_ifindex;

    if(::bind(m_sock, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1) {

        throw CANException("error while socket binding");
    }
}

void SocketCAN::WriteFrame(CANFrame8& frame){

    struct can_frame my_frame;

    my_frame.can_id = frame.GetId();
    my_frame.can_dlc = k_data_length;

    frame.GetData(my_frame.data);

    if(::write(m_sock, &my_frame, sizeof(struct can_frame)) == -1){

        throw CANException("error while writing CAN frame");
    }
}

void SocketCAN::ReadFrame(CANFrame8& frame){

    struct can_frame my_frame;

    if(::read(m_sock, &my_frame, sizeof(struct can_frame)) == -1){

        throw CANException("error while reading CAN frame");
    }

    frame.SetId(my_frame.can_id);
    frame.SetData(my_frame.data);
}

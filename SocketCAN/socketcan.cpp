#include "socketcan.h"
#include "canexception.h"

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#include "inttypes.h"

SocketCAN::SocketCAN(const int data_length)
    : k_data_length(data_length),
      m_sock(-1),
      m_filter_count(0)
{
}

SocketCAN::~SocketCAN(){

    m_sq_consumer_running = false;
    m_rq_producer_runing = false;

    pthread_join(m_thread_sq_consumer, NULL);
    pthread_join(m_thread_sq_consumer, NULL);

    pthread_mutex_destroy(&m_sq_lock);
    pthread_mutex_destroy(&m_rq_lock);

    pthread_cond_destroy(&m_signal_sq_producer);
    pthread_cond_destroy(&m_signal_sq_consumer);
    pthread_cond_destroy(&m_signal_rq_producer);
    pthread_cond_destroy(&m_signal_rq_consumer);

    delete m_send_queue;
    delete m_recv_queue;

    delete m_can_id_filter;

    if( IsValid() ){

        ::close( m_sock );
    }
}

void SocketCAN::Open(std::string interface_name, std::list<int> can_id_filter){

    struct ifreq my_ifr;
    struct sockaddr_can my_addr;

    m_sock = ::socket(PF_CAN, SOCK_RAW, CAN_RAW);

    if( !IsValid() ){

        throw CANException("error while opening socket");
    }

    m_filter_count = can_id_filter.size();
    m_can_id_filter = new struct can_filter[m_filter_count];
    for(int i = 0; i < m_filter_count; i++){

        m_can_id_filter[i].can_id = can_id_filter.front();
        m_can_id_filter[i].can_mask = CAN_SFF_ID_BITS;

        can_id_filter.pop_front();
    }
    ::setsockopt(m_sock, SOL_CAN_RAW, CAN_RAW_FILTER, m_can_id_filter, sizeof(struct can_filter)*m_filter_count);

    ::strcpy(my_ifr.ifr_ifrn.ifrn_name, interface_name.c_str());
    ::ioctl(m_sock, SIOCGIFINDEX, &my_ifr);

    my_addr.can_family = AF_CAN;
    my_addr.can_ifindex = my_ifr.ifr_ifindex;

    if(::bind(m_sock, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1) {

        throw CANException("error while socket binding");
    }

    m_send_queue = new std::queue<CANFrame8>();
    m_recv_queue = new std::queue<CANFrame8>();

    // Initialize lock and signals of the 'send queue'
    ::pthread_mutex_init(&m_sq_lock, NULL);
    ::pthread_cond_init(&m_signal_sq_producer, NULL);
    ::pthread_cond_init(&m_signal_sq_consumer, NULL);

    // Initialize lock and signals of the 'recv queue'
    ::pthread_mutex_init(&m_rq_lock, NULL);
    ::pthread_cond_init(&m_signal_rq_producer, NULL);
    ::pthread_cond_init(&m_signal_rq_consumer, NULL);

    // Create the threads
    m_sq_consumer_running = true;
    if(::pthread_create(&m_thread_sq_consumer, NULL, &ThreadConsumeSendQueue, this) != 0){

        throw CANException("error while creating thread 'ThreadConsumeSendQueue");
    }

    m_rq_producer_runing = true;
    if(::pthread_create(&m_thread_rq_producer, NULL, &ThreadProduceRecvQueue, this) != 0){

        throw CANException("error while creating thread 'ThreadProudceRecvQueue'");
    }
}

void SocketCAN::WriteSocket(CANFrame8& frame){

    struct can_frame my_frame;

    my_frame.can_id = frame.GetId();
    my_frame.can_dlc = k_data_length;

    frame.GetData(my_frame.data);

    if(::write(m_sock, &my_frame, sizeof(struct can_frame)) == -1){

        throw CANException("error while writing CAN frame");
    }
}

void SocketCAN::ReadSocket(CANFrame8& frame){

    struct can_frame my_frame;

    if(::read(m_sock, &my_frame, sizeof(struct can_frame)) == -1){

        throw CANException("error while reading CAN frame");
    }

    frame.SetId(my_frame.can_id);
    frame.SetData(my_frame.data);
}

void SocketCAN::ConsumeSendQueue(){

    while(m_sq_consumer_running){

        pthread_mutex_lock(&m_sq_lock);

        while(m_send_queue->empty()){

            pthread_cond_wait(&m_signal_sq_consumer, &m_sq_lock);
        }

        while(!m_send_queue->empty()){

            CANFrame8 my_frame = m_send_queue->front();
            m_send_queue->pop();

            WriteSocket(my_frame);
        }

        pthread_cond_signal(&m_signal_sq_producer);
        pthread_mutex_unlock(&m_sq_lock);
    }
}

void* SocketCAN::ThreadConsumeSendQueue(void* this_pointer){

    static_cast<SocketCAN*>(this_pointer)->ConsumeSendQueue();

    return NULL;
}

void SocketCAN::ProduceRecvQueue(){

    while(m_rq_producer_runing){

        CANFrame8 *my_frame = new CANFrame8();

        ReadSocket(*my_frame);

        pthread_mutex_lock(&m_rq_lock);

        m_recv_queue->push(*my_frame);

        //pthread_cond_signal(&m_signal_rq_consumer);

        uint8_t *my_data = new uint8_t[8];
        my_frame->GetData(my_data);
        if( my_data[0] == 0x80 ){

            std::cout << std::hex << (int)my_data[0] << " Signal/Slot test" << std::endl;
            emit CatchIt();
        }

        pthread_mutex_unlock(&m_rq_lock);
    }
}

void* SocketCAN::ThreadProduceRecvQueue(void *this_pointer){

    static_cast<SocketCAN*>(this_pointer)->ProduceRecvQueue();

    return NULL;
}

void SocketCAN::PrintRecvQueue(){

    pthread_mutex_lock(&m_rq_lock);

    while(!m_recv_queue->empty()){

        CANFrame8 my_frame = m_recv_queue->front();
        m_recv_queue->pop();

        std::cout << my_frame.ToString() << std::endl;
    }

    pthread_mutex_unlock(&m_rq_lock);
}



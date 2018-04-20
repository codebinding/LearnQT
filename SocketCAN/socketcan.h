#ifndef SOCKETCAN_H
#define SOCKETCAN_H

#include "canframe.h"

#include <linux/can.h>
#include <linux/can/raw.h>

#include <string>
#include <list>
#include <queue>
#include <pthread.h>

#include <QObject>

class SocketCAN : public QObject
{
    Q_OBJECT

public:
    SocketCAN(const int data_length);
    virtual ~SocketCAN();

    void Open(std::string interface_name, std::list<int> can_id_filter);
    void AddFilter(uint16_t id);
    void WriteSocket(CANFrame8& frame);
    void ReadSocket(CANFrame8& frame);

    void Write(CANFrame8& frame);

public slots:
    void PrintRecvQueue();

signals:
    void CatchIt();

private:
    const int k_data_length;
    int m_sock;
    struct can_filter *m_can_id_filter;
    int m_filter_count;

    pthread_mutex_t m_sq_lock;  // send queue lock
    pthread_cond_t m_signal_sq_producer, m_signal_sq_consumer;

    pthread_mutex_t m_rq_lock;
    pthread_cond_t m_signal_rq_producer, m_signal_rq_consumer;

    std::queue<CANFrame8> *m_send_queue;
    std::queue<CANFrame8> *m_recv_queue;

    bool IsValid() const { return m_sock != -1; }

    void ConsumeSendQueue();
    static void* ThreadConsumeSendQueue(void* this_pointer);
    pthread_t m_thread_sq_consumer;
    bool m_sq_consumer_running;

    void ProduceRecvQueue();
    static void* ThreadProduceRecvQueue(void* this_pointer);
    pthread_t m_thread_rq_producer;
    bool m_rq_producer_runing;
};
#endif // SOCKETCAN_H

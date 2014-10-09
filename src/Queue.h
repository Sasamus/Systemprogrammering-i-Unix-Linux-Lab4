//=============================================================
// Name        : Queue.h
// Author      : Albin Engström
// Created     : 2014-10-09
// Modified    : 2014-10-09
// Description : Definition of class Queue
// Purpose     : Act as an FIFO queue
//=============================================================
#ifndef QUEUE_H
#define QUEUE_H

class Queue
{
public:
    Queue(int p_Size);

    ~Queue(){}

    void Enqueue(int p_Value);
    //Pre: The queue isn't full
    //Post: p_Value is added to the queue

    int Dequeue();
    //Pre: The queue isn't empty
    //Post: A value is removed from the queue and returned



private:
    int m_Size = 10;
    int m_Head = 0;
    int m_Tail = 0;

};

#endif // QUEUE_H

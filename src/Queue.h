//=============================================================
// Name        : Queue.h
// Author      : Albin Engström
// Created     : 2014-10-09
// Modified    : 2014-10-10
// Description : Definition of class Queue
// Purpose     : Act as an FIFO queue
//=============================================================
#ifndef QUEUE_H
#define QUEUE_H

#include "Constants.h"

class Queue
{
public:
    Queue(){}

    ~Queue(){}

    void Enqueue(int p_Value);
    //Pre: The queue isn't full
    //Post: p_Value is added to the queue

    int Dequeue();
    //Pre: The queue isn't empty
    //Post: A value is removed from the queue and returned

    int Length();
    //Pre:
    //Post: Return the current number of elements in the queue

    bool Full();
    //Pre:
    //Post: Return true if the queue is full, else false

    bool Empty();
    //Pre:
    //Post: Return true if the queue is empty, else false



private:
    int m_Size = 0;
    int m_Array[Constants::G_BUFFERSIZE];
    int m_Head = 0;
    int m_Tail = 0;

};

#endif // QUEUE_H

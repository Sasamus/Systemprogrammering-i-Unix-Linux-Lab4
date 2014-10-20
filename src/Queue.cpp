//=============================================================
// Name        : Queue.cpp
// Author      : Albin Engström
// Created     : 2014-10-09
// Modified    : 2014-10-20
// Description : Implementation of class Queue
//=============================================================
#include "Queue.h"

void Queue::Enqueue(int value)
{
    //Check if m_tail is at the end of m_array
    if(m_head < Constants::G_BUFFERSIZE - 1)
    {
        //Increment m_tail
        m_tail++;
    }
    else
    {
        //Increment m_tail, which wraps to 0
        m_tail = 0;
    }


    //Add value to TheArray
    m_array[m_tail] = value;

    //Increment m_size
    m_size++;
}

int Queue::Dequeue()
{
    //Check if m_head is at the end of m_array
    if(m_head < Constants::G_BUFFERSIZE - 1)
    {
        //Increment m_head
        m_head++;
    }
    else
    {
        //Increment m_head, which wraps to 0
        m_head = 0;
    }

    //Decrement m_size
    m_size--;

    //Return the value
    if(m_head == 0)
    {
        return m_array[Constants::G_BUFFERSIZE -1];
    }
    else
    {
        return m_array[m_head - 1];
    }
}

int Queue::Length()
{
    return m_size;
}

bool Queue::Full()
{
    return m_size == Constants::G_BUFFERSIZE;
}

bool Queue::Empty()
{
    return m_size == 0;
}

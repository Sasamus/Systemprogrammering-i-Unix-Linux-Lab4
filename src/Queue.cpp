//=============================================================
// Name        : Queue.cpp
// Author      : Albin Engström
// Created     : 2014-10-09
// Modified    : 2014-10-11
// Description : Implementation of class Queue
//=============================================================
#include "Queue.h"

void Queue::Enqueue(int p_Value)
{
    //Add value to TheArray
    m_Array[m_Tail] = p_Value;

    //Increment m_Size
    m_Size++;

    //Increment m_Tail
    m_Tail++;

}

int Queue::Dequeue()
{
    //Increment m_Head
    m_Head++;

    //Decrement m_Size
    m_Size--;

    //Return the value
    return m_Array[m_Head - 1];
}

int Queue::Length()
{
    return m_Size;
}

bool Queue::Full()
{
    return m_Size == Constants::G_BUFFERSIZE;
}

bool Queue::Empty()
{
    return m_Size == 0;
}

//=============================================================
// Name        : Queue.cpp
// Author      : Albin Engström
// Created     : 2014-10-09
// Modified    : 2014-10-09
// Description : Implementation of class Queue
//=============================================================
#include "Queue.h"

Queue::Queue(int p_Size)
: m_Size(p_Size)
{
    int TheArray[m_Size];
}

void Queue::Enqueue(int p_Value)
{
    //Increment m_Tail
    m_Tail++;

    //Add value to TheArray
    TheArray[m_Tail] = p_Value;

    //Increment m_Size
    m_Size++;

}

int Queue::Dequeue()
{
    //Decrement m_Head
    m_Head--;

    //Decrement m_Size
    m_Size--;

    //Return the value
    return TheArray[m_Head + 1];
}

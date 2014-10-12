//=============================================================
// Name        : ProcessManager.h
// Author      : Albin Engström
// Created     : 2014-10-08
// Modified    : 2014-10-12
// Description : Definition of class ProcessManager
// Purpose     : Manages the programs processes
//=============================================================
#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include "Queue.h"
#include "SharedMem.h"
#include "Constants.h"

#include <new>
#include <iostream>
#include <semaphore.h>
#include <unistd.h>

class ProcessManager
{
public:
    ProcessManager(){}
    ~ProcessManager(){}

    int Run();
    //Pre:
    //Post: Create and manage the processes

private:
    //A pointer to a Queue object
    Queue *m_queue;

    //Semaphore for space available in buffer
    sem_t m_space_available;

    //Semaphore for items available in buffer
    sem_t m_items_available;

    //Holds the process pid
    pid_t m_pid;
};

#endif //PROCESSMANAGER_H

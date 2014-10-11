//=============================================================
// Name        : ProcessManager.h
// Author      : Albin Engström
// Created     : 2014-10-08
// Modified    : 2014-10-11
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

class ProcessManager
{
public:
    ProcessManager(){}
    ~ProcessManager(){}

    void Run();
    //Pre:
    //Post: Create and manage the processes

private:
    Queue *p_Queue;
    sem_t SpaceAvailable;
    sem_t ItemsAvailable;

};

#endif //PROCESSMANAGER_H

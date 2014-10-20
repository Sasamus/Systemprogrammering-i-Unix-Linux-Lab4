//=============================================================
// Name        : ProcessManager.h
// Author      : Albin Engström
// Created     : 2014-10-08
// Modified    : 2014-10-20
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
#include <cstdlib>
#include <ctime>

class ProcessManager
{
public:
    ProcessManager(){}
    ~ProcessManager();

    int Run(int nr_numbers);
    //Pre:
    //Post: Create and manage the processes

    int CreateSharedMem();
    //Pre:
    //Post: Create a SharedMem object and the things in it

    void SetParentToSleep();
    //Pre:
    //Post: Sets m_parent_sleep to true

    void SetChildToSleep();
    //Pre:
    //Post: Sets ld_sleep to true

    int Sleep();
    //Pre:
    //Post: Sleeps for a bit

private:
    //Variables to keep track of if parent/child should sleep
    bool m_parent_sleep = false;
    bool m_child_sleep = false;

    //A pointer to a Queue object
    Queue *m_queue;

    //Semaphore for space available in buffer
    sem_t *m_space_available;

    //Semaphore for items available in buffer
    sem_t *m_items_available;

    //Semaphore to keep track of if buffer diting is allowed
    sem_t *m_editing_allowed;

    //Holds the process pid
    pid_t m_pid;

    //A pointer to a SharedMem object
    SharedMem *m_shared_mem;
};

#endif //PROCESSMANAGER_H

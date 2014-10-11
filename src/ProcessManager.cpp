//=============================================================
// Name        : ProcessManager.cpp
// Author      : Albin Engström
// Created     : 2014-10-08
// Modified    : 2014-10-11
// Description : Implementation of class Processmanager
//=============================================================
#include "ProcessManager.h"

void ProcessManager::Run()
{
    //Create a SharedMem object
    SharedMem o_SharedMem(IPC_PRIVATE, 52);

    //Attache the shared memmory to the process
    o_SharedMem.attach();

    //Create a buffer and add it to o_SharedMem
    p_Queue = new ((Queue*) o_SharedMem.getAddr()) Queue();

    //Initialize the sempahores
    if(sem_init(&SpaceAvailable, 1, Constants::G_BUFFERSIZE) == -1)
    {
        perror("");
        return;
    }
    if(sem_init(&ItemsAvailable, 1, 0) == -1)
    {
        perror("");
        return;
    }

    //Destroys the semaphores
    if(sem_destroy(&SpaceAvailable) == -1)
    {
        perror("");
        return;
    }
    if(sem_destroy(&ItemsAvailable) == -1)
    {
        perror("");
        return;
    }

    //Detache the shared memmory from the process
    o_SharedMem.detach();

    //Removes the shared memmory from program control
    o_SharedMem.remove();
}

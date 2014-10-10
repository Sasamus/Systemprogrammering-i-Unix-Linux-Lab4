//=============================================================
// Name        : ProcessManager.cpp
// Author      : Albin Engström
// Created     : 2014-10-08
// Modified    : 2014-10-10
// Description : Implementation of class Processmanager
//=============================================================
#include "ProcessManager.h"
#include "Queue.h"
#include "SharedMem.h"

#include <new>
#include <iostream>

void ProcessManager::Run()
{
    //Create a SharedMem object
    SharedMem o_SharedMem(IPC_PRIVATE, 52);

    //Attache the shared memmory to the process
    o_SharedMem.attach();

    //Create a buffer and add it to o_SharedMem
    Queue *p_Queue = new ((Queue*) o_SharedMem.getAddr()) Queue();

    //Detache the shared memmory from the process
    o_SharedMem.detach();

    //Removes the shared memmory from program control
    o_SharedMem.remove();
}

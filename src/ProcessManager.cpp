//=============================================================
// Name        : ProcessManager.cpp
// Author      : Albin Engström
// Created     : 2014-10-08
// Modified    : 2014-10-09
// Description : Implementation of class Processmanager
//=============================================================
#include "ProcessManager.h"
#include "SharedMem.h"

void ProcessManager::Run()
{
    //Create a SharedMem object
    SharedMem o_SharedMem(IPC_PRIVATE, 1);

}

//=============================================================
// Name        : ProcessManager.cpp
// Author      : Albin Engström
// Created     : 2014-10-08
// Modified    : 2014-10-12
// Description : Implementation of class Processmanager
//=============================================================
#include "ProcessManager.h"

int ProcessManager::Run()
{
    //Create a SharedMem object
    SharedMem shared_mem(IPC_PRIVATE, 52);

    //Attache the shared memmory to the process
    if(shared_mem.attach() == -1)
    {
        std::cout << "Failed to attach shared memmory" << std::endl;
        return -1;
    }

    //Create a buffer and add it to shared_mem
    m_queue = new ((Queue*) shared_mem.getAddr()) Queue();

    //Initialize the sempahores
    if(sem_init(&m_space_available, 1, Constants::G_BUFFERSIZE) == -1)
    {
        perror(NULL);
        return -1;
    }
    if(sem_init(&m_items_available, 1, 0) == -1)
    {
        perror(NULL);
        return -1;
    }

    //Fork the process and capture the pid
    m_pid = fork();

    //Check if parent or child
    if(m_pid != 0)
    //Parent
    {
        //sem_wait(&m_space_available);
        m_queue->Enqueue(1);
        //sem_post(&m_items_available);
    }
    else
    //Child
    {
        //sem_wait(&m_items_available);
        std::cout << m_queue->Dequeue() << std::endl;
        //sem_post(&m_space_available);
    }

    if(m_pid != 0)
    {
        //Destroys the semaphores
        if(sem_destroy(&m_space_available) == -1)
        {
            perror(NULL);
            return -1;
        }
        if(sem_destroy(&m_items_available) == -1)
        {
            perror(NULL);
            return -1;
        }

        //Detache the shared memmory from the process
        shared_mem.detach();

        //Removes the shared memmory from program control
        shared_mem.remove();
    }

    //Returns 0
    return 0;
}

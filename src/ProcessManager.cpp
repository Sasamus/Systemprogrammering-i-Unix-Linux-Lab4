//=============================================================
// Name        : ProcessManager.cpp
// Author      : Albin Engström
// Created     : 2014-10-08
// Modified    : 2014-10-16
// Description : Implementation of class Processmanager
//=============================================================
#include "ProcessManager.h"

ProcessManager::~ProcessManager()
{
    if(m_pid != 0)
    {
        //Destroys the semaphores
        if(sem_destroy(m_space_available) == -1)
        {
            perror(NULL);
        }
        if(sem_destroy(m_items_available) == -1)
        {
            perror(NULL);
        }

        //Delete the Queue object;
        m_queue->~Queue();

        //Detach the shared memmory from the process
        m_shared_mem->detach();

        //Removes the shared memmory from program control
        m_shared_mem->remove();
    }
}

int ProcessManager::Run(int nr_numbers)
{
    //Calls CreateSharedMem()
    if(CreateSharedMem() == -1)
    {
        return -1;
    }

    //Fork the process and capture the pid
    m_pid = fork();

    //Check if fork() was sucessful
    if(m_pid == -1)
    {
        perror(NULL);
        return -1;
    }

    //Seed rand
    srand(time(NULL));

    //Check if parent or child
    if(m_pid != 0)
    //Parent
    {
        for(int i=0; i < nr_numbers; i++)
        {
            //Wait for space in buffer
            sem_wait(m_space_available);

            //Generate a number
            int nr = rand() % 899 + 100;

            //Add nr to buffer
            m_queue->Enqueue(nr);

            //Print some info to screen
            std::cout << "Producer: " << nr << "   Items in buffer: ";
            std::cout << m_queue->Length() << std::endl;

            //Announce that a number have been added to the buffer
            sem_post(m_items_available);
        }
    }
    else
    //Child
    {
        for(int i=0; i < nr_numbers; i++)
        {
            //Wait for an item to be available in the buffer
            sem_wait(m_items_available);

            //Print some info to screen and remove number from buffer
            std::cout << "Consumer: " << m_queue->Dequeue();
            std::cout << "   Items in buffer: " <<;
            std::cout << m_queue->Length() << std::endl;

            //Announce that an item have been removed from buffer
            sem_post(m_space_available);
        }
    }

    //Returns 0
    return 0;
}

int ProcessManager::CreateSharedMem()
{
    //Calculate the size the SharedMem object should have
    int size = sizeof(m_queue) + sizeof(m_space_available) +
                sizeof(m_items_available);

    //Create a SharedMem object
    m_shared_mem = new SharedMem(IPC_PRIVATE, size);

    //Attach the shared memmory to the process
    if(m_shared_mem->attach() == -1)
    {
        std::cout << "Failed to attach shared memmory" << std::endl;
        return -1;
    }

    //Create a buffer and add it to m_shared_mem
    m_queue = new ((Queue*) m_shared_mem->getAddr()) Queue();

    //Create semaphores and add them to m_shared_mem
    m_space_available = new ((sem_t*) m_shared_mem->getAddr()
                        + sizeof(m_queue)) sem_t();
    m_items_available = new ((sem_t*) m_shared_mem->getAddr()
                        + sizeof(m_queue) + sizeof(m_space_available)) sem_t();

    //Initialize the sempahores
    if(sem_init(m_space_available, 1, Constants::G_BUFFERSIZE) == -1)
    {
        perror(NULL);
        return -1;
    }
    if(sem_init(m_items_available, 1, 0) == -1)
    {
        perror(NULL);
        return -1;
    }

    return 0;
}

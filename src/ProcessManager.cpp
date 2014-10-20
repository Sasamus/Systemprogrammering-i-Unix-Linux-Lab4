//=============================================================
// Name        : ProcessManager.cpp
// Author      : Albin Engström
// Created     : 2014-10-08
// Modified    : 2014-10-20
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

    //Check if parent or child
    if(m_pid != 0)
    //Parent
    {
        //Seed rand
        srand(time(NULL));

        //A variable to hold the generated number
        int nr;

        for(int i=0; i < nr_numbers; i++)
        {
            //Check if parent should sleep
            if(m_parent_sleep == true)
            {
                //Tries to sleep
                if(Sleep() == -1)
                {
                    perror(NULL);
                }

                //Set m_parent_sleep to false
                m_parent_sleep = false;
            }

            //Wait for space in buffer
            sem_wait(m_space_available);

            //Generate a number
            nr =  rand() % 9 + 1;

            //Add nr to buffer
            sem_wait(m_editing_allowed);
            m_queue->Enqueue(nr);
            sem_post(m_editing_allowed);

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
            //Check if parent should sleep
            if(m_child_sleep == true)
            {
                //Tries to sleep
                if(Sleep() == -1)
                {
                    perror(NULL);
                }

                //Set m_child_sleep to false
                m_child_sleep = false;
            }

            //Wait for an item to be available in the buffer
            sem_wait(m_items_available);

            //Print some info to screen and remove number from buffer
            sem_wait(m_editing_allowed);
            std::cout << "Consumer: " << m_queue->Dequeue();
            sem_post(m_editing_allowed);
            std::cout << "   Items in buffer: ";
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
                sizeof(m_items_available) + sizeof(m_editing_allowed);

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
    m_editing_allowed = new ((sem_t*) m_shared_mem->getAddr()
                        + sizeof(m_queue) + sizeof(m_space_available)) sem_t()
                        + sizeof(m_items_available);

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
    if(sem_init(m_editing_allowed, 1, 1) == -1)
    {
        perror(NULL);
        return -1;
    }

    return 0;
}

void ProcessManager::SetParentToSleep()
{
    m_parent_sleep = true;
}

void ProcessManager::SetChildToSleep()
{
    m_child_sleep = true;
}

int ProcessManager::Sleep()
{
    //Creates a timespec to hold the time to sleep
    struct timespec sleep_time;

    //Initializes it's members
    sleep_time.tv_sec = 5;
    sleep_time.tv_nsec = 0;

    //Tries to initiate sleep
    return(nanosleep(&sleep_time, (struct timespec *)NULL));
}

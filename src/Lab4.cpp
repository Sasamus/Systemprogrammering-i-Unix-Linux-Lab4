//=============================================================
// Name         : Lab4.cpp
// Author       : Albin Engström
// Created      : 2014-10-07
// Modified     : 2014-10-20
// Description  : main for project Lab4
// Purpose      : Start the program
//=============================================================
#include "ProcessManager.h"

#include<iostream>
#include<time.h>
#include<signal.h>

using namespace std;

//Create a ProcessManager object
ProcessManager process_manager;

//Handles signals
//Send SIGUSR1 to the parent process to make it sleep
//Send SIGUSR2 to the child process to make it sleep
static void SIGHandler(int pSIG)
{
	if(pSIG == SIGUSR1)
	{
		process_manager.SetParentToSleep();
	}
	else if(pSIG == SIGUSR2)
	{
		process_manager.SetChildToSleep();
	}
}

int main(int argc, char* argv[])
{
    //Sets some signals to be handled by a custom handler
	struct sigaction act;
	act.sa_handler = SIGHandler;
	if(sigaction(SIGUSR1, &act, 0) == -1 || sigaction(SIGUSR2, &act, 0) == -1)
	{
		perror("Error");
		exit(-1);
	}

    //Check for arguments
    if(argc == 2)
    {
        //Call it's Run function
        if(process_manager.Run(atoi(argv[1])) == -1)
        {
            cout << "Failed to run ProcessManager" << endl;
            return -1;
        }
    }
    else
    {
        //Call it's Run function
        if(process_manager.Run(1000) == -1)
        {
            cout << "Failed to run ProcessManager" << endl;
            return -1;
        }
    }

    return 0;
}

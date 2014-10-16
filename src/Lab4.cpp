//=============================================================
// Name         : Lab4.cpp
// Author       : Albin Engström
// Created      : 2014-10-07
// Modified     : 2014-10-16
// Description  : main for project Lab4
// Purpose      : Start the program
//=============================================================
#include "ProcessManager.h"

#include<iostream>

using namespace std;

int main(int argc, char* argv[])
{
    //Create a ProcessManager object
    ProcessManager process_manager;

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

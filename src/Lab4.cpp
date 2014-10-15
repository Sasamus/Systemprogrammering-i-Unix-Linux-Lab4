//=============================================================
// Name         : Lab4.cpp
// Author       : Albin Engström
// Created      : 2014-10-07
// Modified     : 2014-10-15
// Description  : main for project Lab4
// Purpose      : Start the program
//=============================================================
#include "ProcessManager.h"

#include<iostream>

using namespace std;

int main()
{
    //Create a ProcessManager object
    ProcessManager process_manager;

    //Call it's Run function
    if(process_manager.Run() == -1)
    {
        cout << "Failed to run ProcessManager" << endl;
        return -1;
    }

    return 0;
}

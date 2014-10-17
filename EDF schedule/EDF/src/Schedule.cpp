/*
 *       \file       Schedule.cc
 *
 *       \brief      Class definition for LDF Scheduling and RM Scheduling
 *
 *       \compiler   g++\n
 *
 *       \author     Piyush Prakash, achyutapiyush@gmail.com
 *       \license    GNU General Public License Version 2
 *       \copyright  Copyright (c) 2014, B&B Developers
 *                   jashnmalhi@yahoo.in
 */
#include<iostream>
#include<cstdlib>
#include<windows.h>
#include<math.h>
#include "../include/Schedule.h"
#include "../include/BasicStruct.h"
using namespace std;

Schedule::Schedule()
{
    //ctor
}

Schedule::~Schedule()
{
    //dtor
}
/*
 *      \class  Schedule
 *      \fn     Schedule :: runEDF()
 *      \brief  User given data of Processes is collected then evaluated if they are schedulable or not.
 *              The schedulable processes are executed one by one in the scheduled order.
 */
int Schedule::runEDF ()
{
    //Collect the list of processes
    Schedule::collectProcess();

    //Now we have the data, check if feasible

    if (Schedule::is_EDFSchedulable())
    {
        std::cout<<"Tasks are EDF Schedulable\n";
    }
    else
    {
        std::cout<<"Tasks are not EDF Schedulable";
        return false;
    }

/*
 *      \class  Schedule
 *      \brief
 */
     ProcessList local = Schedule::processes;

     while (!local.empty())
     {
         Process temp = local.top();
         local.pop();
         cout<<"Executing "<<temp.processname<<endl;
         Sleep(1000);
     }

}

void Schedule::loadProcessFromFile()
{
    //
}
int Schedule::runRM ()
{
    float total_util;
    int n;

    //Collect the list of processes
    Schedule::collectProcess();

    //Now we have the data, check if feasible
    RMUtil result = Schedule::is_RMSchedulable();
    if (result.feasible)
    {
        std::cout<<"Tasks are RM Schedulable\tu=" << result.total_util << " n=" << result.n << "\n";
    }
    else
    {
        std::cout<<"Tasks are not RM Schedulable\tu="<< result.total_util <<" n="<< result.n <<"\n";
        return false;
    }

    //Start running tasks
     ProcessListRM local = Schedule::convertRM(Schedule::processes);

     while (!local.empty())
     {
         Process temp =et  local.top();
         local.pop();
         cout<<"\nExecuting "<<temp.processname<<" expected time "<<temp.execution_time<<"sec......"<<endl;
         Sleep(temp.execution_time*1000);
     }

}

ProcessListRM Schedule::convertRM(ProcessList processes)
{
    ProcessListRM converted;

    //Now copy the contents
    while(!processes.empty())
    {
        converted.push(processes.top());
        processes.pop();
    }

    return converted;
}


int Schedule::collectProcess()
{
    int no_process;
    //Ask first, how many?
    std::cout<<"How many processes are there?";
    cin>>no_process;

    ProcessList collected_process;
    char buffer [33];
    for (int count = 0; count < no_process; ++count)
    {
        Process temp_process;
        temp_process.collectdata();
        itoa(count, buffer, 10);
        temp_process.set_name("Task " + string(buffer));
        collected_process.push(temp_process);
    } //After this we will have all the process sorted according to deadline

    //Save the tasks in the class
    Schedule::processes = collected_process;

}

bool Schedule::is_EDFSchedulable()
{
    //Calculate the utilization
    float total_util = 0.0;
    ProcessList local = Schedule::processes;

    while(!local.empty())
    {
        Process temp_process = local.top();
        local.pop();
        total_util = (float) temp_process.execution_time/temp_process.period;
    }

    //Check if it is greater than 1
    if (total_util < 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
RMUtil Schedule::is_RMSchedulable()
{
    //Calculate the utilization
    float n, total_util;
    ProcessList local = Schedule::processes;

    int no_process = local.size();
    while(!local.empty())
    {
        Process temp_process = local.top();
        local.pop();
        total_util = (float) temp_process.execution_time/temp_process.period;
    }
    n=(float)no_process*(pow(2.0,1/no_process)-1);

    //Check if it is greater than n

    RMUtil result;
    result.n = n;
    result.total_util = total_util;


    if (total_util <= n)
    {
        result.feasible = true;
    }
    else
    {
        result.feasible = false;
    }

    return result;
}

void Schedule::PrintTasks()
{
    ProcessList local = Schedule::processes;

    if (local.empty())
    {
        cout<<"There is no task to display";
        return;
    }

    while(!local.empty())
    {
        Process temp = local.top();
        local.pop();
        cout<<temp.absolute_deadline<<endl;
    }
}

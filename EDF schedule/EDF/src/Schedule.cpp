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
 *      \fnctn  Schedule :: runEDF()
 *      \brief  User given data of Processes for EDF scheduling is collected then evaluated if they are schedulable or not.
 *              The schedulable processes are executed one by one.
 */
int Schedule::runEDF ()
{
    Schedule::collectProcess();

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
 *      \brief  All the processes for EDF scheduling are stored in a local variable named "local".
                It will prioritize the processes according to their deadline time.
 *              The "local.top()" will return the topmost process from the priority queue "local".
 *              This topmost process is stored in "temp" variable of "process" type.
 *              That process will be removed from the queue so as to get next topmost process.
 *              Now the process is executed after deletion from queue by calling "temp.processname".
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
/*
 *      \class  Schedule
 *      \fnctn  Schedule :: loadProcessFromFile()
 *      \brief
 */
void Schedule::loadProcessFromFile()
{
    //
}
/*
 *      \class  Schedule
 *      \fnctn  Schedule :: rumRM()
 *      \brief  User will be asked to type the process data for RM scheduling through "collectprocess" function then,
 *              If the user given processes are schedulable i.e. if they satisfy the equation u<=n
 *              Then the processes will be scheduled and executed in a arranged sequence.
 */
int Schedule::runRM ()
{
    float total_util;
    int n;

    Schedule::collectProcess();


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

/*
 *      \class  Schedule
 *      \fnctn  Schedule::convertRM(Schedule::processes);
 *      \brief  All the processes for RM scheduling are stored in a local variable named "local".
 *              The "local.top()" will return the topmost process from the priority queue "local".
 *              This topmost process is stored in "temp" variable of "process" type.
 *              That process will be removed from the queue so as to get next topmost process.
 *              Now the process is executed after deletion from queue by calling "temp.processname".
 */
     ProcessListRM local = Schedule::convertRM(Schedule::processes);

     while (!local.empty())
     {
         Process temp = local.top();
         local.pop();
         cout<<"\nExecuting "<<temp.processname<<" expected time "<<temp.execution_time<<"sec......"<<endl;
         Sleep(temp.execution_time*1000);
     }

}
/*
 *      \class  Schedule
 *      \fnctn  ProcessListRM Schedule::convertRM(ProcessList processes)
 *      \brief  The processes are stored in ProcessListRM so as to prioritize them
 *              according to their execution time.untill the process variable is not empty
 *              the loop will push the topmost process into the converted variable and then
 *              pop out that process from "process" variable."converted" variable will store
 *              the prioritized processes.Once the processes variable is empty
 *              the function will return converted.
 */

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

/*
 *      \class  Schedule
 *      \fnctn  Schedule::collectProcess()
 *      \brief  A local variable named "no_process" will store the total no of process(given by user)
 *              The data related to the processes(execution time, period, deadline) is then collected.
 *              "temp_process.collectdata()" will take the user input of process data in a loop untill
 *              the count < no_process.
 *              Set_name is used to give a unique name to each process (eg: Task1 , Task2)
 *              Then the data is pushed to a variable "collected_process" of processlist type.
 */
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

/*
 *      \class  Schedule
 *      \fnctn  Schedule::is_EDFSchedulable()
 *      \brief  The while loop will calculate the total utilization bound factor so as to check if the given data
 *              is schedulable according to EDF schedule or not, total_util variable holds that value.
 *              total_util is calculated as summation of (execution time/period) of all processes.
 *              if total_util holds a value which is smaller than 1 then processes are schedulable else they are not.
 *
 */
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

/*
 *      \class  Schedule
 *      \fnctn  Schedule::is_EDFSchedulable()
 *      \brief  The while loop will calculate the total utilization bound factor so as to check if the given data
 *              is schedulable according to RM schedule or not, total_util variable holds that value.
 *              total_util is calculated as summation of (execution time/period) of all processes.
 *              n variable stores the number of processes to be scheduled.
 *              if total_util holds a value which is smaller than or equals to n then processes are schedulable else they are not.
 *
 */
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

/*
 *      \class  Schedule
 *      \fnctn  Schedule::PrintTasks()
 *      \brief  A variable "local" will hold all the processes and their data, if it is empty then
 *              message"There is no task to display" will be displayed else the process data will be displayed
 *              through the "temp" variable.
 */

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

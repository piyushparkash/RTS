#include<iostream>
#include<cstdlib>
#include<windows.h>
#include<math.h>
#include "../include/Schedule.h"
using namespace std;

float total_util = 0.0,n,no_process = 0;
Schedule::Schedule()
{
    //ctor
}

Schedule::~Schedule()
{
    //dtor
}

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

    //Start running tasks
     ProcessList local = Schedule::processes;

     while (!local.empty())
     {
         Process temp = local.top();
         local.pop();
         cout<<"Executing "<<temp.processname<<endl;
         Sleep(1000);
     }

}
int Schedule::runRM ()
{
    //Collect the list of processes
    Schedule::collectProcess();

    //Now we have the data, check if feasible

    if (Schedule::is_RMSchedulable())
    {
        std::cout<<"Tasks are RM Schedulable\tu="<<total_util<<" n="<<n<<"\n";
    }
    else
    {
        std::cout<<"Tasks are not RM Schedulable\tu="<<total_util<<" n="<<n<<"\n";
        return false;
    }

    //Start running tasks
     ProcessList local = Schedule::processes;

     while (!local.empty())
     {
         Process temp = local.top();
         local.pop();
         cout<<"\nExecuting "<<temp.processname<<" expected time "<<temp.execution_time<<"sec......"<<endl;
         Sleep(temp.execution_time*1000);
     }

}

int Schedule::collectProcess()
{
    //Ask first, how many?
    std::cout<<"How many processes are there?";
    cin>>no_process;

    ProcessList collected_process;
    char buffer [33];
    for (int count = 0; count < no_process; ++count)
    {
        Process temp_process;
        temp_process.collectdata();
//        itoa(count, buffer, 10);
        temp_process.set_name("Task " + string(buffer));
        collected_process.push(temp_process);
    } //After this we will have all the process sorted according to deadline

    //Save the tasks in the class
    Schedule::processes = collected_process;

}

bool Schedule::is_EDFSchedulable()
{
    //Calculate the utilization
    //float total_util = 0.0;
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
bool Schedule::is_RMSchedulable()
{
    //Calculate the utilization

    ProcessList local = Schedule::processes;

    while(!local.empty())
    {
        Process temp_process = local.top();
        local.pop();
        total_util = (float) temp_process.execution_time/temp_process.period;
    }
    n=(float)no_process*(pow(2.0,1/no_process)-1);
    //Check if it is greater than n
    if (total_util <= n)
    {
        return true;
    }
    else
    {
        return false;
    }
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

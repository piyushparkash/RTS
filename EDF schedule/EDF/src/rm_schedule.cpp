#include<iostream>
#include<cstdlib>
#include<windows.h>
#include "../include/rm_schedule.h"
using namespace std;

rm_shedule::rm_schedule()
{
    //ctor
}

rm_schedule::~rm_schedule()
{
    //dtor
}

int rm_schedule::runRM ()
{
    //Collect the list of processes
    rm_schedule::collect_task();

    //Now we have the data, check if feasible

    if (rm_schedule::is_RMschedulable())
    {
        std::cout<<"Tasks are RM Schedulable\n";
    }
    else
    {
        std::cout<<"Tasks are not RM Schedulable";
        return false;
    }

    //Start running tasks
     ProcessList rm_local = rm_schedule::rm_processes;

     while (!rm_local.empty())
     {
         Process temp = rm_local.top();
         rm_local.pop();
         cout<<"Executing "<<temp.processname<<endl;
         Sleep(1000);
     }

}

int rm_schedule::collect_task()
{
    //Ask first, how many?
    int no_process = 0;
    std::cout<<"How many processes are there?";
    cin>>no_process;

    ProcessList collected_task;
    char buffer [33];
    for (int count = 0; count < no_process; ++count)
    {
        Process temp_process;
        temp_process.collectdata();
        //itoa(count, buffer, 10);
        temp_process.set_name("Task " + string(buffer));
        collected_task.push(temp_process);
    } //After this we will have all the process sorted according to deadline

    //Save the tasks in the class
    rm_schedule::rm_processes = collected_task;

}

bool rm_schedule::is_RMschedulable()
{
    //Calculate the utilization
    float total_util = 0.0,n;
    ProcessList rm_local = rm_schedule::rm_processes;

    while(!rm_local.empty())
    {
        Process temp_process = rm_local.top();
        rm_local.pop();
        total_util = (float) temp_process.ex_time/temp_process.p_time;
    }
    n=(float)no_process*(pow(2.0,1/no_process)-1);
    //Check if it is greater than 1
    if (total_util <= n)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void rm_schedule::Print_taskSata()
{
    ProcessList rm_local = rm_schedule::rm_processes;

    if (local.empty())
    {
        cout<<"There is no task to display";
        return;
    }

    while(!rm_local.empty())
    {
        Process temp = rm_local.top();
        rm_local.pop();
        cout<<temp.absolute_deadline<<endl;
    }
}


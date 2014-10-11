#include<iostream>
#include "../include/Schedule.h"
using namespace std;

Schedule::Schedule()
{
    //ctor
}

Schedule::~Schedule()
{
    //dtor
}

int Schedule::run ()
{
    //Collect the list of processes
    Schedule::collectProcess();
}

int Schedule::collectProcess()
{
    //Ask first, how many?
    int no_process = 0;
    std::cout<<"How many processes are there?";
    cin>>no_process;

    ProcessList collected_process;
    for (int count = 0; count < no_process; ++count)
    {
        Process temp_process;
        temp_process.collectdata();
        collected_process.push(temp_process);
    } //After this we will have all the process sorted according to deadline

    //Save the tasks in the class
    Schedule::processes = collected_process;

}

void Schedule::PrintTasks()
{
    ProcessList local = Schedule::processes;

    while(!local.empty())
    {
        Process temp = local.top();
        local.pop();
        cout<<temp.absolute_deadline<<endl;
    }
}

#include "../include/Process.h"
#include <iostream>
using namespace std;
Process::Process()
{
    //ctor
}

Process::~Process()
{
    //dtor
}

void Process::set_period(int userperiod)
{
    Process::is_periodic = true;
    period = userperiod;
}

void Process::user_period()
{
    int period;
    std::cout<<"Period of the process:";
    std::cin>>period;
    Process::set_period(period);
}

void Process::set_name(string name)
{
    Process::processname = name;
}

void Process::collectdata()
{
    cout<<"Execution time of task:";
    cin>>Process::execution_time;

    cout<<"Period Of Task:";
    cin>>Process::period;

    cout<<"Absolute Deadline of Task:";
    cin>>Process::absolute_deadline;
}

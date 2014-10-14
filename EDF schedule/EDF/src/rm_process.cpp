#include "../include/rm_process.h"
#include <iostream>
using namespace std;
rm_process::rm_process()
{
    //ctor
}

rm_process::~rm_process()
{
    //dtor
}

void rm_process::set_period(int userperiod)
{
    rm_process::is_periodic = true;
    period = userperiod;
}

void rm_process::user_period()
{
    int period;
    std::cout<<"Period of the process:";
    std::cin>>period;
    rm_process::set_period(period);
}

void rm_process::set_name(string name)
{
    rm_process::processname = name;
}

void rm_process::collectdata()
{
    cout<<"Execution time of task:";
    cin>>Process::ex_time;

    cout<<"Period Of Task:";
    cin>>Process::p_time;

    cout<<"Absolute Deadline of Task:";
    cin>>Process::absolute_deadline;
}


#include "../include/Process.h"
#include <iostream>
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

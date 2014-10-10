#include "Process.h"

Process::Process()
{
    //ctor
}

Process::~Process()
{
    //dtor
}

bool set_period(int userperiod)
{
    is_periodic = true;
    period = userperiod;
}

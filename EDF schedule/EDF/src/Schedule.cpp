#include "../include/Schedule.h"

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
    ProcessList localprocess = Schedule::processes;

}

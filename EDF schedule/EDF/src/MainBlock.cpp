#include "MainBlock.h"

using namespace std;
Processor::Processor()
{
    VoltageLevel = {2, 3};
}

bool Processor::operator==(Processor tocompare)
{
    if (tocompare.id == id)
    {
        return true;
    }
    else
    {
        return false;
    }
}

TaskMap Processor::filter_by_processor(TaskMap mappedvar, int id)
{
    //We have to filter out results for the processor
    TaskMap result_map;
    for (unsigned int i = 0; i < mappedvar.size(); i++)
    {
        if (id == (*mappedvar[i].processor).id)
        {
            result_map.push_back(mappedvar[i]);
        }
    }

    return result_map;
}

float Processor::calculateUtil(TaskMap mappedvar)
{
    //Get all the task which are allocated to this processor
    TaskMap onthischip = filter_by_processor(mappedvar, this->id);

    //Calculate utilization of all tasks
    float total_util = 0.0;
    for (unsigned int i = 0; i < onthischip.size(); i++)
    {
        total_util += (float)onthischip[i].task.execution_time / onthischip[i].task.period;
    }

    return total_util;
}

Process::Process()
{
    executed = 0;
}

/**
 *      \file   Process.cc
 *      \fnctn  Process::set_period(int userperiod)
 *      \brief  It will get the value of process period as a argument and
 *              then will pass that value to the variable "period".
 */
void Process::set_period(int userperiod)
{
    Process::is_periodic = true;
    period = userperiod;
}

/**
 *      \file   Process.cc
 *      \fnctn  Process::user_period(int userperiod)
 *      \brief  It will get the value of process period from the user through console and
 *              then will pass that value to the function "set_period(period)".
 */
void Process::user_period()
{
    int period;
    std::cout<<"Period of the process:";
    std::cin>>period;
    Process::set_period(period);
}

/**
 *      \file   Process.cc
 *      \fnctn  Process::set_name(string name)
 *      \brief  It will get the value of process name as a argument and
 *              then will pass that value to the variable "processname".
 */
void Process::set_name(std::string name)
{
    Process::processname = name;
}
/**
 *      \file   Process.cc
 *      \fnctn  Process::collectdata()
 *      \brief  It will get the value of process execution_time,Period,Absolute Deadline as a
 *              input from user through console.
 */
void Process::collectdata()
{

    cout<<"Period Of Task:";
    cin>>Process::period;
    Process::period_completed=Process::period;

    cout<<"Arrival time Of Task:";
    cin>>Process::arrival_time;

    cout<<"Absolute Deadline of Task:";
    cin>>Process::absolute_deadline;

    Process::priority=0;
}

/** \brief
 *
 * \param tocompare Process
 * \return bool
 *
 */
bool Process::operator == (Process tocompare)
{
    if (Process::id == tocompare.id)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
 *       \file       Process.cc
 *
 *       \brief      Class definition for processes and its data.
 *
 *       \compiler   g++\n
 *
 *       \author     Piyush Prakash, achyutapiyush@gmail.com
 *       \license    GNU General Public License Version 2
 *       \copyright  Copyright (c) 2014, B&B Developers
 *                   jashnmalhi@yahoo.in
 */

#include "../include/Process.h"
#include <iostream>
using namespace std;


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
void Process::set_name(string name)
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
    cout<<"Execution time of task:";
    cin>>Process::execution_time;
    Process::executed=Process::execution_time;

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

/** \brief
 *
 * \return bool
 *
 */
bool Process::isComplete()
{
    if (Process::executed == Process::execution_time)
    {
        return true;
    }
    else
    {
        return false;
    }
}

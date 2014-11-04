/*
 *       \file       Schedule.cpp
 *
 *       \brief      Class definition for LDF Scheduling and RM Scheduling
 *
 *       \compiler   g++\n
 *
 *       \author     Piyush Prakash, achyutapiyush@gmail.com
 *       \license    GNU General Public License Version 2
 *       \copyright  Copyright (c) 2014, B&B Developers
 *                   jashnmalhi@yahoo.in
 */

#include<iostream>
#include<cstdlib>
#include<windows.h>
#include<math.h>
#include "../include/Schedule.h"
#include "../include/BasicStruct.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

Schedule::Schedule()
{
    //ctor
}

Schedule::~Schedule()
{
    //dtor
}

bool Schedule::allScheduled(usProcessList localprocesslist)
{
    bool found = false;


    for(unsigned int i = 0; i < localprocesslist.size(); i++)
    {
        if (localprocesslist[i].execution_time != localprocesslist[i].executed)
        {
            found = true;
            break;
        }
    }

    return !found;
}


usProcessList Schedule::getNotScheduled(usProcessList localprocesslist)
{
    for (int i = 0; i < localprocesslist.size(); i++)
    {
        if (localprocesslist[i].executed != localprocesslist[i].execution_time)
        {
            localprocesslist.erase(localprocesslist.begin()+5);
        }
    }

    return localprocesslist;
}


usProcessList::iterator Schedule::find_next_process(usProcessList &localprocesslist, unsigned int time, int &nothing)
{
    usProcessList processatt;
    usProcessList::iterator it;
    unsigned int index, priority;

    index = priority = localprocesslist.size(); //Set to max priority

    for (int i = 0; i < localprocesslist.size(); i++)
    {
        if (localprocesslist[i].arrival_time <= time)
        {
            processatt.push_back(localprocesslist[i]);
            if (localprocesslist[i].priority < priority)
            {
                priority = localprocesslist[i].priority;
                index = i;
            }
        }
    }

    //If no process is there at this time. Pull the flag
    if (processatt.size() == 0)
    {
        nothing = 1;
    }

    // If the above flag is true, then this is of no importance
    it = localprocesslist.begin()+index;
    return it;
}


void Schedule::execute_onesec(usProcessList::iterator localprocess, unsigned int time)
{
    if (localprocess->executed == 0)
    {
        cout<<"Task "<< localprocess->id <<" started executing at T = " << time << endl;
    }
    else
    {
        cout<<"Task "<< localprocess->id <<" resumed execution at T = " << time << endl;
    }
    localprocess->executed++; //Increment stating, it has executed for 1 sec
}

/*
 *      \class  Schedule
 *      \fnctn  Schedule :: runEDF()
 *      \brief  User given data of Processes for EDF scheduling is collected then evaluated if they are schedulable or not.
 *              The schedulable processes are executed one by one.
 */

int Schedule::runEDF ()
{
    Schedule::loadProcessFromFile("Sample.txt");

    PrintTasks();

    if (Schedule::is_EDFSchedulable())
    {
        std::cout<<"Tasks are EDF Schedulable\n";
    }
    else
    {
        std::cout<<"Tasks are not EDF Schedulable";
        return false;
    }


    usProcessList localprocesslist = Schedule::copyto_vector(Schedule::processes);
    Schedule::set_priority(localprocesslist);
    unsigned int mainTime = 0;
    usProcessList::iterator next_process, current_process;

    //Sorted according to arrival time
    RMarrival sortrm;
    sort(localprocesslist.begin(), localprocesslist.end(), sortrm);

    int nothing = 0;

    while(!localprocesslist.empty())
    {
        //Find the next process to execute
        next_process = Schedule::find_next_process(localprocesslist, mainTime, nothing);

        if (nothing == 1)
        {
            //The processor is going to be idle for this one
            cout<<"The processor is going to be idle for this one" << endl;

            //Reset the idle flag
            nothing = 0;
            mainTime++;
            continue;
        }

        if (idle) //If the previous task has completed its execution, there is nothing on the processor
        {
            execute_onesec(next_process, mainTime);
            idle = false;
        }
        else if (next_process == current_process || mainTime == 0)
        {
            execute_onesec(next_process, mainTime);
        }
        else
        {
            preempt_process(current_process, next_process, mainTime);
            execute_onesec(current_process, mainTime);
        }

        //One sec work is done, increment the time
        mainTime++;

        //Check if the process has completed
        if (next_process->isComplete())
        {
            cout<<"Task " << next_process->id << " has completed it processing at time T = " << mainTime << endl;
            removeTask(next_process, localprocesslist);
            idle = true;
        }
        else
        {
            //Store our current process
            current_process = next_process;
        }

        //Reset the idle flag
        nothing = false;

    }
    //Start the loop
    //Check if there is any process to be scheduled
    //Arrange the process according to deadlines

    //Create a function to arrange and return the first element after arranging.
    //


}


void Schedule::removeTask(usProcessList::iterator toremove, usProcessList &inthis)
{
        inthis.erase(toremove);
}



/** \brief This function swaps the current process with the process with which
            it would be preempted.
 *
 * \param Process nextone Process which will preempted the current process
 * \param Process firstone The current process which was running
 * \param usigned time The main time counter
 * \return none
 *
 */
void Schedule::preempt_process(usProcessList::iterator firstone, usProcessList::iterator nextone, unsigned int time)
{
    //Print the Preemption
    cout<< "Task " << firstone->id <<" was preempted by Task " << nextone->id << " at T = " << time << endl;

    //Copy the contents of the nextone in the firstone
    firstone = nextone;
}



/**
 *      \brief This functions loads the process from the file which is passed
 *             as a parameter to the functions. These parameters are written
 *             in the file delimited by space and one Process per line
 *      \param string filename The name of the file which contains the parameters
 */
void Schedule::loadProcessFromFile(string filename)
{
    fstream file;
    string line;
    file.open(filename.c_str());

    if (!file.is_open())
    {
        cout<<"Could not find file. Please check";
        return;
    }

    string var;
    vector<string> tokens;
    Process temp;
    int counter = 0;


    while(!file.eof())
    {
        //Right Now we have 3 variables that needs to be fetched
        std::getline(file,line);
        istringstream streamline(line);

        //get the three written numbers in the file
        while (streamline >> var)
        {
            tokens.push_back(var);
            var.clear();
        }

        //Insert value in the Process;
        temp.execution_time = atoi(tokens[0].c_str());
        temp.period = atoi(tokens[1].c_str());
        temp.absolute_deadline = atoi(tokens[2].c_str());
        temp.arrival_time = atoi(tokens[3].c_str());
        temp.id = counter;

        Schedule::processes.push(temp);


        //Reset the vector and the string
        tokens.erase(tokens.begin(), tokens.end());
        var.clear();
        counter++;
    }
}


/*
 *      \class  Schedule
 *      \fnctn  Schedule :: rumRM()
 *      \brief  User will be asked to type the process data for RM scheduling through "collectprocess" function then,
 *              If the user given processes are schedulable i.e. if they satisfy the equation u<=n
 *              Then the processes will be scheduled and executed in a arranged sequence.
 */

int Schedule::runRM ()
{
    vector <Process> temp;

    int total=0;
    int total_time;


    Schedule::loadProcessFromFile("Sample.txt");


    RMUtil result = Schedule::is_RMSchedulable();
    if (result.feasible)
    {
        std::cout<<"Tasks are RM Schedulable\tu=" << result.total_util << " n=" << result.n << "\n";
        //
        ProcessListRM local = Schedule::convertRM(Schedule::processes);

        //copy processlist to vector
        while (!local.empty())
        {
            temp.push_back(local.top());
            local.pop();
            total++;
        }

        //function to set value to priority variable according to the asscending order of their period.
        for(int j=0; j<total; j++)
        {
            temp[j].priority=j;
        }
        //function to compare the processes according to their arrival time
        for(int m=0; m<total; m++)
        {
            for(int k=0; k<total; k++)
            {
                if(temp[k].arrival_time>temp[k+1].arrival_time)
                {
                    usProcessList for_sort(2);
                    for_sort.push_back(temp[k]);
                    temp[k]=temp[k+1];
                    temp[k+1]=for_sort[0];
                }
            }
            total_time=total_time+temp[m].execution_time;
        }
        //function to find schedule for preempted tasks
        Schedule::RM_preemptive(total_time,temp,total);
    }
    else
    {
        std::cout<<"Tasks are not RM Schedulable\tu="<< result.total_util <<" n="<< result.n <<"\n";
        return false;
    }

    //Start running tasks
    /* ProcessListRM local = Schedule::convertRM(Schedule::processes);

    while (!local.empty())
    {
        Process temp = local.top();
        local.pop();
        cout<<"\nExecuting "<<temp.processname<<" expected time "<<temp.execution_time<<"sec......"<<endl;
        Sleep(temp.execution_time*1000);
    }
    */
}


/*
 *      \class  Schedule
 *      \fnctn  ProcessListRM Schedule::convertRM(ProcessList processes)
 *      \brief  The processes are stored in ProcessListRM so as to prioritize them
 *              according to their period time.untill the process variable is not empty
 *              the loop will push the topmost process into the converted variable and then
 *              pop out that process from "process" variable."converted" variable will store
 *              the prioritized processes.Once the processes variable is empty
 *              the function will return converted.
 */

ProcessListRM Schedule::convertRM(ProcessList processes)
{
    ProcessListRM converted;

    //Now copy the contents
    while(!processes.empty())
    {
        converted.push(processes.top());
        processes.pop();
    }

    return converted;
}

void Schedule::set_priority(usProcessList &localprocesslist)
{
    for (int i = 0; i < localprocesslist.size(); i++)
    {
        localprocesslist[i].priority = i;
    }
}

ProcessListarrive Schedule::compare(ProcessList processes)
{
    ProcessListarrive arrival;

    //Now copy the contents
    while(!processes.empty())
    {
        arrival.push(processes.top());
        processes.pop();
    }

    return arrival;
}


usProcessList Schedule::copyto_vector(ProcessList local)
{
    usProcessList temp;

    while(!local.empty())
    {
        temp.push_back(local.top());
        local.pop();
    }

    return temp;
}

void Schedule::RM_preemptive(int total_time,usProcessList arrived,int total)
{
    int i=0,n;
    cout<<"\n ..........STARTED first Task "<<arrived[0].processname<<" at T = "<<total_time<<endl;
    while(total_time!=0)
    {
        if(arrived[i].execution_time==0)
        {
            cout<<"\n .... "<<arrived[i].processname<<" has FINISHED...at T = "<<total_time<<endl;
            Sleep(1000);
            i++;
            cout<<"\n\n ..........STARTED "<<arrived[i].processname<<" at T = "<<total_time<<endl;
            //arrived.erase(arrived.begin()+i);
            //arrived.pop_back();

        }
        else if(arrived[i].execution_time>=1 & arrived[i].arrival_time == arrived[i+1].arrival_time)
        {
            if(arrived[i].priority < arrived[i+1].priority)
            {
                Sleep(1000);
                cout<<"\n Still Executing "<<arrived[i].processname<<" time-remaining "<<arrived[i].execution_time<<"sec......"<<endl;
                Sleep(1000);
                arrived[i].execution_time=arrived[i].execution_time-1;
                arrived[i].arrival_time=arrived[i].arrival_time+1;
                i++;
            }
            else
            {
                cout<<"\n"<<arrived[i].processname<<" has been preempted by task "<<arrived[i+1].processname<<endl;
                vector <Process> tempry(2);
                Sleep(2000);
                cout<<"\n\n ..........STARTED "<<arrived[i+1].processname<<" at T = "<<total_time<<endl;
                tempry[0]=arrived[i];
                arrived[i]=arrived[i+1];
                arrived[i+1]=tempry[0];
                arrived[i].execution_time=arrived[i].execution_time-1;
                arrived[i].arrival_time=arrived[i].arrival_time+1;

            }
            total_time=total_time-1;
        }
        else
        {
            cout<<"\n Executing "<<arrived[i].processname<<" time-remaining "<<arrived[i].execution_time<<"sec......"<<endl;
            Sleep(1000);
            arrived[i].execution_time=arrived[i].execution_time-1;
            arrived[i].arrival_time=arrived[i].arrival_time+1;
            total_time=total_time-1;
        }
    }
    cout<<"\n****************ALL the processes has been FINISHED**************** "<<endl;
}

/*
 *      \class  Schedule
 *      \fnctn  Schedule::collectProcess()
 *      \brief  A local variable named "no_process" will store the total no of process(given by user)
 *              The data related to the processes(execution time, period, deadline) is then collected.
 *              "temp_process.collectdata()" will take the user input of process data in a loop untill
 *              the count < no_process.
 *              Set_name is used to give a unique name to each process (eg: Task1 , Task2)
 *              Then the data is pushed to a variable "collected_process" of processlist type.
 */
int Schedule::collectProcess()
{
    int no_process;
    //Ask first, how many?
    std::cout<<"How many processes are there?";
    cin>>no_process;

    ProcessList collected_process;
    char buffer [33];
    for (int count = 0; count < no_process; ++count)
    {
        Process temp_process;
        temp_process.collectdata();
        snprintf(buffer, sizeof(buffer), "%d", count+1);
        //itoa(count, buffer, 10);
        temp_process.set_name("Task " + string(buffer));
        collected_process.push(temp_process);
    } //After this we will have all the process sorted according to deadline

    //Save the tasks in the class
    Schedule::processes = collected_process;

}


/*
 *      \class  Schedule
 *      \fnctn  Schedule::is_EDFSchedulable()
 *      \brief  The while loop will calculate the total utilization bound factor so as to check if the given data
 *              is schedulable according to EDF schedule or not, total_util variable holds that value.
 *              total_util is calculated as summation of (execution time/period) of all processes.
 *              if total_util holds a value which is smaller than 1 then processes are schedulable else they are not.
 *
 */
bool Schedule::is_EDFSchedulable()
{
    //Calculate the utilization
    float total_util = 0.0;
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

/*
 *      \class  Schedule
 *      \fnctn  Schedule::is_RMSchedulable()
 *      \brief  The while loop will calculate the total utilization bound factor so as to check if the given data
 *              is schedulable according to RM schedule or not, total_util variable holds that value.
 *              total_util is calculated as summation of (execution time/period) of all processes.
 *              n variable stores the number of processes to be scheduled.
 *              if total_util holds a value which is smaller than or equals to n then processes are schedulable else they are not.
 *
 */
RMUtil Schedule::is_RMSchedulable()
{
    //Calculate the utilization
    float n, total_util;
    ProcessList local = Schedule::processes;

    float no_process = local.size();
    while(!local.empty())
    {
        Process temp_process = local.top();
        local.pop();
        total_util = (float) temp_process.execution_time/temp_process.period;
    }
    n = no_process * (pow(2, 1 / no_process) - 1);

    //Check if it is greater than n

    RMUtil result;
    result.n = n;
    result.total_util = total_util;


    if (total_util <= n)
    {
        result.feasible = true;
    }
    else
    {
        result.feasible = false;
    }

    return result;
}

/*
 *      \class  Schedule
 *      \fnctn  Schedule::PrintTasks()
 *      \brief  A variable "local" will hold all the processes and their data, if it is empty then
 *              message"There is no task to display" will be displayed else the process data will be displayed
 *              through the "temp" variable.
 */

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
        cout<<temp.id<<endl;
    }

}

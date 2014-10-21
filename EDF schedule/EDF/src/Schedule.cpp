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


using namespace std;

Schedule::Schedule()
{
    //ctor
}

Schedule::~Schedule()
{
    //dtor
}

usProcessList ProcessatT(int time)
{

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

    if (Schedule::is_EDFSchedulable())
    {
        std::cout<<"Tasks are EDF Schedulable\n";
    }
    else
    {
        std::cout<<"Tasks are not EDF Schedulable";
        return false;
    }


    ProcessList local = Schedule::processes;

    //Start the loop
    //Check if there is any process to be scheduled
    //Arrange the process according to deadlines

    //Create a function to arrange and return the first element after arranging.
    //


}
/*
 *      \class  Schedule
 *      \fnctn  Schedule :: loadProcessFromFile()
 *      \brief
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

        Schedule::processes.push(temp);


        //Reset the vector and the string
        tokens.erase(tokens.begin(), tokens.end());
        var.clear();
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
    float total_util;


    Schedule::collectProcess();


    RMUtil result = Schedule::is_RMSchedulable();
    if (result.feasible)
    {
        std::cout<<"Tasks are RM Schedulable\tu=" << result.total_util << " n=" << result.n << "\n";
         ProcessListRM local = Schedule::convertRM(Schedule::processes);

        while (!local.empty())
        {
            temp.push_back(local.top());
            local.pop();
            total++;
           // cout<<"\nExecuting "<<temp[i].processname<<" expected time "<<temp[i].execution_time<<"sec......"<<endl;
            //Sleep(temp[i].execution_time*1000);
        }

        //function to set value to priority variable according to the asscending order of their period.
        int total_time = Schedule::set_priority(temp ,total);

        //function to compare the variables according to their arrival time
        ProcessListarrive local_arrive = Schedule::compare(Schedule::processes);

        //function to copy vector to new vector
        vector<Process> arrived = Schedule::copyto_vector(local_arrive);

        //function to find schedule for preempted tasks
         Schedule::RM_preemptive(total_time,arrived,total);
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

int Schedule::set_priority( vector <Process> temp,int total)
{
    int total_time_calculate=0;
    for(int j=0;j<total;j++)
    {
        temp[j].priority=j;
        total_time_calculate=total_time_calculate+temp[j].execution_time;
    }
    return total_time_calculate;
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

vector<Process> Schedule::copyto_vector(ProcessListarrive local_arrive)
{
    vector <Process> arrived;
    while (!local_arrive.empty())
    {
        arrived.push_back(local_arrive.top());
        local_arrive.pop();
    }
    return arrived;
}

void Schedule::RM_preemptive(int total_time,vector<Process> arrived,int total)
{
    int i=0,n;
    vector <Process> tempry(total);

    while(total_time!=0)
    {
        if(arrived[i].execution_time==0)
        {
            cout<<"\n .... "<<arrived[i].processname<<" has FINISHED......"<<endl;
            //arrived.erase(arrived.begin()+i);
            //arrived.pop_back();
            i++;
        }
        else if(arrived[i].execution_time>=1 & arrived[i].arrival_time == arrived[i+1].arrival_time)
        {
            if(arrived[i].priority < arrived[i+1].priority)
            {
                cout<<"\n Now Executing "<<arrived[i].processname<<i<<" time-remaining "<<arrived[i].execution_time<<"sec......"<<endl;
                Sleep(1000);
                arrived[i].execution_time=arrived[i].execution_time-1;
                arrived[i].arrival_time=arrived[i].arrival_time+1;
            }
             else
            {
                cout<<"\n"<<arrived[i].processname<<" has been preempted by task "<<arrived[i+1].processname<<endl;
                tempry[0]=arrived[i];
                arrived[i]=arrived[i+1];
                arrived[i+1]=tempry[0];
                Sleep(1000);
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
        snprintf(buffer, sizeof(buffer), "%d", count);
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
    n = no_process*(pow(2,1/no_process) - 1);

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
        cout<<temp.absolute_deadline<<endl;
    }

}

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

bool allScheduled(usProcessList localprocesslist)
{
    bool found = false;


    for(int i = 0; i < localprocesslist.size(); i++)
    {
        if (localprocesslist[i].execution_time != localprocesslist[i].executed)
        {
            found = true;
            break;
        }
    }

    return !found;
}

/*
 *      \class  Schedule
 *      \fnctn  Schedule :: runEDF()
 *      \brief  User given data of Processes for EDF scheduling is collected then evaluated if they are schedulable or not.
 *              The schedulable processes are executed one by one.
 */

void assignPriorities(usProcessList &processes)
{
    //We have the sorted process according to the deadline
    //And we have to save this structure.
    //So lets assign priority first
    for (int i = 0; i < sortedprocess.size(); i++)
    {
        sortedprocess[i].priority = i;
    }
}

usProcessList ProcessatT(usProcessList sortedprocess, int time)
{

    //Now we have to sort this vector according
    //to the arrival time.
    sort(sortedprocess.begin(), sortedprocess.end(), RMarrival);

    //Now we have to return the process which fall under the given time.
    usProcessList givenTime;
    for(int i = 0; i < sortedprocess.size(); i++)
    {
        if (sortedprocess[i].arrival_time == time)
        {
            givenTime.push_back(sortedprocess[i]);
        }
    }

    //We have the processes whose arrival time is given time

    //Sort them according to deadline
    sort(givenTime.begin(), givenTime.end(), ProcessCompare);

    return givenTime;
}
usProcessList getNotScheduled(usProcessList localprocesslist)
{
    for (int i = 0; i < localprocesslist.size(); i++)
    {
        if (localprocesslist[i].executed != localprocesslist[i].execution_time)
        {
            localprocesslist.erase(localprocesslist.begin()+5)
        }
    }

    return localprocesslist;
}

unsigned int find_next_process(usProcessList &localprocesslist, unsigned int time)
{
    usProcessList processatt;
    unsigned int index = priority = localprocesslist.size(); //Set to max priority

    for (int i = 0; i < localprocesslist.size(); i++)
    {
        if (localprocesslist[i].arrival_time == time)
        {
            processatt.push_back(localprocesslist[i]);
            if (localprocesslist[i].priority < priority)
            {
                priority = localprocesslist[i].priority;
                index = i;
            }
        }
    }

    Process toreturn = localprocesslist[i];
    localprocesslist.erase(localprocesslist.begin()+i);
    return toreturn;
}

void execute_onesec(Process &localprocess, unsigned int time)
{
    if (localprocess.executed == 0)
    {
        cout<<"Task "<< localprocess.id <<" started executing at T = " << time;
    }
    else
    {
        cout<<"Task "<< localprocess.id <<" resumed execution at T = " << time;
    }
    localprocess.executed++; //Increment stating, it has executed for 1 sec
}

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


    usProcessList localprocesslist = copyto_vector(Schedule::processes);
    Schedule::set_priority(localprocesslist);
    unsigned int process_no_executing, mainTime;
    Process next_process, current_process;

    //Sorted according to arrival time
    sort(tobescheduled.begin(), tobescheduled.end(), RMarrival);

    while(!allScheduled(localprocesslist))
    {
        //This is when second loop is running
        if (current_process.executed == current_process.execution_time) //it has been fully executed
        {
            //We find the next candidate
            next_process = Schedule::find_next_process(localprocesslist, mainTime);
        }

        //Check the lowest process
        next_process = Schedule::find_next_process(localprocesslist, mainTime);

        //We have the process to be executed. Execute it for 1 sec
        Schedule::execute_onesec(localprocesslist, next_process, mainTime);

        mainTime++;

        //Store our current process
        current_process = next_process;


        //Now one sec has passed. Deadlines have come closer.
        //We have sort again and assign priorities again. I will have to store the whole process somewhere.
    }
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


    Schedule::loadProcessFromFile("Sample.txt")


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
        for(int j=0;j<total;j++)
            {
                temp[j].priority=j;
            }
        //function to compare the processes according to their arrival time
        for(int m=0;m<total;m++)
        {
            for(int k=0;k<total;k++)
            {
                if(temp[k].arrival_time>temp[k+1].arrival_time)
                {
                    vector<Process> for_sort(2);
                    for_sort[1]=temp[k];
                    temp[k]=temp[k+1];
                    temp[k+1]=for_sort[1];
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

void Schedule::RM_preemptive(int total_time,vector<Process> arrived,int total)
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
        cout<<temp.absolute_deadline<<endl;
    }

}

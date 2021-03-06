/*
 *       \file       Schedule.cpp
 *
 *       \brief      Class definition for EDF Scheduling and RM Scheduling
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
#include "Schedule.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "MainBlock.h"


using namespace std;

/** \brief Constructor for initialize the no of processors in the system
 *         and give each one an ID
 */
Schedule::Schedule()
{
    processorlist.resize(noproccessor);

    //Assign Ids to each of the processor
    for (unsigned int i = 0; i < processorlist.size(); i++)
    {
        processorlist[i].id = i;
    }
}

Schedule::~Schedule()
{
    //dtor
}


usProcessList::iterator Schedule::find_next_process(usProcessList &localprocesslist, unsigned int time, int &nothing)
{
    usProcessList processatt;
    usProcessList::iterator it;
    unsigned int index, priority;

    index = priority = localprocesslist.size(); //Set to max priority

    for (unsigned int i = 0; i < localprocesslist.size(); i++)
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

/**
 *      \class  Schedule
 *      \fnctn  Schedule :: runEDF()
 *      \brief  User given data of Processes for EDF scheduling is collected then evaluated if they are schedulable or not.
 *              The schedulable processes are executed one by one.
 */

int Schedule::runEDF ()
{
    loadProcessFromFile("Sample.txt", "exetime.txt", "energy.txt");

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
        if (true /* next_process->isComplete() */)
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


}


/** \brief This functions removes the process from the localprocesslist which has completed its execution.
 *
 * \param toremove usProcessList::iterator The iterator pointing towards the process to remove
 * \param inthis usProcessList& The list of processes
 * \return void
 *
 */
void Schedule::removeTask(usProcessList::iterator toremove, usProcessList &inthis)
{
    inthis.erase(toremove);
}



/** \brief This functions just outputs the preemption on the screen for the user to understand
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

vector<string> extract_token(string line)
{
    stringstream sst(line);
    string varstring;
    vector<string> tokens;
    while(sst >> varstring)
    {
        tokens.push_back(varstring);
        varstring.clear();
    }

    return tokens;
}


/**
 *      \brief This functions loads the process from the file which is passed
 *             as a parameter to the functions. These parameters are written
 *             in the file delimited by space and one Process per line
 *      \param string filename The name of the file which contains the parameters
 */
void Schedule::loadProcessFromFile(string filename, string exefilename, string energyfilename)
{
    fstream file, exefile, energyfile;
    string line;
    file.open(filename.c_str());
    exefile.open(exefilename.c_str());
    energyfile.open(energyfilename.c_str());


    if (!file.is_open() || !exefile.is_open() || !energyfile.is_open())
    {
        cout<<"Could not find file. Please check";
        return;
    }

    int counter = 0;
    while(!file.eof())
    {
        string exeline, energyline;

        //Right Now we have 3 variables that needs to be fetched
        std::getline(file,line);
        std::getline(exefile, exeline);
        std::getline(energyfile, energyline);

        //Vectors to hold the tokens from the 3 files
        vector<string> tokens = extract_token(line);
        vector<string> exetokens = extract_token(exeline);
        vector<string> energytokens = extract_token(energyline);


        Process temp;
        temp.period = atoi(tokens[0].c_str());
        temp.absolute_deadline = atoi(tokens[1].c_str());
        temp.arrival_time = atoi(tokens[2].c_str());
        temp.id = counter;

        //Load the Execution Times
        for (unsigned i = 0; i < noproccessor; i++)
        {

            for (unsigned j = 0; j < processorlist[i].VoltageLevel.size(); j++)
            {
                //Insert value in the Process;
                ExecutionTime extemp;
                extemp.execution_time = atoi(exetokens[j].c_str());
                extemp.energyconsumed = atoi(energytokens[j].c_str());
                extemp.processor = processorlist.begin() + i;
                extemp.processid = counter;
                extemp.vlevel = processorlist[i].VoltageLevel.begin() + j;
                executetimes.push_back(extemp);
            }
        }
        //Add this to the list of the processes
        Schedule::processes.push(temp);


        //Reset the vector and the string
        tokens.erase(tokens.begin(), tokens.end());
        exetokens.erase(exetokens.begin(), exetokens.end());
        energytokens.erase(energytokens.begin(), energytokens.end());
        counter++;
    }
}


/**
 *      \class  Schedule
 *      \fnctn  Schedule :: rumRM()
 *      \brief  User will be asked to type the process data for RM scheduling through "collectprocess" function then,
 *              If the user given processes are schedulable i.e. if they satisfy the equation u<=n
 *              Then the processes will be scheduled and executed in a arranged sequence.
 */
int Schedule::lcm(usProcessList processes)
{
    int temp_gcd=0,temp_lcm=1;

    for(int i=0; i<processes.size(); i++)
    {
        temp_gcd=Schedule::GCD(temp_gcd,processes[i].period);
        //cout<<temp_gcd<<"\n";
        temp_lcm=temp_lcm*processes[i].period;
    }

    return temp_lcm/temp_gcd;
}
int Schedule::GCD(int a, int b)
{
    if (b==0) return a;
    return GCD(b,a%b);
}

int Schedule::runRM ()
{
    usProcessList temp;

    int total=0;
    int total_time;


    PrintTasks();


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
            for(int k=0; k<total-1; k++)
            {
                if(temp[k].arrival_time>temp[k+1].arrival_time)
                {
                    swap(temp[k], temp[k+1]);
                }
            }
//            total_time=total_time+temp[m].execution_time; //This needs a fix
        }
        //function to find schedule for preempted tasks
        Schedule::RM_preemptive(total_time,temp,total);
        int LCM=Schedule::lcm(temp);
        cout<<LCM;
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
        if(true/* arrived[i].execution_time==0 */)
        {
            cout<<"\n .... "<<arrived[i].processname<<" has FINISHED...at T = "<<total_time<<endl;
            Sleep(1000);
            i++;
            cout<<"\n\n ..........STARTED "<<arrived[i].processname<<" at T = "<<total_time<<endl;
            //arrived.erase(arrived.begin()+i);
            //arrived.pop_back();

        }
        else if(true /* arrived[i].execution_time>=1 & arrived[i].arrival_time == arrived[i+1].arrival_time */)
        {
            if(arrived[i].priority < arrived[i+1].priority)
            {
                Sleep(1000);
                //cout<<"\n Still Executing "<<arrived[i].processname<<" time-remaining "<<arrived[i].execution_time<<"sec......"<<endl;
                Sleep(1000);
//                arrived[i].execution_time=arrived[i].execution_time-1;
                arrived[i].arrival_time=arrived[i].arrival_time+1;
                // i++;
                //i++;
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
//                arrived[i].execution_time=arrived[i].execution_time-1;
                arrived[i].arrival_time=arrived[i].arrival_time+1;

            }
            total_time=total_time-1;
        }
        else
        {
//            cout<<"\n Executing "<<arrived[i].processname<<" time-remaining "<<arrived[i].execution_time<<"sec......"<<endl;
            Sleep(1000);
//            arrived[i].execution_time=arrived[i].execution_time-1;
            arrived[i].arrival_time=arrived[i].arrival_time+1;
            total_time=total_time-1;
        }
    }
    cout<<"\n****************ALL the processes has been FINISHED**************** "<<endl;
}

/**
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

    return 0;

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
//        total_util = (float) temp_process.execution_time/temp_process.period;
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
//        total_util = (float) temp_process.execution_time/temp_process.period;
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

    Process temp;

    while(!local.empty())
    {
        temp = local.top();
        local.pop();

        //We have whole lots of information to show of the processes
        cout<<"=== Task " << temp.id << "===" << endl;
        cout<<"Arrival Time\t\t\t\t\t: " << temp.arrival_time << endl;
        cout<<"Absolute Deadline\t\t\t\t\t: " << temp.absolute_deadline << endl;
        cout<<"Period\t\t\t\t\t: " << temp.period << endl;

        //Now show the execution time, voltage
        ExecutionTimeList etimes = getExecutionTime(executetimes, temp.id);

        for(unsigned int i = 0; i < etimes.size(); i++)
        {
            cout << "Execution Time at Voltage Level " << *etimes[i].vlevel << " of Processor "
                 << (*etimes[i].processor).id << " is " << etimes[i].execution_time
                 << " and Energy Consumed is " << etimes[i].energyconsumed << endl;
        }
    }

}

void Schedule::BranchBound ()
{
    loadProcessFromFile("Sample.txt", "exetime.txt", "energy.txt");

    //Lets first process the tasks to be executed
    usProcessList tasklist = copyto_vector(processes);

    //Lets start the loop start finding the processor on which it is to be allocated
    for (unsigned int i = 0; i < tasklist.size(); i++)
    {
        bool overload;

        //Role of allocator starts from here, return the least energy row, if processor is available
        ExecutionTime least_exe_time = alloc.least_energy_row(executetimes, tasklist[i], TaskProcessorMap, overload, false, executetimes[0].processor);

        //This is when there is not enough processors for the tasks available
        if (overload)
        {
            cout<< "There are not enough processors for task set\n";
            overload = false;
            continue;
        }

        //map the above process to the processor and save it.
        Process result = alloc.prepare_process(least_exe_time, tasklist[i]);

        //Map the process with the processor
        ProcessorAllocation result_mapped;
        result_mapped.processor = least_exe_time.processor;
        result_mapped.task = result;

        cout<<"Process "<< result.id << " was allocated to processor " << (*result_mapped.processor).id << endl;

        //And oh, don't forget to push it to the main variable
        TaskProcessorMap.push_back(result_mapped);

        //Now repeat the similar procedure for the backup
        ExecutionTime least_exe_time_backup = alloc.least_energy_row(executetimes, tasklist[i], TaskProcessorMap, overload, true, result_mapped.processor);

        if (overload)
        {
            //We don't have any space for the back
            cout << "We don't have any processor for backup of task " << tasklist[i].id << endl;
            overload = false;
            continue;
        }

        result = alloc.prepare_process(least_exe_time_backup, tasklist[i]);

        //Let them know that this is a backup task
        result.is_backup = true;

        //Lets use the same variable as above
        result_mapped.processor = least_exe_time_backup.processor;
        result_mapped.task = result;

        cout<<"Process "<< result.id << " 's backup was allocated to processor " << (*result_mapped.processor).id << endl;

        //And oh, don't forget to push it to the main variable
        TaskProcessorMap.push_back(result_mapped);


    }
}

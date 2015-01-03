#ifndef MAINBLOCK_H
#define MAINBLOCK_H

#include<iostream>
#include<vector>
#include<queue>
#include<string>

struct ProcessorAllocation;
typedef std::vector<ProcessorAllocation> TaskMap;

class Processor
{
    public:
        /** Default constructor */
        Processor();

        int id;

        std::vector<float> VoltageLevel;

        //Add a function to calculate the utilization of processor
        float calculateUtil(TaskMap);
        TaskMap filter_by_processor(TaskMap, int);

        bool operator==(Processor);
    protected:
    private:
};

typedef std::vector<Processor> ProcessorList;


//The Process Class

class Process
{
public:
    std::string processname;
    int execution_time;
    int energyconsumed;
    int executed;
    int is_periodic;
    int period;
    int priority;
    int period_completed;
    int arrival_time;
    int relative_deadline;
    int absolute_deadline;
    int id;
    Process();
    void set_period(int);
    void user_period();
    void collectdata();
    void set_name(std::string);
    bool operator == (Process);
    bool isComplete();

protected:
private:
};


struct ProcessCompare
{
    bool operator()(const Process &p1, const Process &p2) const
    {
        int p1_deadline = p1.absolute_deadline;
        int p2_deadline = p2.absolute_deadline;
        return p1_deadline > p2_deadline;
    }
};

struct RMCompare
{
    bool operator()(const Process &p1, const Process &p2) const
    {
        int p1_period = p1.period;
        int p2_period = p2.period;
        return p1_period > p2_period;
    }
};

struct RMarrival
{
    bool operator()(const Process &p1, const Process &p2) const
    {
        int p1_arrival_time = p1.arrival_time;
        int p2_arrival_time = p2.arrival_time;
        return p1_arrival_time > p2_arrival_time;
    }
};


typedef std::priority_queue<Process, std::vector<Process>, ProcessCompare> ProcessList;
typedef std::priority_queue<Process, std::vector<Process>, RMCompare> ProcessListRM;
typedef std::priority_queue<Process, std::vector<Process>, RMarrival> ProcessListarrive;
typedef std::vector<Process> usProcessList;



struct RMUtil
{
    float n;
    float total_util;
    bool feasible;
};

struct ExecutionTime
{
    ProcessorList::iterator processor;
    std::vector<float>::iterator vlevel;
    int execution_time;
    int energyconsumed;
    int processid;
};
typedef std::vector<ExecutionTime> ExecutionTimeList;

ExecutionTime getExecutionTime(ExecutionTimeList executetimes, int processid, ProcessorList::iterator processor, std::vector<float>::iterator vlevel)
{
    bool found = false;
    int index;

    //Search for the process in the ExecutionTimelist
    for (int i = 0; i < executetimes.size(); i++)
    {
        if (executetimes[i].processid = processid && processor == executetimes[i].processor
                                        && vlevel == executetimes[i].vlevel)
        {
            found = true;
            index = i;
        }
    }

    if (found)
    {
        return executetimes[index];
    }
    else
    {
        std::cout<<"We have a serious problem. We could not find the asked process";
    }
}

ExecutionTimeList getExecutionTime(ExecutionTimeList executetimes, int processid, ProcessorList::iterator processor)
{
    ExecutionTimeList etime;

    //Search for the process in the ExecutionTimelist
    for (int i = 0; i < executetimes.size(); i++)
    {
        if (executetimes[i].processid = processid && processor == executetimes[i].processor)
        {
            etime.push_back(executetimes[i]);
        }
    }

    return etime;
}

ExecutionTimeList getExecutionTime(ExecutionTimeList executetimes, int processid)
{
    ExecutionTimeList etime;

    //Search for the process in the ExecutionTimeList
    for (int i = 0; i < executetimes.size(); i++)
    {
        if (executetimes[i].processid == processid)
        {
            etime.push_back(executetimes[i]);
        }
    }

    return etime;
}

struct ProcessorAllocation
{
    Process task;
    ProcessorList::iterator processor;
};

#endif // MAINBLOCK_H

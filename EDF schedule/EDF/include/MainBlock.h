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
    bool is_backup;
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
ExecutionTime getExecutionTime(ExecutionTimeList, int processid, ProcessorList::iterator processor, std::vector<float>::iterator vlevel);
ExecutionTimeList getExecutionTime(ExecutionTimeList, int processid, ProcessorList::iterator processor);
ExecutionTimeList getExecutionTime(ExecutionTimeList, int processid);

struct ProcessorAllocation
{
    Process task;
    ProcessorList::iterator processor;
};

TaskMap filter_by_processor(TaskMap, int);

float calculate_processorutil(TaskMap, ProcessorList::iterator);
#endif // MAINBLOCK_H

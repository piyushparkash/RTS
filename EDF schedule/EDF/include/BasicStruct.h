#ifndef BASICSTRUCT_H_INCLUDED
#define BASICSTRUCT_H_INCLUDED

#include <vector>
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

struct ProcessorAllocation
{
    Process task;
    ProcessorList::iterator processor;
};

typedef std::vector<ExecutionTime> ExecutionTimeList;
#endif // BASICSTRUCT_H_INCLUDED

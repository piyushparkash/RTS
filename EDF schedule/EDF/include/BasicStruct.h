#ifndef BASICSTRUCT_H_INCLUDED
#define BASICSTRUCT_H_INCLUDED

struct RMUtil
{
    float n;
    float total_util;
    bool feasible;
};

struct ExecutionTime
{
    ProcessorList::iterator processor;
    int execution_time;
    int eneryconsumed;
    int processid;
};

typedef std::vector<ExecutionTime> ExecutionTimeList;
#endif // BASICSTRUCT_H_INCLUDED

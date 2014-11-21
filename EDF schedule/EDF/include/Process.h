#ifndef PROCESS_H
#define PROCESS_H
#include<string>

#include"Processor.h"
struct ExecutionTime
{
    ProcessorList::iterator processor;
    int execution_time;
    int eneryconsumed;
};

class Process
{
public:
    std::string processname;
    ExecutionTime execution_time;
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
    ExecutionTime processor(ProcessorList::iterator);

protected:
private:
};

#endif // PROCESS_H

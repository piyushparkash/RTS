#ifndef PROCESS_H
#define PROCESS_H
#include<string>

class Process
{
public:
    std::string processname;
    int execution_time;
    int executed;
    int is_periodic;
    int period;
    int priority;
    int period_completed;
    int arrival_time;
    int relative_deadline;
    int absolute_deadline;

    Process();
    virtual ~Process();
    void set_period(int);
    void user_period();
    void collectdata();
    void set_name(std::string);
protected:
private:
};

#endif // PROCESS_H

#ifndef SCHEDULE_H
#define SCHEDULE_H
#include "Process.h"
#include <vector>
#include <queue>


class ProcessCompare
{
/*    ProcessCompare(Process a, Process b)
    {
        if (a.absolute_deadline < b.absolute_deadline)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
*/

    bool operator()(const Process a, const Process b)
    {
        if (a.absolute_deadline < b.absolute_deadline)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

typedef std::priority_queue<Process> ProcessList;

class Schedule
{
    public:
        Schedule();
        virtual ~Schedule();

        // Variable to store all the process classes
        ProcessList processes;

        void getProcess();
        int run();
        int collectProcess();
    protected:
    private:
};
#endif // SCHEDULE_H

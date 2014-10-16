#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>
#include <queue>

#include "Process.h"
#include "ProcessQueue.h"

class Schedule
{
    public:
        Schedule();
        virtual ~Schedule();

        // Variable to store all the process classes
        ProcessList processes;

        void getProcess();
        int runEDF();
        int runRM();
        int collectProcess();
        void PrintTasks();
        bool is_EDFSchedulable();
        bool is_RMSchedulable();
        ProcessListRM convertRM(ProcessList);
    protected:
    private:
};
#endif // SCHEDULE_H

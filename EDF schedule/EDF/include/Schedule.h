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
        int collectProcess();
        void PrintTasks();
        bool is_EDFSchedulable();
    protected:
    private:
};
#endif // SCHEDULE_H

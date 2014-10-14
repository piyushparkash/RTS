
#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>
#include <queue>

#include "rm_process.h"
#include "processQue_rm.h"

class rm_schedule
{
    public:
        rm_schedule();
        virtual ~rm_schedule();

        // Variable to store all the process classes
        ProcessList processes;

        void get_task();
        int runRM();
        int collect_task();
        void Print_taskData();
        bool is_RMschedulable();
    protected:
    private:
};
#endif // SCHEDULE_H

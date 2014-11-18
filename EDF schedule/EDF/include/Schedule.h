#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>
#include <queue>

#include "Process.h"
#include "ProcessQueue.h"
#include "BasicStruct.h"

/*
 *      \class  Schedule
 *      \brief  All the processes for EDF scheduling are stored in a local variable named "local".
                It will prioritize the processes according to their deadline time.
 *              The "local.top()" will return the topmost process from the priority queue "local".
 *              This topmost process is stored in "temp" variable of "process" type.
 *              That process will be removed from the queue so as to get next topmost process.
 *              Now the process is executed after deletion from queue by calling "temp.processname".
 */
class Schedule
{
    public:
        Schedule();
        virtual ~Schedule();

        // Variable to store all the process classes
        ProcessList processes;

        void loadProcessFromFile(std::string);
        void getProcess();
        bool allScheduled(usProcessList);
        usProcessList getNotScheduled(usProcessList);
        usProcessList::iterator find_next_process(usProcessList&, unsigned int, int&);
        void execute_onesec(usProcessList::iterator, unsigned int);

        int runEDF();
        int runRM();
        int lcm(usProcessList);
        int GCD(int,int);
        int collectProcess();
        void PrintTasks();
        bool is_EDFSchedulable();
        void set_priority(usProcessList&);
        usProcessList copyto_vector(ProcessList);
        void RM_preemptive(int,usProcessList,int);
        RMUtil is_RMSchedulable();
        ProcessListRM convertRM(ProcessList);
        ProcessListarrive compare(ProcessList);
        void preempt_process(usProcessList::iterator, usProcessList::iterator, unsigned int);
        void removeTask(usProcessList::iterator, usProcessList&);
        bool idle;

    protected:
    private:
};
#endif // SCHEDULE_H

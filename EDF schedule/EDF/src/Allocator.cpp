#include "Allocator.h"

Allocator::Allocator()
{
    //ctor
}

Allocator::~Allocator()
{
    //dtor
}


ExecutionTime Allocator::least_energy_row(ExecutionTimeList executetimes, Process task, TaskMap TaskProcessorMap)
{
    //First thing would be to filter our according to the process
    ExecutionTimeList executetimes_task = getExecutionTime(executetimes, task.id);
    ExecutionTime best_result;

    //We have the execution times, choose the best one with least energy
    int bestone = -1;
    int bestenergy;
    while(true)
    {
        for (unsigned int i = 0; i < executetimes_task.size(); i++)
        {
            if (bestone == -1)
            {
                bestone = i;
                bestenergy = executetimes_task[i].energyconsumed;
            }
            else if (executetimes_task[i].energyconsumed < bestenergy)
            {
                bestone = i;
                bestenergy = executetimes_task[i].energyconsumed;
            }
        }

        //Calculate the utilization value of task
        int task_util = executetimes_task[bestone].execution_time/task.period;
        int processor_util = (*executetimes_task[bestone].processor).calculateUtil(TaskProcessorMap);
        if (task_util + processor_util > 1)
        {
            executetimes_task.erase(executetimes_task.begin()+bestone);
            bestone = -1;
        }
        else
        {
            best_result = executetimes_task[bestone];
        }
    }
    return best_result;

}

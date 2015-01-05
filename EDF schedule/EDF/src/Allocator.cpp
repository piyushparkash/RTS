#include "Allocator.h"
using namespace std;
Allocator::Allocator()
{
    //ctor
}

Allocator::~Allocator()
{
    //dtor
}


ExecutionTime Allocator::least_energy_row(ExecutionTimeList executetimes, Process task, TaskMap TaskProcessorMap, bool &overload)
{
    //Get the Execution Time of the given task Process
    ExecutionTimeList executetimes_task = getExecutionTime(executetimes, task.id);

    //The picked execution time which is best suited
    ExecutionTime best_result;

    //We have the execution times, choose the best one with least energy
    int bestone = -1;
    int bestenergy;
    while(true)
    {

        //When we don't have execution time and energy consumed for the processor
        if (executetimes_task.size() == 0)
        {
            overload = true;
            break;
        }


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
        float task_util = (float)executetimes_task[bestone].execution_time/task.period;
        int processor_util = calculate_processorutil(TaskProcessorMap, executetimes_task[bestone].processor);
        if ((task_util + processor_util) > 1)
        {
            executetimes_task.erase(executetimes_task.begin()+bestone);
            bestone = -1;
        }
        else
        {
            best_result = executetimes_task[bestone];
            break;
        }
    }
    return best_result;

}

Process Allocator::prepare_process(ExecutionTime process_ex, Process final_process)
{
    Process result = final_process;

    //Assign the energy and the execution time
    result.energyconsumed = process_ex.energyconsumed;
    result.execution_time = process_ex.execution_time;

    return result;
}

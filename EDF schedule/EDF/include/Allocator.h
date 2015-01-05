#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "MainBlock.h"


class Allocator
{
    public:
        /** Default constructor */
        Allocator();
        /** Default destructor */
        virtual ~Allocator();

        ExecutionTime least_energy_row(ExecutionTimeList, Process, TaskMap, bool&);
        Process prepare_process(ExecutionTime, Process);
    protected:
    private:
};

#endif // ALLOCATOR_H

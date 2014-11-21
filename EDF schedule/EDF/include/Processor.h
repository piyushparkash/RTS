#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "ProcessQueue.h"

class Processor
{
    public:
        /** Default constructor */
        Processor();

        usProcessList tasks;
        vector<int> VoltageLevel;
    protected:
    private:
};

typedef vector<Processor> ProcessorList;
#endif // PROCESSOR_H

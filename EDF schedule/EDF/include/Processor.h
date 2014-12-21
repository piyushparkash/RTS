#ifndef PROCESSOR_H
#define PROCESSOR_H
#include<vector>
#include<queue>

#include "Process.h"

class Processor
{
    public:
        /** Default constructor */
        Processor();

        int id;

        std::vector<float> VoltageLevel;
    protected:
    private:
};

typedef std::vector<Processor> ProcessorList;
#endif // PROCESSOR_H

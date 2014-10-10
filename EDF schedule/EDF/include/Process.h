#ifndef PROCESS_H
#define PROCESS_H


class Process
{
    public:
        int execution_time;
        bool is_periodic;
        int period;
        int relative_deadline;
        int absolute_deadline;

        Process();
        virtual ~Process();
        bool set_period(int);
    protected:
    private:
};

#endif // PROCESS_H

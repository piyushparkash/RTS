#ifndef PROCESS_H
#define PROCESS_H


class Process
{
public:
    int execution_time;
    int is_periodic;
    int period;
    int relative_deadline;
    int absolute_deadline;

    Process();
    virtual ~Process();
    void set_period(int);
    void user_period();
    void collectdata();
protected:
private:
};

#endif // PROCESS_H

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

    bool operator< (Process b)
    {
        if (this->absolute_deadline < b.absolute_deadline)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    Process();
    virtual ~Process();
    void set_period(int);
    void user_period();
protected:
private:
};

#endif // PROCESS_H

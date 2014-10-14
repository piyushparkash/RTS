
#ifndef PROCESS_H
#define PROCESS_H
#include<string>

class rm_process
{
public:
    std::string processname;
    int ex_time;
    int is_periodic;
    int p_time;
    int relative_deadline;
    int absolute_deadline;

    rm_process();
    virtual ~rm_process();
    void set_period(int);
    void user_period();
    void collectdata();
    void set_name(std::string);
protected:
private:
};

#endif // PROCESS_H

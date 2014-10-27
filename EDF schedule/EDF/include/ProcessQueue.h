// *** ADDED BY HEADER FIXUP ***
#include <queue>
#include <vector>
// *** END ***
#include<vector>
#include<queue>
struct ProcessCompare
{
    bool operator()(const Process &p1, const Process &p2) const
    {
        int p1_deadline = p1.absolute_deadline;
        int p2_deadline = p2.absolute_deadline;
        return p1_deadline > p2_deadline;
    }
};

struct RMCompare
{
    bool operator()(const Process &p1, const Process &p2) const
    {
        int p1_period = p1.period;
        int p2_period = p2.period;
        return p1_period > p2_period;
    }
};

struct RMarrival
{
    bool operator()(const Process &p1, const Process &p2) const
    {
        int p1_arrival_time = p1.arrival_time;
        int p2_arrival_time = p2.arrival_time;
        return p1_arrival_time > p2_arrival_time;
    }
};

typedef std::priority_queue<Process, std::vector<Process>, ProcessCompare> ProcessList;
typedef std::priority_queue<Process, std::vector<Process>, RMCompare> ProcessListRM;
typedef std::priority_queue<Process, std::vector<Process>, RMarrival> ProcessListarrive;
typedef std::vector<Process> usProcessList;

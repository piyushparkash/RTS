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

typedef std::priority_queue<Process, std::vector<Process>, ProcessCompare> ProcessList;


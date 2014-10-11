#include <iostream>
#include <cmath>
#include <windows.h>
#include "get_taskdata.h"
using namespace std;
int main()
{
    long int process;

//get total number of processes
    cout <<"How many total processes";
    cin>>process;
    get_taskdata *obj=new get_taskdata(process);

return 0;
}

#include <iostream>
#include "include/Schedule.h"

using namespace std;

int main()
{
    int choice;
    cout<<"choose the algo to proceed \n 1.) EDF scheduling algo \n 2.) RM scheduling algo\n";
    cin>>choice;
    if(choice<1 || choice>2)
    {
       cout<<"invalid digit !! try again\n";
       cout<<"choose the algo to proceed \n 1.) EDF scheduling algo \n 2.) RM scheduling algo\n";
       cin>>choice;
    }
    Schedule sch;
    switch(choice)
    {
       case(1):
       sch.runEDF();
       break;
       case(2):
       sch.runRM();
    }
}

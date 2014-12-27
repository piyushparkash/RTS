
/*
 *       \file       main.cc
 *
 *       \brief      Creation of objects and Calling functions on the basis of user choice.
 *
 *       \compiler   g++\n
 *
 *       \author     Piyush Prakash, achyutapiyush@gmail.com
 *       \license    GNU General Public License Version 2
 *       \copyright  Copyright (c) 2014, B&B Developers
 *                   jashnmalhi@yahoo.in
 */

#include <iostream>
#include "include/Schedule.h"

using namespace std;

int main()
{
    Schedule sch;
    int choice;
    cout<<"choose the algo to proceed \n 1.) EDF scheduling algo \n 2.) RM scheduling algo\n"
            << " 3.) Branch And Bound\n";
    cin>>choice;

    /*
     * user is asked to type a number(either 1 or 2) to make a choice for EDF or RM scheduling.
     */

    if(choice < 1 || choice > 3)

    {
        cout<<"invalid digit !! try again\n";
        cout<<"choose the algo to proceed \n 1.) EDF scheduling algo \n 2.) RM scheduling algo\n"
            << " 3.) Branch And Bound\n";
        cin>>choice;
    }
    /*
     * If user pressed 1 EDF scheduling will be done to the processes
     *              If user pressed 2 RM scheduling will be done to the processes.
     */

    switch(choice)
    {
    case(1):
        sch.runEDF();
        break;
    case(2):
        sch.runRM();
        break;
    case (3):
        sch.BranchBound();
        break;
    default:
        cout<<"Please select a correct option";
    }
}

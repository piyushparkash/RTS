#include <iostream>
#include <cmath>
using namespace std;
int main()
{
     long int select,process,a_temp;
//get total number of processes
     cout <<"How many total processes";
     cin>>process;

     float p_time[process],ex_time[process],n,uti=0,process_f,response[process];
     process_f=process;
     int prior[process],prior_temp[process];
//get the C and T of all processes
     for(int i=0;i<process;i++)
     {
        cout<<"\ncompletion Time or execution time of process"<<i+1<<": ";
        cin>>ex_time[i];
        cout<<"\nperiod of process"<<i+1<<": ";
        cin>>p_time[i];
     }
//copy the period of all processes in another variable to get priority
     for(int k=0;k<process;k++)
        {
            prior_temp[k]=p_time[k];
        }
//sort the period to set priority
     for(int k=0;k<process-1;k++)
        {
            for(int j=0;j<process-1;j++)
                {
                    if(prior_temp[j]>prior_temp[j+1])
                        {
                                a_temp=prior_temp[j];
                                //cout<<a_temp<<"  "<<j<<"--a\t";
                                prior_temp[j]=prior_temp[j+1];
                                //cout<<prior_temp[j]<<"--prio j\t";
                                prior_temp[j+1]=a_temp;
                                //cout<<prior_temp[j+1]<<"--prio j+1\t";
                        }
                }
         }
//match the priority to original processes
    for(int k=0;k<process;k++)
        {
            for(int j=0;j<process;j++)
                 {
                      if(p_time[k]== prior_temp[j])
                          {
                              prior[k]=j+1;
                          }
                 }
        }
//print the table
     cout<<"\nprocess \t ex-time \t period \t priority \t response time \n";
     for(int j=0;j<process;j++)
     {
        cout<<"p"<<j<<" \t\t "<<ex_time[j]<<" \t\t "<<p_time[j]<<" \t\t "<<prior[j]<<" \t\t "<<"\n";
     }
    cout<<"\n";
// get the utilization bound for condition u<=n*(2^(1/n) -1)
    for(int a=0;a<process;a++)
    {
       uti=uti+(ex_time[a]/p_time[a]);
    }
    process_f=process;
    n=process*(pow(2.0,1/process_f)-1);
//if utilization condition satisfied print the algo choice
    if(uti<=n)
    {
        cout<<"the tasks are scheduleable !! utilization="<<uti<<"\n";
//ask for the scheduling algo
        cout <<"choose 1 algo"<<"\n1. RM scheduling"<<"\n2. EDF scheduling \n";
        cin>>select;
//if choice invalid
        if(select<1 || select>2)
        {
             cout<<"invalid digit !! try again";
             cout <<"choose 1 algo"<<"\n1. RM scheduling"<<"\n2. EDF scheduling \n";
        cin>>select;
        }
        cout<<"\n";
// switch to the chosen algo
        switch(select)
        {
    // RM algo logic
            case 1:  cout<<"RM scheduling algo\n";
           /* for(int k=0;k<process;k++)
            {
                if(prior_temp[k]==1)
                {
                    response[k]=ex_time[k]
                }
                else
                {
                    for(int y=0;response_temp[y]!=response_temp[y+1];y++)
                    {
                        response_temp[y]=response[k-1]+
                    }
                }
            } */
            break;
    //EDF algo logic
            case 2:  cout<<"EDF scheduling algo";
            break;
    //default choice
            default:  cout<<"no selection";
            break;
        }
    }
// if the condition is not satisfied end the execution
    else
    {
        cout<<"failed to schedule the tasks !! utilization="<<uti<<" n="<<n<<"\n";
    }



}

#include <iostream>
using namespace std;
int main()
{
     int select,process,a_temp;
     float n,uti=0;
     //get total number of processes
     cout <<"How many total processes";
     cin>>process;

     int p_time[process],ex_time[process],prior[process],prior_temp[process];
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
     for(int k=0;k<process;k++)
        {
            for(int j=0;j<process;j++)
                {
                    if(prior_temp[j]>prior_temp[j+1])
                        {
                                a_temp=prior_temp[j];
                                prior_temp[j]=prior_temp[j+1];
                                prior_temp[j+1]=a_temp;
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
     // get the utilization bound for condition u<=n*(2^(1/n) -1)
    cout<<"\n";
    for(int a=0;a<process;a++)
    {
        uti=uti+(ex_time[a]/p_time[a]);
    }

    n=process*((2^(1/process))-1);
    cout<<uti <<"\t"<< n<<"\n";
    if(uti<=n)
    {
        cout<<"the tasks are scheduleable !! utilization="<<uti<<"\n";
    }
    else
    {
        cout<<"failed to schedule the tasks !! utilization="<<uti<<" n="<<n<<"\n";
    }

/*
    cout <<"choose 1 algo"<<"\n1. RM scheduling"<<"\n2. EDF scheduling \n";
    cin>>select;
    if(select<1 || select>2)
    {
         cout<<"invalid digit !! try again";
         cout <<"choose 1 algo"<<"\n1. RM scheduling"<<"\n2. EDF scheduling \n";
    cin>>select;
    }
cout<<"\n";
    switch(select)
    {
        case 1:  cout<<"RM scheduling algo\n";


        break;
        case 2:  cout<<"EDF scheduling algo";
        break;
        default:  cout<<"no selection";
        break;
    }
*/
}

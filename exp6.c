#include <stdio.h>

#define MAX 10
#define QUANTUM 3

struct process
{
    int pid, at, bt, pr;
    int ct, tat, wt;
};

int main()
{
    struct process p[MAX];
    int n, i, j, time;
    float avg_fcfs=0, avg_sjf=0, avg_pr=0, avg_rr=0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i=0;i<n;i++)
    {
        printf("\nPID AT BT PR: ");
        scanf("%d%d%d%d",&p[i].pid,&p[i].at,&p[i].bt,&p[i].pr);
    }

    printf("\nFCFS\n----------------------------\n");
    printf("PID AT BT PR CT TAT WT\n----------------------------\n");

    time = 0;

    for(i=0;i<n;i++)
    {
        if(time < p[i].at)
            time = p[i].at;

        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        avg_fcfs += p[i].wt;
        time = p[i].ct;

        printf("%d   %d  %d  %d  %d  %d   %d\n",
               p[i].pid,p[i].at,p[i].bt,p[i].pr,
               p[i].ct,p[i].tat,p[i].wt);
    }

    avg_fcfs = avg_fcfs/n;

    printf("\nSJF\n----------------------------\n");
    printf("PID AT BT PR CT TAT WT\n----------------------------\n");

    int completed[MAX]={0};
    int done=0;
    time=0;

    while(done<n)
    {
        int min=9999, index=-1;

        for(i=0;i<n;i++)
        {
            if(p[i].at<=time && completed[i]==0)
            {
                if(p[i].bt < min)
                {
                    min=p[i].bt;
                    index=i;
                }
            }
        }

        if(index==-1)
        {
            time++;
        }
        else
        {
            p[index].ct=time+p[index].bt;
            p[index].tat=p[index].ct-p[index].at;
            p[index].wt=p[index].tat-p[index].bt;

            avg_sjf+=p[index].wt;
            time=p[index].ct;
            completed[index]=1;
            done++;
        }
    }

    for(i=0;i<n;i++)
        printf("%d   %d  %d  %d  %d  %d   %d\n",
               p[i].pid,p[i].at,p[i].bt,p[i].pr,
               p[i].ct,p[i].tat,p[i].wt);

    avg_sjf=avg_sjf/n;

    printf("\nPriority\n----------------------------\n");
    printf("PID AT BT PR CT TAT WT\n----------------------------\n");

    for(i=0;i<n;i++)
        completed[i]=0;

    done=0;
    time=0;

    while(done<n)
    {
        int max=-1, index=-1;

        for(i=0;i<n;i++)
        {
            if(p[i].at<=time && completed[i]==0)
            {
                if(p[i].pr > max)
                {
                    max=p[i].pr;
                    index=i;
                }
            }
        }

        if(index==-1)
        {
            time++;
        }
        else
        {
            p[index].ct=time+p[index].bt;
            p[index].tat=p[index].ct-p[index].at;
            p[index].wt=p[index].tat-p[index].bt;

            avg_pr+=p[index].wt;
            time=p[index].ct;
            completed[index]=1;
            done++;
        }
    }

    for(i=0;i<n;i++)
        printf("%d   %d  %d  %d  %d  %d   %d\n",
               p[i].pid,p[i].at,p[i].bt,p[i].pr,
               p[i].ct,p[i].tat,p[i].wt);

    avg_pr=avg_pr/n;

    printf("\nRound Robin\n----------------------------\n");
    printf("PID AT BT PR CT TAT WT\n----------------------------\n");

    int rem[MAX];
    for(i=0;i<n;i++)
        rem[i]=p[i].bt;

    int remain=n;
    time=0;

    while(remain>0)
    {
        for(i=0;i<n;i++)
        {
            if(rem[i]>0 && p[i].at<=time)
            {
                if(rem[i]>QUANTUM)
                {
                    time+=QUANTUM;
                    rem[i]-=QUANTUM;
                }
                else
                {
                    time+=rem[i];
                    p[i].ct=time;
                    p[i].tat=p[i].ct-p[i].at;
                    p[i].wt=p[i].tat-p[i].bt;

                    avg_rr+=p[i].wt;
                    rem[i]=0;
                    remain--;
                }
            }
        }
    }

    for(i=0;i<n;i++)
        printf("%d   %d  %d  %d  %d  %d   %d\n",
               p[i].pid,p[i].at,p[i].bt,p[i].pr,
               p[i].ct,p[i].tat,p[i].wt);

    avg_rr=avg_rr/n;

    printf("\nAverage Waiting Time\n----------------------------\n");
    printf("FCFS: %.2f\n",avg_fcfs);
    printf("SJF: %.2f\n",avg_sjf);
    printf("Priority: %.2f\n",avg_pr);
    printf("RR: %.2f\n",avg_rr);

    float min=avg_fcfs;
    char name[20]="FCFS";

    if(avg_sjf<min){ min=avg_sjf; sprintf(name,"SJF"); }
    if(avg_pr<min){ min=avg_pr; sprintf(name,"Priority"); }
    if(avg_rr<min){ min=avg_rr; sprintf(name,"RR"); }

    printf("\nMinimum Average Waiting Time: %s (%.2f)\n",name,min);

    return 0;
}

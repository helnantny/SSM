#include<stdio.h>
void main()
{
int n,i,j,ct=0;
double avgwait=0,avgtat=0;
printf("enter no. of processes:");
scanf("%d",&n);
int pID[n],bTime[n],wTime[n],tTime[n],prio[n];
int btime[n],wtime[n],tattime[n];
printf("enter the burst time and priority of the processes\n");
for(i=0;i<n;i++)
{
pID[i]=i+1;
printf("p%d burst time:",(i+1));
scanf("%d%d",&btime[i],&prio[i]);
}
int temp;
for(i=0;i<n-1;i++)
{
for(j=i+1;j<n;j++)
{
if(prio[i]>prio[j])
{ temp=bTime[i];
bTime[i]=bTime[j];
bTime[j]=temp;
temp=prio[i];
prio[i]=prio[j];
prio[j]=temp;
temp=pID[i];
pID[i]=pID[j];
pID[j]=temp;
}}}
wtime[0]=0;
for(i=1;i<n;i++)
{
wtime[i]=wtime[i-1]+btime[i-1];
avgwait=avgwait+wtime[i];
}
avgwait=avgwait/n;
for(i=0;i<n;i++)
{
tattime[i]=wtime[i]+btime[i];
avgtat=avgtat+tattime[i];
}
avgtat=avgtat/n;
printf("PID\tBT\tWT\tTAT\n");
for(i=0;i<n;i++)
{
printf("P%d\t%d\t%d\t%d\n",i+1,btime[i],wtime[i],tattime[i]);
}
printf("\n");
printf("average waiting time:%.2f\nAverage Turn Around Time:%.2f\n",avgwait,avgtat);
printf("\n");
printf("ghant chart\n");
for(i=0;i<n;i++)
{
printf("--------------");
}
printf("\n| ");
for(i=0;i<n;i++)
{
printf("p%d |",i+1);
}
printf("\n");
for(i=0;i<n;i++)
{
printf("-------");
}
printf("\n0\t");
for(i=0;i<n;i++)
{
ct=ct+btime[i];
printf("%d\t",ct);
}
printf("\n");
}

#include<stdio.h>
int head,a[20],i,distance,n,seektime=0;
int main(){
printf("\nenter head position:");
scanf("%d",&head);
printf("\nenter number of disk requests:");
scanf("%d",&n);
printf("\nenter disk requests:");
for(i=0;i<=n;i++){
scanf("%d",&a[i]);
}
a[0]=head;
printf("\n\tFCFS DISK SCHEDULING\n\n");
for(i=0;i<n;i++)
{
distance=(a[i]>a[i+1])?a[i]-a[i+1]:a[i+1]-a[i];
printf("head movement from %d to %d:%d\n",a[i],a[i+1],distance);
seektime=seektime+distance;
}
printf("\ntotal seek time is:%d\n",seektime);}



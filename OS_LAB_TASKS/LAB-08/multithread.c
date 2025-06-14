#include<stdio.h>
#include<stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 7
#define NUM_THREADS 3
int arr[ARRAY_SIZE];
int avg;
int min,max;
void *avgarr(void *arg)
{
int sum=0;
for(int i=0;i<ARRAY_SIZE;i++)
{
sum += arr[i];
}
avg =(int)sum/ARRAY_SIZE;
pthread_exit(0);
}
void *minarr(void *arg)
{
min=arr[0];
for(int i=1;i<ARRAY_SIZE;i++)
{
if(arr[i] < min)
{
min = arr[i];
}
}
pthread_exit(0);
}
void *maxarr(void *arg)
{
max=arr[0];
for(int i=1;i<ARRAY_SIZE;i++)
{
if(arr[i] > max)
{
max = arr[i];
}
}
pthread_exit(0);
}
int main(int argc, char *argv[])
{
if(argc!=8)
{
printf("Usage: %s <arrayelements>", argv[0]);
return 1;
}
for(int i=0;i<7;i++)
{
arr[i]=atoi(argv[i+1]);
}
pthread_t workers[3];
pthread_create(&workers[0], NULL, avgarr, NULL);
pthread_create(&workers[1], NULL, minarr, NULL);
pthread_create(&workers[2], NULL, maxarr, NULL);
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(workers[i], NULL);
    }

    printf("Average: %d\n", avg);
    printf("Min: %d\n", min);
    printf("Max: %d\n", max);
return 0;
}

 

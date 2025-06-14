#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define NUM_THREADS 5

int shared_data = 0;
pthread_mutex_t mutex;
void *func1(void *arg)
{
    int _id = *((int *) arg);
    pthread_mutex_lock(&mutex);
    shared_data++;
    pthread_mutex_unlock(&mutex);
    return NULL;
}
int main()
{
    pthread_t tids[NUM_THREADS];
    int thread_args[NUM_THREADS];
    pthread_mutex_init(&mutex,NULL);

    for(int i=0;i<NUM_THREADS;i++)
    {
        thread_args[i] = i;
        pthread_create(&tids[i],NULL,func1,&thread_args[i]);
    }
    for(int i=0;i<NUM_THREADS;i++)
    {
        pthread_join(tids[i],NULL);
    }
    printf("The shared data is: %d\n",shared_data);
    pthread_mutex_destroy(&mutex);

    return 0;
}

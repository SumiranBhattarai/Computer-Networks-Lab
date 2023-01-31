#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int max = 100;
volatile int count = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;
void *printEven(void *arg)
{
    printf("Entering Even Function: ");
    while (count < max)
    {
        pthread_mutex_lock(&mutex);
        while (count % 2 == 0)
        {
            pthread_cond_wait(&cond, &mutex);
        }
        printf("\n%d", count++);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
    }
    printf("Exiting Even Function: ");
    pthread_exit(0);
}
void *printOdd(void *arg)
{
    printf("Entering Odd Function: ");
    while (count < max)
    {
        pthread_mutex_lock(&mutex);
        while (count % 2 != 0)
        {
            pthread_cond_wait(&cond, &mutex);
        }
        printf("\n%d", count++);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
    }
    printf("Exiting Odd Function: ");
    pthread_exit(0);
}
void main()
{
    pthread_t t1, t2;
    pthread_mutex_init(&mutex, 0);
    pthread_mutex_init(&cond, 0);
    pthread_create(&t1, 0, printEven, 0);
    pthread_create(&t1, 0, printOdd, 0);
    pthread_join(t1, 0);
    pthread_join(t2, 0);
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&cond);
}
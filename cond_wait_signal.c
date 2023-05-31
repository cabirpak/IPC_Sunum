//reference: https://aticleworld.com/print-even-and-odd-numbers-using-two-threads-using-mutex-in-c/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int MAX = 100;
volatile int countOdd = 0;
volatile int countEven = 1;
pthread_mutex_t mutex;
pthread_cond_t cond;
void *printEvenNum(void *arg)
{
    printf("evn basladi\n");
    while(countEven < MAX)
    {
        pthread_mutex_lock(&mutex);
        
        pthread_cond_wait(&cond, &mutex);
        printf("%d ", countEven);
        countEven+=2;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(0);
}
void *printOddNum(void *arg)
{
    printf("odd basladi\n");
    while(countOdd < MAX)
    {
        pthread_mutex_lock(&mutex);
        
        pthread_cond_signal(&cond);
        printf("%d ", countOdd);
        countOdd+=2;
        pthread_cond_wait(&cond, &mutex);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(0);
}
int main()
{
    pthread_t thread1;
    pthread_t thread2;
    pthread_mutex_init(&mutex, 0);
    pthread_cond_init(&cond, 0);
    pthread_create(&thread1, 0, &printEvenNum, NULL);
    pthread_create(&thread2, 0, &printOddNum, NULL);
    pthread_join(thread1, 0);
    pthread_join(thread2, 0);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return  0;
}

//ref: https://aticleworld.com/print-even-and-odd-numbers-using-two-threads-using-mutex-in-c/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int MAX = 100;
int count = 0;
void *printEvenNum(void *arg)
{
    while(count < MAX)
    {
        if(count % 2 == 0)
        {
            printf("%d ", count++);
        }
    }
    pthread_exit(0);
}
void *printOddNum(void *arg)
{
 
    while(count < MAX)
    {
        if(count % 2 == 1)
        {
            printf("%d ", count++);
        }
    }
    pthread_exit(0);
}
int main()
{
    pthread_t t1;
    pthread_t t2;
    pthread_create(&t1, 0, &printEvenNum, NULL);
    pthread_create(&t2, 0, &printOddNum, NULL);
    pthread_join(t1, 0);
    pthread_join(t2, 0);
    return  0;
}

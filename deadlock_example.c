#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
pthread_mutex_t mutex1, mutex2;

void *job1(){
    printf("Job1 going to try to lock mutex1\n");
    pthread_mutex_lock(&mutex1);
    printf("Job1 locked the mutex1\n");
    sleep(1);
    printf("Job1 going to try to lock mutex2\n");
    pthread_mutex_lock(&mutex2); 
    printf("Job1 locked the mutex2, going to unlock it\n");
    pthread_mutex_unlock(&mutex2);
    printf("Job1 going to unlock the mutex1\n");
    pthread_mutex_unlock(&mutex1);
    pthread_exit(NULL);
}

void *job2(){
    printf("Job2 going to try to lock mutex2\n");
    pthread_mutex_lock(&mutex2);
    printf("Job2 locked the mutex2\n");
    sleep(1);
    printf("Job2 going to try to lock mutex1\n");
    pthread_mutex_lock(&mutex1); 
    printf("Job2 locked the mutex1, going to unlock it\n");
    pthread_mutex_unlock(&mutex1);
    printf("Job1 going to unlock the mutex2\n");
    pthread_mutex_unlock(&mutex2);
    pthread_exit(NULL);
}

int main() {
    pthread_mutex_init(&mutex1,NULL);
    pthread_mutex_init(&mutex2,NULL);

    pthread_t t1,t2;
    pthread_create(&t1,NULL,job1,NULL);
    pthread_create(&t2,NULL,job2,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    return 0;

}


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


int main()
{
    
    pthread_mutex_t m;
    pthread_mutex_init(&m, 0);
    
    int pid = fork();
    if(pid == 0) {
        printf("ana process\n");
        pthread_mutex_lock(&m);
        printf("ana process sleep oncesinde...\n");
        sleep(3);
        printf("ana process sleep sonrasinda...\n");
        pthread_mutex_unlock(&m);
    } else {
        printf("yeni process\n");
        pthread_mutex_lock(&m);
        printf("yeni process sleep oncesinde...\n");
        sleep(3);
        printf("yeni process sleep sonrasinda...\n");
        pthread_mutex_unlock(&m);
    }

    return 0;
}

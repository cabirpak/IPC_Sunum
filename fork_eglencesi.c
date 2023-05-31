
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


int main()
{
    
    pthread_mutex_t m;
    pthread_mutex_init(&m, 0);
    
    int pid = fork();
    if(pid != 0) {
        printf("ana process %d\n", pid);
        pthread_mutex_lock(&m);
        printf("do main job...\n");
        printf("ana process sleep oncesinde...\n");
        sleep(3);
        printf("ana process sleep sonrasinda...\n");
        pthread_mutex_unlock(&m);
        
        
        int pid = fork();
        
        if(pid != 0) {
            printf("ana process2 %d\n", pid);
            pthread_mutex_lock(&m);
            printf("do main job...2\n");
            printf("ana process sleep oncesinde...2\n");
            sleep(3);
            printf("ana process sleep sonrasinda...2\n");
            pthread_mutex_unlock(&m);
        } else {
            printf("yeni process2\n");
            pthread_mutex_lock(&m);
            printf("yeni process sleep oncesinde...2\n");
            sleep(3);
            printf("yeni process sleep sonrasinda...2\n");
            pthread_mutex_unlock(&m);
        }
    
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

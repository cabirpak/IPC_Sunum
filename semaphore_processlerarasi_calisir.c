
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>          /* O_CREAT, O_EXEC          */
#include <errno.h>          /* errno, ECHILD            */
#include <sys/wait.h>
//https://stackoverflow.com/questions/16400820/how-to-use-posix-semaphores-on-forked-processes-in-c

int main()
{
    
    sem_t *sem;
    sem = sem_open ("pSem", O_CREAT | O_EXCL, 0644, 1); 
    
    int pid = fork();
    if(pid != 0) {
        printf("ana process\n");
        printf("semwait: %d\n", sem_wait(sem));
        printf("ana process sleep oncesinde...\n");
        sleep(3);
        printf("ana process sleep sonrasinda...\n");
        sem_post(sem);
    } else {
        printf("yeni process\n");
        printf("semwait: %d\n", sem_wait(sem));
        printf("yeni process sleep oncesinde...\n");
        sleep(3);
        printf("yeni process sleep sonrasinda...\n");
        sem_post(sem);
    }
    
    if (pid != 0){
        /* wait for all children to exit */
        while (pid = waitpid (-1, NULL, 0)){
            if (errno == ECHILD)
                break;
        }

        printf ("\nParent: All children have exited.\n");

        /* cleanup semaphores */
        sem_unlink ("pSem");   
        sem_close(sem);  
        /* unlink prevents the semaphore existing forever */
        /* if a crash occurs during the execution         */
        //exit (0);
    }

    return 0;
}

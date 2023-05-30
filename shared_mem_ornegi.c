
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>          /* O_CREAT, O_EXEC          */
#include <errno.h>          /* errno, ECHILD            */
#include <sys/wait.h>
#include <sys/shm.h>        /* shmat(), IPC_RMID        */

//https://stackoverflow.com/questions/16400820/how-to-use-posix-semaphores-on-forked-processes-in-c

int main()
{
    
    sem_t *sem;
    sem = sem_open ("pSem", O_CREAT | O_EXCL, 0644, 1);
    
    key_t shmkey;                 /*      shared memory key       */
    int shmid;                    /*      shared memory id        */
    int *p;                       /*      shared variable         *//*shared */
    
    
    
    
    /* initialize a shared variable in shared memory */
    shmkey = ftok ("/dev/null", 5);       /* valid directory name and a number */
    printf ("shmkey for p = %d\n", shmkey);
    shmid = shmget (shmkey, sizeof (int), 0644 | IPC_CREAT);
    if (shmid < 0){                           /* shared memory error check */
        perror ("shmget\n");
        exit (1);
    }

/*p burada aloke ediliyor. eger malloc kullanilirsa, cocuk process'le ana process 
farkli adreslerini gorur. shmat kullanilirsa ikisi ayni heap adresini gorur. */
    p = (int *) shmat (shmid, NULL, 0);   /* attach p to shared memory */
    //p = (int *) malloc(sizeof(int));
    *p = 0;
    printf ("p=%d is allocated in shared memory.\n\n", *p);
    
    
    
    
    int pid = fork();
    if(pid != 0) {
        printf("ana process\n");
        printf("semwait: %d\n", sem_wait(sem));
        printf("ana process sleep oncesinde...\n");
        *p = 1234;
        sleep(3);
        printf("ana process sleep sonrasinda...\n");
        sem_post(sem);
    } else {
        printf("yeni process\n");
        printf("semwait: %d\n", sem_wait(sem));
        printf("yeni process sleep oncesinde...\n");
        sleep(3);
        printf("shared memory contents: %d\n", *p);
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

        /* shared memory detach */
        shmdt (p);
        shmctl (shmid, IPC_RMID, 0);
        
        
        /* cleanup semaphores */
        sem_unlink ("pSem");   
        sem_close(sem);  
        /* unlink prevents the semaphore existing forever */
        /* if a crash occurs during the execution         */
        //exit (0);
    }

    return 0;
}

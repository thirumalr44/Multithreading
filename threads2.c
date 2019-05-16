/* Thirumala Reddy Potlapati
   U55049337
   
   As we observe the time used and system time used for mutex locks and semaphore solutions for 2 threads.
   The time used is same and system time is slightly more for semaphore.
   When the system time is seen, semaphore has taken more than 100,000 usec and mutex locks has taken
   more than 10,000 usec but less than 100,000 usec.
   I think the reason for more system time is that semaphore is kind of a signaling mechanism for the threads, it needs to increment
   and decrement a variable so that mutual exclusion works. Hence it takes more system time as to perform test and perform
   decrement/increment.
   Mutex is just a lock which keeps other threads from accessing the critical section while a thread is using critical section.
   It is kind of test and set, slightly faster than semaphore.
   
*/

#define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <semaphore.h> /* semaphore header file */
#include <sys/time.h>
#include <sys/resource.h>

struct rusage mytiming;
struct timeval mytimeval;

sem_t sem; /* variable where semaphore value is stored */

struct shared_dat
   {
   int value;     /* shared variable to store result*/
   };

struct shared_dat  *counter;
int temp = 0;

/****************************************************************
* This function increases the value of shared variable "counter"
  by one 2500000 times
****************************************************************/
void * thread1(void *arg)
{
	int line = 0;	
	while (line < 2500000)
	{
		line++;
			sem_wait(&sem); /* locking the semaphore */
			
/* Critical Section */
		if(line%100==0)
		{
			counter->value = counter->value + 100;
	     temp++;
		}

		    sem_post(&sem); /* unlocking the semaphore */
		  
           }
	   printf("from process1 counter  =  %d\n", counter->value); 
	   printf("thread1 incremented counter by 100 for %d times\n", temp);
return(NULL);
}


/****************************************************************
This function increases the value of shared variable "counter"
by one 2500000 times
****************************************************************/
void * thread2(void *arg)
{
	int line = 0;	
	while (line < 2500000)
	   {
            line++;

			sem_wait(&sem); /* locking the semaphore */
			
/* Critical Section */
	    counter->value = counter->value + 1;
	    
		    sem_post(&sem); /* unlocking the semaphore */
		
           }
	   printf("from process2 counter = %d\n", counter->value); 
return(NULL);
}

/****************************************************************
This function increases the value of shared variable "counter"
by one 2500000 times
****************************************************************/
void * thread3(void *arg)
{
	int line = 0;	
	while (line < 2500000)
	   {
            line++;

			sem_wait(&sem); /* locking the semaphore */
			
/* Critical Section */
	    counter->value = counter->value + 1;

            sem_post(&sem); /* unlocking the semaphore */
	    
           }
	   printf("from process3 counter = %d\n", counter->value); 
return(NULL);
}


/****************************************************************
*                  Main Body                                    *
****************************************************************/
main()
{
        int             r=0;
	int 		i;
	int 		shmid;	  /* shared memory ID */
        pthread_t	tid1[1];     /* process id for thread 1 */
        pthread_t	tid2[1];     /* process id for thread 2 */
		pthread_t   tid3[1];     /* process id for thread 3 */
        pthread_attr_t	attr[1];     /* attribute pointer array */

         counter = (struct shared_dat *) malloc(sizeof(struct shared_dat));

	/* initialize shared memory to 0 */
	counter->value = 0 ;
           printf("1 - I am here %d in pid %d\n",r,getpid());
    
	fflush(stdout);
 /* Required to schedule thread independently.
 Otherwise use NULL in place of attr. */
        pthread_attr_init(&attr[0]);
        pthread_attr_setscope(&attr[0], PTHREAD_SCOPE_SYSTEM);  /* system-wide contention */ 

	/* end to schedule thread independently */

	sem_init(&sem,0,1);    /* semaphore initialization */
	
/* Create the threads */
        int t1 = pthread_create(&tid1[0], &attr[0], thread1, NULL);
        int t2 = pthread_create(&tid2[0], &attr[0], thread2, NULL);
		int t3 = pthread_create(&tid3[0], &attr[0], thread3, NULL);
		
		if(t1)
		{printf("thread1 creation failed and return = %d", t1);}
	
	    if(t2)
		{printf("thread1 creation failed and return = %d", t2);}
	
	    if(t3)
		{printf("thread1 creation failed and return = %d", t3);}

/* Wait for the threads to finish */
    pthread_join(tid1[0], NULL);
    pthread_join(tid2[0], NULL);
	pthread_join(tid3[0], NULL);
	        printf("from parent counter  =  %d\n", counter->value);
		printf("---------------------------------------------------------------------------\n");
		printf("\t\t	End of simulation\n");

/*Using getrusage we are measuring the time*/
	getrusage(RUSAGE_SELF, &mytiming);

	printf("Time used is sec: %d, usec %d\n",mytiming.ru_utime.tv_sec,

	mytiming.ru_utime.tv_usec);

	printf("System Time used is sec: %d, usec %d\n",mytiming.ru_stime.tv_sec,

	mytiming.ru_stime.tv_usec);
		
		exit(0);
		
}


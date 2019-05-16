/*Thirumala Reddy Potlapati
  U55049337
*/

#define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/resource.h>

struct rusage mytiming;
struct timeval mytimeval;

struct shared_dat
   {
   int value;     /* shared variable to store result*/
   };

struct shared_dat  *counter;
int temp =0;

        /*mutex locks initialization*/
		pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
		//pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

/****************************************************************
* This function increases the value of shared variable "counter"
  by one 2500000 times
****************************************************************/
void * thread1(void *arg)
{	
			
      
	int line = 0;	
	while (line < 2500000)
	   { line++;
    pthread_mutex_lock( &mutex );        
/* Critical Section */
/*Mutex locks are applied for critical section */    
		if(line%100==0)
		{counter->value = counter->value + 100;
	     temp++;
		 //line = line+100;
		}
		
pthread_mutex_unlock( &mutex );    
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
	   {line++;
pthread_mutex_lock( &mutex );
   

/* Critical Section */
/*Mutex locks are applied for critical section */

	    counter->value = counter->value + 1;
	pthread_mutex_unlock( &mutex );    
           }
	
	   printf("from process2 counter = %d\n", counter->value); 
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

/* Create the threads */
        
		int t1 = pthread_create(&tid1[0], &attr[0], thread1, NULL);
        int t2 = pthread_create(&tid2[0], &attr[0], thread2, NULL);
		
		if(t1)
		{printf("thread1 creation failed and return = %d", t1);}
	
	    if(t2)
        {printf("thread2 creation failed and return = %d", t2);} 			

/* Wait for the threads to finish */
    pthread_join(tid1[0], NULL);
    pthread_join(tid2[0], NULL);
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


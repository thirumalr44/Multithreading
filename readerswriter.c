/*

  Thirumala Reddy Potlapati
  U55049337

*/


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <semaphore.h> 

sem_t readers_sem;
sem_t writer_sem;

int numOfReaders;
int readers_count=0;
int temp1 =0;
int flag=0;
int counter_value=0;



void relaxandspendtime()
        {
       int i;
      for(i = 0; i < 250000000; i++) i=i;
      }

/****************************************************************
* Readers thread function
****************************************************************/
void * readers_thread(void *arg)
{  if(flag == 1)
	{printf("ERROR--Writer is using the critical section.\n");}
	else { 
		sem_wait(&readers_sem); 
		readers_count++;
		if(readers_count==1)
		{sem_wait(&writer_sem);}
        sem_post(&readers_sem);
		
		relaxandspendtime();
		sem_wait(&readers_sem);
		readers_count--;
		if(readers_count==0)
		{sem_post(&writer_sem);}
		
        sem_post(&readers_sem);
		temp1++;
		printf("Reader %d work is done.\n", temp1);
           }

}


/****************************************************************
Writer thread function increases the value of shared variable "counter"
by one 25000 times
****************************************************************/
void * writer_thread(void *arg)
{    
		
	for(int line=0; line<25000; line++)
	   {
        sem_wait(&writer_sem); 
      /* Critical Section */
	  flag = 1; /* Flag is set after entering Critical Section*/

	    
          counter_value++; 
		  
       flag = 0; /* Flag will be reset after completion of work in Critical Section */
	     sem_post(&writer_sem);      
		}
		
				  
	   printf("Writer thread counter = %d.\n", counter_value); 
	   printf("Writer work is done.\n");
	   

}


/****************************************************************
*                  Main Body                                    *
****************************************************************/
int main(int argc, char *argv[])
{
      
	long int i;
	int k;
	int temp2 [numOfReaders+1];
	
	numOfReaders = atoi(argv[1]);
       /* Input through command line */
	   if(argc < 2)
	   {printf("Enter the number between 1 to 14");
        exit(0);
	   }
       
	    pthread_t	readers[14];     /* process id for readers thread */
        pthread_t	writer[1];     /* process id for writer thread */
        pthread_attr_t	attr[1];     /* attribute pointer array */
        
         
 /* Required to schedule thread independently.
 Otherwise use NULL in place of attr. */
        pthread_attr_init(&attr[0]);
        pthread_attr_setscope(&attr[0], PTHREAD_SCOPE_SYSTEM);  /* system-wide contention */ 

	/* end to schedule thread independently */
	
/* Semaphores initialization */	

        sem_init(&readers_sem, 0, 1);
		sem_init(&writer_sem, 0, 1);

/* Create the threads */
      k = (int)(numOfReaders/2);
      for(i = 0; i < k; i++){
       temp2[i] = pthread_create(&readers[i], &attr[0], readers_thread, (void*) i);
	   if(temp2[i])
	   {printf(" Reader Thread %d creation failed.\n", i);}
	  }
	  
/* Create the writer thread */
        temp2[numOfReaders] =   pthread_create(&writer[0], &attr[0], writer_thread, NULL);
        if(temp2[numOfReaders])
		{printf(" Writer Thread creation failed.\n");}
      
	  for(i = k ; i < numOfReaders ; i++) {
         temp2[i] = pthread_create(&readers[i], &attr[0], readers_thread, (void*) i);
	    if(temp2[i])
	   {printf(" Reader Thread %d creation failed.\n", i);}
	  }
	  
/* Wait for the threads to finish */
/* Joining the threads */	  
        for(i = 0; i < numOfReaders ; i++)
		{
			pthread_join(readers[i], NULL);
		}
		pthread_join(writer[0], NULL);	

printf("---------------------------------------------------------------------------\n");
		printf("\t\t	End of simulation.\n");		
		
		return 0;
}


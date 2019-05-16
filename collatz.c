//Thirumala Reddy Potlapati
//U55049337



#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(int argc, char *argv[])
{
int n1,n2;
pid_t pid1,pid2;
n1 = atoi(argv[1]);
for(;;)
{
if(n1>0 && n1<40)
{
    n2=n1+3;
    pid1=fork();
 if(pid1==0)
    {
       printf("From Child 1 init n=%d, ", n1);
       while (n1>1)
       {
        if(n1%2==0)
            {n1=n1/2;}
        else
            {n1=3*n1+1;}
        printf("From Child 1 n=%d, ", n1);
       }
    }
    else
    {
        wait(&pid1);
exit(0);
        return 0;
    }
    printf("\n");
    pid2=fork();
 if(pid2==0)
    {
       printf("From Child 2 init n=%d, ", n2);
       while (n2>1)
       {
        if(n2%2==0)
            {n2=n2/2;}
        else
            {n2=3*n2+1;}
        printf("From Child 2 n=%d, ", n2);
       }
    }
    else
    {
        wait(&pid2);
        return 0;
    }
    printf("\nChildren Complete\n");
    exit(0);
    break;
exit(0);
}
else
{
    printf("enter the number between 0 and 40\n");
    scanf("%d", &n1);
}
}
return 0;
}

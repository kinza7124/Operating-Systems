#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
printf("Original process (Before Fork) - PID: %d\n",getpid());
pid_t f;
f= fork();
if(f<0)
{
printf("error");
exit(1);
}
else if(f==0)
{
printf("Child process: PID %d , Parent process: PID %d\n",getpid(),getppid());
}		
else 
{
printf("Parent process: PID %d, Child process: PID %d\n",getpid(),f);	
wait(NULL);
}
return 0;
}

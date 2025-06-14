#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
pid_t f;
f= fork();
if(f<0)
{
printf("error");
exit(1);
}
else if(f==0)
{
printf("Child process: PID %d - Listing directory contents\n",getpid());
execlp("ls", "ls", "-l", NULL);
perror("execlp failed");
exit(1);
}		
else 
{	
wait(NULL);
}
return 0;
}

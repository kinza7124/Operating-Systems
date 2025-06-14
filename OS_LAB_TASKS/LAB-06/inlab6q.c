#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
void numseparate(int num, int pipefd[3][2]) {
int i = 0;
int digits[3];
while (num>0 && i<3) {
digits[i] = num % 10;
num /= 10;
i++;
}

for (int j = 0;j<i;j++) {
write(pipefd[j][1],&digits[j], sizeof(int));

close(pipefd[j][1]);
}
}
int main() {
int num;
printf("Enter a Number(Max 3 digits):");
scanf("%d",&num);
int pipefd[3][2];
for (int i = 0;i<3; i++) {
if (pipe(pipefd[i]) == -1) {
perror("Pipe failed.");
return 1;
}
}
pid_t p1 = fork();
if (p1>0) {
wait(NULL);
int product = 1, digit;
for (int i = 0;i<3; i++) {
close(pipefd[i][1]);
if (read(pipefd[i][0],&digit, sizeof(int))> 0) {
product *= digit;
}
close(pipefd[i][0]);
}
printf("Product of digits: %d\n", product);
}
else if (p1 == 0) {
numseparate(num, pipefd);
exit(0);
}
else {
printf("Fork failed\n");
return 1;
}
}

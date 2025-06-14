#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    pid_t pid;
    char *output_file = "who_output.txt";
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } 
    else if (pid == 0) {
        int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("Error opening file");
            exit(1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);

        printf("Child Process (PID: %d) - Executing 'who' command...\n", getpid());

        execlp("who", "who", NULL);
        perror("execlp failed");
        exit(1);
    } 
    else { 
     printf("Parent Process (PID: %d) - Waiting for child to finish...\n", getpid());
     wait(NULL); 
     printf("Parent Process - Output has been successfully stored in '%s'.\n", output_file);
    }

    return 0;
}


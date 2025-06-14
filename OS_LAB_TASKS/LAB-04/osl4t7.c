#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BUFFER_SIZE 1024
int main(int argc, char *argv[]) {
    if (argc != 2) { 
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(1);
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(1);
    }
    pid_t pid = fork();
    if (pid < 0) { 
        perror("Fork failed");
        close(fd);
        exit(1);
    } 
    else if (pid == 0) { 
        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;
        printf("Child Process (PID: %d) - Displaying file contents:\n\n", getpid());

        while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
            write(STDOUT_FILENO, buffer, bytes_read);
        }
        if (bytes_read == -1) {
            perror("Error reading file");
            close(fd);
            exit(1);
        }
        printf("\n\nChild Process - File display completed.\n");
        close(fd);
        exit(0);
    } 
    else { 
        printf("Parent Process (PID: %d) - Waiting for child to finish...\n", getpid());
        wait(NULL);
        printf("Parent Process - File reading completed.\n");
        close(fd);
    }
    return 0;
}


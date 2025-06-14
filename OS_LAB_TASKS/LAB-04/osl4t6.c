#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
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
        char ch;
        int line_count = 0;
        ssize_t bytes_read;

        printf("Child Process (PID: %d) - Counting lines...\n", getpid());
        while ((bytes_read = read(fd, &ch, 1)) > 0) {
            if (ch == '\n')
                line_count++;
        }

        if (bytes_read == -1) {
            perror("Error reading file");
            close(fd);
            exit(1);
        }
        printf("Child Process - Total lines: %d\n", line_count);
        close(fd);
        exit(0);
    } 
    else { 
        printf("Parent Process (PID: %d) - Waiting for child process...\n", getpid());
        wait(NULL);
        printf("Parent Process - Line counting completed.\n");
        close(fd);
    }
	return 0;
}


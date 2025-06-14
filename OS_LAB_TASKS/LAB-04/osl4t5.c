#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BUFFER_SIZE 1024
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <backup_file>\n", argv[0]);
        exit(1);
    }
    int src_fd, dest_fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;
    src_fd = open(argv[1], O_RDONLY);
    if (src_fd == -1) {
        perror("Error opening source file");
        exit(1);
    }
    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("Error opening backup file");
        close(src_fd);
        exit(1);
    }
    pid_t pid = fork(); 
    if (pid < 0) { 
        perror("Fork failed");
        close(src_fd);
        close(dest_fd);
        exit(1);
    } 
    else if (pid == 0) { 
        printf("Child Process (PID: %d) - Copying file...\n", getpid());

        while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
            bytes_written = write(dest_fd, buffer, bytes_read);
            if (bytes_written == -1) {
                perror("Error writing to backup file");
                close(src_fd);
                close(dest_fd);
                exit(1);
            }
        }
        if (bytes_read == -1) {
            perror("Error reading source file");
        }
        printf("Child Process - Backup completed successfully.\n");
        close(src_fd);
        close(dest_fd);
        exit(0);
    } 
    else {
        printf("Parent Process (PID: %d) - Waiting for backup to complete...\n", getpid());
        wait(NULL); 
        printf("Parent Process - Backup process completed.\n");
        close(src_fd);
        close(dest_fd);
    }

    return 0;
}



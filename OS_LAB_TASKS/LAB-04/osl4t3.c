#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 1024
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
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
        perror("Error opening destination file");
        close(src_fd);
        exit(1);
    }
    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written == -1) {
            perror("Error writing to destination file");
            close(src_fd);
            close(dest_fd);
            exit(1);
        }
    }

    if (bytes_read == -1) {
        perror("Error reading source file");
    }

    close(src_fd);
    close(dest_fd);

    printf("File copied successfully from '%s' to '%s'\n", argv[1], argv[2]);
    return 0;
}



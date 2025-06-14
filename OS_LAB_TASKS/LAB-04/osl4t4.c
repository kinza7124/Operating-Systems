#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
void list_directory(const char *dir_path, int depth) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char full_path[1024];
    if ((dir = opendir(dir_path)) == NULL) {
        perror("Error opening directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
       snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        if (stat(full_path, &file_stat) == -1) {
            perror("Error getting file stats");
            continue;
        }

        for (int i = 0; i < depth; i++)
            printf("  ");

        if (S_ISDIR(file_stat.st_mode)) {
            printf("[DIR]  %s\n", entry->d_name);
            list_directory(full_path, depth + 1);
        } else {
            printf("[FILE] %s\n", entry->d_name);
        }
    }
    closedir(dir);
}
int main(int argc, char *argv[]) {
    const char *start_dir = (argc == 2) ? argv[1] : "."; 
    printf("Listing contents of directory: %s\n", start_dir);
    list_directory(start_dir, 0);
    return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>    
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>

void change_directory(char *path) {    
    if (path == NULL || strcmp(path, "~") == 0) {
        path = getenv("HOME");
    }
    if (chdir(path) == -1) {
        perror("chgdir");  
    } else {
        printf("Changed directory to %s\n", path);
    }
}

int main(int argc, char* argv[]) {
    char* path = (char*)malloc(sizeof(char) * 100);
    char* option = (char*)malloc(sizeof(char) * 100);

    if (argc < 2) {
        printf("Usage: chgdir <directory_path> or <option>\n");
        free(path);
        free(option);
        return 1;
    }

    if (argc == 2) {
        change_directory(NULL); // No path specified, go to home directory
    } else {
        strcpy(path, argv[2]);
        change_directory(path);
    }
    
    free(path);
    free(option);
    return 0;
}

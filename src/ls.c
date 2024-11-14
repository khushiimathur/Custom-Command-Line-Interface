
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {

    char* path = (char*)malloc(sizeof(char) * 100);
    char* option = (char*)malloc(sizeof(char) * 100);

    if (argc == 1) {
        strcpy(path, ".");
        strcpy(option, "");
    }
    else if (argc == 2) {
        strcpy(path, argv[1]);
        strcpy(option, "");
    }
    else {
        strcpy(path, argv[1]);
        strcpy(option, argv[2]);
    }


    struct dirent** fileListTemp;
    int noOfFiles;

    noOfFiles = scandir(path, &fileListTemp, NULL, alphasort);

    if (noOfFiles < 0) {
        printf( "Error: No such file or directory\n");
        return 0;
    }

    if (strcmp(option, "-a") == 0) {
        for (int i = 0; i < noOfFiles; i++) {
            printf("%s\t", fileListTemp[i]->d_name);
        }
    }
    else if (strcmp(option, "-A") == 0) {
        for (int i = 2; i < noOfFiles; i++) {
            printf("%s\t", fileListTemp[i]->d_name);
        }
    }
    else {
        for (int i = 0; i < noOfFiles; i++) {
            if (fileListTemp[i]->d_name[0] != '.') {
                printf("%s\t", fileListTemp[i]->d_name);
            }
        }
    }

    printf("\n");

    free(path);
    free(option);
    free(fileListTemp);
}
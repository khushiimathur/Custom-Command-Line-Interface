
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define NUM_WORDS 10            // Max number of word in the input  
#define WORD_LEN 100            // Max number of letters in a word of input

int main(int argc, char* argv[]) {
    
    if (argc == 1 || argc == 2) {
        printf("Error:missing operand\n");
        return 0;
    }

    char* option = (char*)malloc(sizeof(char) * WORD_LEN);
    char* _paths[NUM_WORDS];
    char* paths[NUM_WORDS];
    int optionChanged = 0;
    int pathIndex = 0;

    for (int i = 0; i < NUM_WORDS; i++) {
        _paths[i] = (char*)malloc(sizeof(char) * WORD_LEN);
        _paths[i][0] = '\0';

        paths[i] = (char*)malloc(sizeof(char) * WORD_LEN);
        paths[i][0] = '\0';
    }
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0) {
            optionChanged = 1;
            strcpy(option, "-v");
        }
        else if (strcmp(argv[i], "-p") == 0) {
            optionChanged = 1;
            strcpy(option, "-p");
        }
        else {
            strcpy(_paths[pathIndex], argv[i]);
            pathIndex += 1;
        }
    }

    if (pathIndex == 0) {
        printf("Error:missing operand\n");
        return 0;
    }
    else {
        for (int i = 0; i < NUM_WORDS && _paths[i][0] != '\0'; i++) {
            if (_paths[i][0] == '/' || _paths[i][0] == '~') {
                strcpy(paths[i], _paths[i]);
            }
            else {
                strcpy(paths[i], argv[1]);
                strcat(paths[i], "/");
                strcat(paths[i], _paths[i]);
            }
        }
    }

    if (optionChanged == 0) {
        strcpy(option, "");
    }

    for (int i = 0; i < NUM_WORDS && paths[i][0] != '\0'; i++) {
        if (mkdir(paths[i], 0777) == 0) {
            if (strcmp(option, "-v") == 0) {
                printf("Created directory '%s'\n", paths[i]);
            }
        }
        else {
            if (strcmp(option, "-p")) {
                printf("Error:Unable to create the directory %s\n", paths[i]);
            }
        }
    }
    return 0;
}
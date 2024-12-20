#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_WORDS 10              
#define WORD_LEN 100            

int main(int argc, char* argv[]) {
    // Formatting input
    if (argc == 1 || argc == 2) {
        printf("Error:missing operand");
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
        if (strcmp(argv[i], "-i") == 0) {
            optionChanged = 1;
            strcpy(option, "-i");
        }
        else if (strcmp(argv[i], "-f") == 0) {
            optionChanged = 1;
            strcpy(option, "-f");
        }
        else {
            strcpy(_paths[pathIndex], argv[i]);
            pathIndex += 1;
        }
    }

    if (pathIndex == 0) {
        printf( "Error:missing operand");
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

    // Main execution
    for (int i = 0; i < NUM_WORDS && paths[i][0] != '\0'; i++) {
        if (strcmp(option, "-i") == 0) {
            int choice = 1;
            printf("Do you want to remove the file %s [1/0] ", paths[i]);
            scanf("%d", &choice);
            if (choice) {
                if (remove(paths[i]) == 0) {

                }
                else {
                    printf( "Error:The file doesn't exist\n");
                }
            }

        }
        else {
            if (remove(paths[i]) == 0) {

            }
            else {
                if (strcmp(option, "-f") == 0) {

                }
                else {
                    printf( "Error:The file doesn't exist\n");
                }
            }
        }
    }

    return 0;
}
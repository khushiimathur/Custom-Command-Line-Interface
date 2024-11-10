#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_WORDS 10 
#define WORD_LEN 100 

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Error: Enter directory and file names\n");
        return 1;
    }

    char option[WORD_LEN] = "";
    char* paths[NUM_WORDS];
    int optionChanged = 0;
    int pathIndex = 0;

    for (int i = 0; i < NUM_WORDS; i++) {
        paths[i] = (char*)malloc(sizeof(char) * WORD_LEN);
        paths[i][0] = '\0';
    }

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0) {
            optionChanged = 1;
            strcpy(option, "-n");
        }
        else if (strcmp(argv[i], "-E") == 0) {
            optionChanged = 1;
            strcpy(option, "-E");
        }
        else {
            strcpy(paths[pathIndex], argv[i]);
            pathIndex += 1;
        }
    }

    if (pathIndex == 0) {
        printf("Error: Missing operand\n");
        return 1;
    }

    for (int i = 0; i < NUM_WORDS && paths[i][0] != '\0'; i++) {
        if (paths[i][0] != '/' && paths[i][0] != '~') {
            char temp[WORD_LEN];
            snprintf(temp, sizeof(temp), "%s/%s", argv[1], paths[i]);
            strcpy(paths[i], temp);
        }
    }

    int i = 0;
    while (paths[i][0] != '\0') {
        FILE* fptr = fopen(paths[i], "r");
        if (fptr == NULL) {
            printf("Error: File %s doesn't exist\n", paths[i]);
            return 1;
        }

        char a;
        int lnNo = 1;
        if (strcmp(option, "-n") == 0) {
            printf("%d\t", lnNo);
        }
        while (fscanf(fptr, "%c", &a) == 1) {
            if (a == '\n' && strcmp(option, "-E") == 0) {
                printf("$");
            }
            printf("%c", a);
            if (a == '\n' && strcmp(option, "-n") == 0) {
                lnNo += 1;
                printf("%d\t", lnNo);
            }
        }
        printf("\n\n\n");

        i += 1;
        fclose(fptr);
    }

    for (int i = 0; i < NUM_WORDS; i++) {
        free(paths[i]);
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include <pthread.h>



/////////////////////////////// Global variables ///////////////////////////////
char* username;
char hostname[1024];

#define NUM_WORDS 10            // Max number of word in the input  
#define WORD_LEN 100            // Max number of letters in a word of input
#define BUFFER_SIZE 1024

char input[NUM_WORDS][WORD_LEN];


//////////////////////////////////// Colors ////////////////////////////////////
#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define RESET "\033[0m"
#define BOLD "\033[1m"


//////////////////////////////////// Helper ////////////////////////////////////
void* runThread(void* command) {
    system((char*)command);
    return NULL;
}
//////////////////////////////////// Prompt ////////////////////////////////////
void takeInput() {
    // Taking input
    for (int i = 0; i < NUM_WORDS; i++) {
        input[i][0] = '\0';
    }

    char str[NUM_WORDS * WORD_LEN];
    fgets(str, NUM_WORDS * WORD_LEN, stdin);
    for (int i = 0; i < NUM_WORDS * WORD_LEN != str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }
    char* token = strtok(str, " ");
    for (int i = 0; i < NUM_WORDS && token != NULL; i++) {
        strcpy(input[i], token);
        token = strtok(NULL, " ");
    }

}

void prompt() {
    // username
    printf(CYAN BOLD "%s" RESET, username);
    printf("@");
    printf(BLUE "%s " RESET, hostname);

    // current directory
    char tmp[FILENAME_MAX];
    printf(GREEN "%s" RESET, getcwd(tmp, FILENAME_MAX));

    printf(CYAN BOLD"\n█\ue0b0 " RESET);
    takeInput();
}

void sendEmail(const char *sender, const char *password, const char *recipient, const char *subject, const char *body) {
    char command[2048];
    snprintf(command, sizeof(command),
             "python3 send_email.py --sender \"%s\" --password \"%s\" --recipient \"%s\" --subject \"%s\" --body \"%s\"",
             sender, password, recipient, subject, body);
    system(command);
}

int copy_paste() {
    char source_path[256];
    char destination_path[256];

    // Ask for source and destination paths
    printf("Enter the path of the file to copy: ");
    fgets(source_path, sizeof(source_path), stdin);
    source_path[strcspn(source_path, "\n")] = 0; // Remove newline

    printf("Enter the destination directory: ");
    fgets(destination_path, sizeof(destination_path), stdin);
    destination_path[strcspn(destination_path, "\n")] = 0; // Remove newline

    // Open source file
    FILE *source_file = fopen(source_path, "rb");
    if (!source_file) {
        perror("Error opening source file");
        return -1;
    }

    // Construct the destination file path
    char destination_file_path[512];
    snprintf(destination_file_path, sizeof(destination_file_path), "%s/%s", destination_path, strrchr(source_path, '/') + 1);

    // Open destination file
    FILE *dest_file = fopen(destination_file_path, "wb");
    if (!dest_file) {
        perror("Error opening destination file");
        fclose(source_file);
        return -1;
    }

    // Copy content from source to destination
    char buffer[BUFFER_SIZE];
    size_t bytes;
    while ((bytes = fread(buffer, 1, BUFFER_SIZE, source_file)) > 0) {
        fwrite(buffer, 1, bytes, dest_file);
    }

    fclose(source_file);
    fclose(dest_file);
    printf("File copied to '%s'.\n", destination_file_path);
    return 0;
}

// Function to move (cut and paste) a file from source to destination
int cut_paste() {
    char source_path[256];
    char destination_path[256];

    // Ask for source and destination paths
    printf("Enter the path of the file to move: ");
    fgets(source_path, sizeof(source_path), stdin);
    source_path[strcspn(source_path, "\n")] = 0; // Remove newline

    printf("Enter the destination directory: ");
    fgets(destination_path, sizeof(destination_path), stdin);
    destination_path[strcspn(destination_path, "\n")] = 0; // Remove newline

    // Construct the destination file path
    char destination_file_path[512];
    snprintf(destination_file_path, sizeof(destination_file_path), "%s/%s", destination_path, strrchr(source_path, '/') + 1);

    // Use rename function to move the file
    if (rename(source_path, destination_file_path) != 0) {
        perror("Error moving file");
        return -1;
    }

    printf("File moved to '%s'.\n", destination_file_path);
    return 0;
}

///////////////////////////////// Main Function ////////////////////////////////
int main(int argc, char** argv) {
    // Getting the username
    username = getenv("USER");
    hostname[1023] = '\0';
    gethostname(hostname, 1023);


    ///////////////////// Getting the paths of executables /////////////////////
    char tmp[FILENAME_MAX];
    char* absPath = getcwd(tmp, FILENAME_MAX);

    char* arg0 = (char*)malloc(sizeof(char) * FILENAME_MAX);
    strcpy(arg0, argv[0]);
    strcat(arg0, "/");

    if (arg0[0] == '/' || arg0[0] == '~') {
        strcpy(absPath, "");
    }

    char* token = strtok(arg0, "/");
    char* tmpString = (char*)malloc(sizeof(char) * FILENAME_MAX);
    strcpy(tmpString, "");
    while (token != NULL) {
        strcat(absPath, tmpString);
        strcat(absPath, "/");
        strcpy(tmpString, token);
        token = strtok(NULL, "/");
    }

    char* display = (char*)malloc(sizeof(char) * FILENAME_MAX);
    char* date = (char*)malloc(sizeof(char) * FILENAME_MAX);
    char* list = (char*)malloc(sizeof(char) * FILENAME_MAX);
    char* make_dir = (char*)malloc(sizeof(char) * FILENAME_MAX);
    char* remove_dir = (char*)malloc(sizeof(char) * FILENAME_MAX);

    strcpy(display, absPath);
    strcpy(date, absPath);
    strcpy(list, absPath);
    strcpy(make_dir, absPath);
    strcpy(remove_dir, absPath);

    strcat(display, "display");
    strcat(date, "date");
    strcat(list, "list");
    strcat(make_dir, "make_dir");
    strcat(remove_dir, "remove_dir");


    ////////////////////////////// Main execution //////////////////////////////
    int run = 1;
    while (run) {
        prompt();

        
        ////////////////////////// Internal Commands ///////////////////////////
        // exit
        if (strcmp(input[0], "exit") == 0) {
            run = 0;
            return 0;
        }

        // help
        else if (strcmp(input[0], "help") == 0) {
            printf("To get the help regarding the commands of the shell refer to README.md\n");
        }

        // cd
        else if (strcmp(input[0], "change_dir") == 0) {
            char path[1024] = {0}; 
            for (int i = 1; i < NUM_WORDS && input[i][0] != '\0'; i++) {
                strcat(path, input[i]); 
                if (i < NUM_WORDS - 1 && input[i + 1][0] != '\0') {
                    strcat(path, " "); 
                }
            }
            if (chdir(path) != 0) {
                printf(RED BOLD "Error: " RESET);
                printf("no such file or directory: '%s'\n", path);
            }
        }

        
        

        // pwd
        else if (strcmp(input[0], "working_dir") == 0) {
            int flag = 1;
            for (int i = 1; i < NUM_WORDS && input[i][0] != '\0'; i++) {
                if (strcmp(input[1], "-P") == 0) {
                    flag = 0;
                }
                else if (strcmp(input[1], "-L") == 0) {
                    flag = 1;
                }
                else {
                    printf(RED BOLD "Error: " RESET);
                    printf("Command-line option not recognised\n");
                    continue;
                }
            }

            if (flag) {
                char buff[FILENAME_MAX];
                printf("%s\n", getcwd(buff, FILENAME_MAX));
            }
            else {
                char buff[FILENAME_MAX];
                printf("%s\n", getcwd(buff, FILENAME_MAX));
            }
        }

        // echo
        else if (strcmp(input[0], "echo") == 0) {
            int flag = 1;
            for (int i = 1; i < NUM_WORDS && input[i][0] != '\0'; i++) {
                if (strcmp(input[i], "-E") == 0) {
                    flag = 1;
                }
                else if (strcmp(input[i], "-n") == 0) {
                    flag = 0;
                }
                else {
                    printf("%s ", input[i]);
                }
            }

            if (flag) {
                printf("\n");
            }
        }
        ////////////////////////// External Commands ///////////////////////////
        // ls
        else if (strcmp(input[0], "list") == 0) {
            char* option = (char*)malloc(sizeof(char) * WORD_LEN);
            char* _path = (char*)malloc(sizeof(char) * WORD_LEN);
            char* path = (char*)malloc(sizeof(char) * WORD_LEN);
            int optionChanged = 0;
            int pathChanged = 0;
            for (int i = 1; i < NUM_WORDS && input[i][0] != '\0'; i++) {
                if (strcmp(input[i], "-A") == 0) {
                    optionChanged = 1;
                    strcpy(option, "-A");
                }
                else if (strcmp(input[i], "-a") == 0) {
                    optionChanged = 1;
                    strcpy(option, "-a");
                }
                else {
                    pathChanged = 1;
                    strcpy(_path, input[i]);
                }
            }

            if (pathChanged == 0) {
                char tmp[FILENAME_MAX];
                char* currPath = getcwd(tmp, FILENAME_MAX);
                strcpy(path, currPath);
            }
            else {
                if (_path[0] == '/') {
                    strcpy(path, _path);
                    strcat(path, "/");
                }
                else if (_path[0] == '~') {
                    strcpy(path, _path);
                }
                else {
                    char tmp[FILENAME_MAX];
                    char* currPath = getcwd(tmp, FILENAME_MAX);
                    strcpy(path, currPath);
                    strcat(path, "/");
                    strcat(path, _path);
                }
            }

            if (optionChanged == 0) {
                strcpy(option, "");
            }

            
            if (fork() == 0) {
                execl(list, list, path, option, NULL);
                break;
            }
            else {
                wait(NULL);
            }
            
        }

        // date
        else if (strcmp(input[0], "date") == 0) {
            char* option = (char*)malloc(sizeof(char) * WORD_LEN);
            int optionChanged = 0;
            for (int i = 1; i < NUM_WORDS && input[i][0] != '\0'; i++) {
                if (strcmp(input[i], "-u") == 0) {
                    strcpy(option, "-u");
                    optionChanged = 1;
                }
                else if (strcmp(input[i], "-R") == 0) {
                    strcpy(option, "-R");
                    optionChanged = 1;
                }
            }

            if (optionChanged == 0) {
                strcpy(option, "");
            }


            
                if (fork() == 0) {
                    execl(date, date, option, NULL);
                    break;
                }
                else {
                    wait(NULL);
                }
            
        }

        // rm
        else if (strcmp(input[0], "remove_dir") == 0) {
            char tmp[FILENAME_MAX];
            char* currPath = getcwd(tmp, FILENAME_MAX);

            
            
                if (fork() == 0) {
                    execl(remove_dir, remove_dir, currPath, input[1][0] != '\0' ? input[1] : "", input[2][0] != '\0' ? input[2] : "", input[3][0] != '\0' ? input[3] : "", input[4][0] != '\0' ? input[4] : "", input[5][0] != '\0' ? input[5] : "", input[6][0] != '\0' ? input[6] : "", input[7][0] != '\0' ? input[7] : "", input[8][0] != '\0' ? input[8] : "", input[9][0] != '\0' ? input[9] : "", NULL);
                    break;
                }
                else {
                    wait(NULL);
                }
            
        }

        // cat
        else if (strcmp(input[0], "display") == 0) {
            char tmp[FILENAME_MAX];
            char* currPath = getcwd(tmp, FILENAME_MAX);


            
        
                if (fork() == 0) {
                    execl(display, display, currPath, input[1][0] != '\0' ? input[1] : "", input[2][0] != '\0' ? input[2] : "", input[3][0] != '\0' ? input[3] : "", input[4][0] != '\0' ? input[4] : "", input[5][0] != '\0' ? input[5] : "", input[6][0] != '\0' ? input[6] : "", input[7][0] != '\0' ? input[7] : "", input[8][0] != '\0' ? input[8] : "", input[9][0] != '\0' ? input[9] : "", NULL);
                    break;
                }
                else {
                    wait(NULL);
                }
            
        }

        // mkdir
        else if (strcmp(input[0], "make_dir") == 0) {
            char tmp[FILENAME_MAX];
            char* currPath = getcwd(tmp, FILENAME_MAX);


            
            // FORK Process
            
                if (fork() == 0) {
                    execl(make_dir, make_dir, currPath, input[1][0] != '\0' ? input[1] : "", input[2][0] != '\0' ? input[2] : "", input[3][0] != '\0' ? input[3] : "", input[4][0] != '\0' ? input[4] : "", input[5][0] != '\0' ? input[5] : "", input[6][0] != '\0' ? input[6] : "", input[7][0] != '\0' ? input[7] : "", input[8][0] != '\0' ? input[8] : "", input[9][0] != '\0' ? input[9] : "", NULL);
                    break;
                }
                else {
                    wait(NULL);
                }
            
        }
        else if (strcmp(input[0], "send-email") == 0) {
            char sender[256];
            char password[256];
            char recipient[256];
            char subject[256];
            char body[1024];

            printf("Enter sender email: ");
            fgets(sender, sizeof(sender), stdin);
            sender[strcspn(sender, "\n")] = 0;

            printf("Enter sender email password: ");
            fgets(password, sizeof(password), stdin);
            password[strcspn(password, "\n")] = 0;

            printf("Enter recipient email: ");
            fgets(recipient, sizeof(recipient), stdin);
            recipient[strcspn(recipient, "\n")] = 0;

            printf("Enter subject: ");
            fgets(subject, sizeof(subject), stdin);
            subject[strcspn(subject, "\n")] = 0;

            printf("Enter email body: ");
            fgets(body, sizeof(body), stdin);
            body[strcspn(body, "\n")] = 0;

            sendEmail(sender, password, recipient, subject, body);
        }           

        else if (strcmp(input[0], "copy_paste") == 0) {
            copy_paste();
        } 
        else if (strcmp(input[0], "cut_paste") == 0) {
            cut_paste();
        }
        
        else if (strcmp(input[0], "send-email") == 0){
            char sender[256];
            char password[256];
            char recipient[256];
            char subject[256];
            char body[1024];

            printf("Enter sender email: ");
            fgets(sender, sizeof(sender), stdin);
            sender[strcspn(sender, "\n")] = 0;

            printf("Enter sender email password: ");
            fgets(password, sizeof(password), stdin);
            password[strcspn(password, "\n")] = 0;

            printf("Enter recipient email: ");
            fgets(recipient, sizeof(recipient), stdin);
            recipient[strcspn(recipient, "\n")] = 0;

            printf("Enter subject: ");
            fgets(subject, sizeof(subject), stdin);
            subject[strcspn(subject, "\n")] = 0;

            printf("Enter email body: ");
            fgets(body, sizeof(body), stdin);
            body[strcspn(body, "\n")] = 0;

            sendEmail(sender, password, recipient, subject, body);
            

        }
        else {
            printf(RED BOLD "ERROR: " RESET);
            printf("Command not found\n");
        }
    }
        

    return 0;
}
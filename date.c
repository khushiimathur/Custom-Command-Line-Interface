#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
char* command = (argc > 1) ? argv[1] : "";

    if (command[0] == '\0') {
        time_t t = time(NULL);
        printf("%s", ctime(&t));
    }
    else if (strcmp(command, "-u") == 0) {
        time_t now = time(NULL);
        struct tm* t = gmtime(&now);
        for (int i = 0; i < 100 && asctime(t)[i] != '\n'; i++) {
            printf("%c", asctime(t)[i]);
        }
        printf(" GMT\n");
    }
    else if (strcmp(command, "-R") == 0) {
        time_t t = time(NULL);
        struct tm lt = { 0 };
        localtime_r(&t, &lt);

        int hr = lt.tm_gmtoff / 3600;
        int min = (lt.tm_gmtoff / 60) % 60;

        for (int i = 0; i < 100 && ctime(&t)[i] != '\n'; i++) {
            printf("%c", ctime(&t)[i]);
        }
        printf(" %02d%d\n", hr, min);
    }
  
    return 0;
}

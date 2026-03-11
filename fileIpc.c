#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;
    FILE *id;
    int operation;
    int loop = 1;

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    // CHILD PROCESS = BACKGROUND
    if (pid == 0) {
        int bgLoop = 1;

        while (bgLoop == 1) {
            usleep(500000);   // delay so prints can be seen

            id = fopen("1", "r");
            if (id != NULL) {
                printf("BACKGROUND : Operation 1 complete\n");
                fclose(id);
                remove("1");
            }

            id = fopen("2", "r");
            if (id != NULL) {
                printf("BACKGROUND : Operation 2 complete\n");
                fclose(id);
                remove("2");
            }

            id = fopen("3", "r");
            if (id != NULL) {
                printf("BACKGROUND : Operation 3 complete\n");
                fclose(id);
                remove("3");
            }

            id = fopen("4", "r");
            if (id != NULL) {
                printf("BACKGROUND : Operation 4 complete\n");
                fclose(id);
                remove("4");
                bgLoop = 0;   // stop background process
            }
        }

        return 0;
    }

    // PARENT PROCESS = FOREGROUND
    else {
        while (loop == 1) {
            printf("Enter 1, 2, 3, or 4 to quit: ");
            scanf("%d", &operation);

            if (operation == 1) {
                id = fopen("1", "w");
                if (id == NULL) {
                    printf("ERROR : File failed to open\n");
                } else {
                    fclose(id);
                }
            }
            else if (operation == 2) {
                id = fopen("2", "w");
                if (id == NULL) {
                    printf("ERROR : File failed to open\n");
                } else {
                    fclose(id);
                }
            }
            else if (operation == 3) {
                id = fopen("3", "w");
                if (id == NULL) {
                    printf("ERROR : File failed to open\n");
                } else {
                    fclose(id);
                }
            }
            else if (operation == 4) {
                id = fopen("4", "w");
                if (id == NULL) {
                    printf("ERROR : File failed to open\n");
                } else {
                    fclose(id);
                }
                loop = 0;   // stop foreground process
            }
            else {
                printf("ERROR : Illegal input\n");
            }
        }

        wait(NULL);   // wait for child to finish
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    FILE *fp;
    int i;
    char filename[64];

    // Create initial file named "0" to start the sequence
    sprintf(filename, "/tmp/%d", 0);
    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }
    fclose(fp);

    for (i = 0; i < 60; i = i + 1) {
        if ((i & 1) == 0) { // Only act on even numbers
            sprintf(filename, "/tmp/%d", i);
            while (access(filename, F_OK) != 0) {
                usleep(100000); // Poll every 0.1 seconds
            }
            printf("%d\n", i);
            remove(filename); // Remove current turn file
            // Create next file for odd process
            sprintf(filename, "/tmp/%d", i + 1);
            fp = fopen(filename, "w");
            fclose(fp);
        }
        sleep(1);
    }

    return 0;
}

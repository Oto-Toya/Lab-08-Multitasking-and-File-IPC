#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    FILE *fp;
    int i;
    char filename[64];

    for (i = 0; i < 60; i = i + 1) {
        if ((i & 1) == 1) { // Only act on odd numbers
            sprintf(filename, "/tmp/%d", i);
            while (access(filename, F_OK) != 0) {
                usleep(100000); // Poll every 0.1 seconds
            }
            printf("%d\n", i);
            remove(filename); // Remove current turn file
            // Create next file for even process
            sprintf(filename, "/tmp/%d", i + 1);
            fp = fopen(filename, "w");
            fclose(fp);
        }
        sleep(1);
    }

    return 0;
}

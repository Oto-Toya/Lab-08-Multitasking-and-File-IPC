//odd.c
#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>

#define TURN_FILE "/tmp/turn.txt"

static char read_turn(FILE* fp) {
    rewind(fp);
    int c = fgetc(fp);
    return (c == 'A' || c == 'B') ? (char)c : 'A';
}

static void write_turn(FILE* fp, char t) {
    rewind(fp);
    fputc(t, fp);
    fflush(fp);
    fsync(fileno(fp));
}

int main() {
    int i;

    FILE* fp = fopen(TURN_FILE, "r+");
    if (!fp) {
        fp = fopen(TURN_FILE, "w+");
        if (!fp) { perror("fopen"); return 1; }
        fputc('A', fp);         // A goes first
        fflush(fp);
        fsync(fileno(fp));
    }

    for (i = 0; i < 60; i = i + 1) {
		//stop until signal
        if ((i & 1) == 0) { // check if i is odd
            sleep(1);
            continue;
        }
        flock(fileno(fp), LOCK_EX);
        char turn = read_turn(fp);
        if (turn == 'B') {
            printf("B: %d\n", i);
            fflush(stdout);
            write_turn(fp, 'A');
        }

        flock(fileno(fp), LOCK_UN);


        sleep(1);
    }
    fclose(fp);
	return 0;
}

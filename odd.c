//odd.c
#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>

#define TURN_FILE "/tmp/turn.txt"   //IPC File

// Reads and returns char in file stream
static char read_turn(FILE* fp) {
    rewind(fp);     // Clears buffer
    int c = fgetc(fp);  // Gets char from file stream
    return (c == 'A' || c == 'B') ? (char)c : 'A';  // If c is qual to A or B returns char c else returns 'A'
}

// Writes char to file stream
static void write_turn(FILE* fp, char t) {
    rewind(fp);     // Clears buffer
    fputc(t, fp);   // Puts char into file stream
    fflush(fp);     // Force writes to buffer
    fsync(fileno(fp));  // Forces buffer to stream
}

int main() {
    int i;

    FILE* fp = fopen(TURN_FILE, "r+");  // Opens file for reading and writing
    // If fp doesnt exsit
    while(!fp) {
        sleep(1);
        fp = fopen(TURN_FILE, "r+");
    }
    

    for (i = 0; i < 60; i = i + 1) {
        if ((i & 1) == 0) { // check if i is Even
            sleep(1);
            continue;
        }
        //Odd
         while (1){
        flock(fileno(fp), LOCK_EX); // Locks file
        char turn = read_turn(fp);  // Reads the file
        if (turn == 'B') {          // If B
            printf("B: %d\n", i);   // Prints the odd interaction
            fflush(stdout);         
            write_turn(fp, 'A');    // Writes A to file stream
            flock(fileno(fp), LOCK_UN);  // unlock then break
        break;
        }
        // odd
        flock(fileno(fp), LOCK_UN);  // always unlock if odd
        usleep(10000);               // wait before retrying
    }
        sleep(1);   
    }
    fclose(fp); // Closes the file when done
    
	return 0;
}

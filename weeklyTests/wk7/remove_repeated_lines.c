//
// COMP1511 Week 7 Weekly Test - Filtering Out Repeated Lines
//
// By Soorriamoorthy Saruva (z525806) on 1-11-19
//

#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_NUM_LINES 256

int main(void) {
    int numLines = 0;
    char lines[MAX_NUM_LINES][MAX_LINE_LENGTH];
    char line[MAX_LINE_LENGTH];

    while (fgets(line, MAX_LINE_LENGTH, stdin) != NULL) {
        int isRepeated = 0;
        int i = 0;
        // Check if line is repeated while there are more lines to check
        // it is not known to be repeated
        while (i < numLines && !isRepeated) {
            if (strcmp(lines[i], line) == 0) {
                isRepeated = 1;
            }
            i++;
        }
        // If the line is not repeated, copy into the array and print it
        if (!isRepeated) {
            strcpy(lines[numLines], line);
            printf("%s", line);
            numLines++;
        }
    }

    return 0;
}
//
// COMP1511 Week 5 Weekly Test - Indivisible Numbers
//
//  By Soorriamoorthy Saruva (z525806) on 20-10-19
//

#include <stdio.h>

#define MAX_SIZE 1000

int main(void) {
    int numbers[MAX_SIZE] = {0};
    int numCount = 0;

    // Get all numbers
    while ((numCount < MAX_SIZE) && (scanf("%d", &numbers[numCount]) == 1)) {
        numCount++;
    }

    // Print indivisible numbers
    printf("Indivisible numbers: ");
    int i = 0;
    while ((i < numCount) && numCount > 0) {
        int indivisble = 1;
        int j = 0;
        // loop only when there is a valid index and the number is indivisible
        while ((j < numCount) && indivisble) {
            // if the indexes are not the same and the number is divisible
            // by another number, set indivisible to 0
            if ((j != i) && (numbers[i] % numbers[j] == 0)) {
                indivisble = 0;
            }
            j++;
        }
        // If the number is indivisible, print it
        if (indivisble) {
            printf("%d ", numbers[i]);
        }
        i++;
    }
    printf("\n");

    return 0;
}
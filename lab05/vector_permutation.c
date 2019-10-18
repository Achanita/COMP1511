//
// COMP1511 Lab05 - Rearrange a Vector of Integers
// 
// By Soorriamoorthy S Saruva (z5258068) on 18-10-19
// 

#include <stdio.h>

#define MAX_SIZE 1000

int main(void) {
    int length;
    int original[MAX_SIZE] = {0};
    int permutation[MAX_SIZE] = {0};
    int validPermutation = 1;
    int i;

    // Get vector length
    printf("Enter vector length: ");
    scanf("%d", &length);

    // Get vector
    printf("Enter vector: ");
    i = 0;
    while (i < length) {
        scanf("%d", &original[i]);
        i++;
    }

    // Get the final order
    printf("Enter permutation: ");
    i = 0;
    while (i < length) {
        scanf("%d", &permutation[i]);
        i++;
    }

    // Check if the final order is valid
    i = 0;
    while (i < length) {
        validPermutation = validPermutation 
            && (permutation[i] >= 0) 
            && (permutation[i] < length);
        i++;
    }

    if (validPermutation) {
        // Print out the vector in the new order
        i = 0;
        while (i < length) {
            printf("%d ", original[permutation[i]]);
            i++;
        }
        printf("\n");
    } else {
        printf("Invalid permutation\n");
    }

    return 0;
}
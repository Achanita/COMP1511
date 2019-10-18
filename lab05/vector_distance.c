// COMP1511 Week 5 Lab: Euclidean Distance
//
// This program was written by Soorriamoorthy Saruva (z5258068)
// on 18-10-19
//
// This program calculates the maximum value in an array of integers.
//

#include <stdio.h>
#include <math.h>

#define MAX_LENGTH 1000

int main(void) {
    int length;
    int i;

    // Get the vector length
    printf("Enter vector length: ");
    scanf("%d", &length);

    int vector1[MAX_LENGTH] = {0};
    int vector2[MAX_LENGTH] = {0};

    // Get vector 1
    printf("Enter vector 1: ");
    i = 0;
    while (i < length) {
        scanf("%d", &vector1[i]);
        i++;
    }

    // Get vector 2
    printf("Enter vector 2: ");
    i = 0;
    while (i < length) {
        scanf("%d", &vector2[i]);
        i++;
    }

    int squaredDifferenceSum = 0;
    i = 0;
    while (i < length) {
        squaredDifferenceSum += pow(vector1[i] - vector2[i], 2);
        i++;
    }

    double difference = sqrt(squaredDifferenceSum);

    printf("Euclidean distance = %lf\n", difference);

    return 0;
}
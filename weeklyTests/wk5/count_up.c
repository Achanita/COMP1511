//
// COMP1511 Week 5 Weekly Test - Counting Up
//
//  By Soorriamoorthy Saruva (z525806) on 20-10-19
//

#include <stdio.h>

int main(void) {
    int lower;
    int upper;

    // Get lower and upper bounds
    printf("Enter lower: ");
    scanf("%d", &lower);
    printf("Enter upper: ");
    scanf("%d", &upper);

    // Print all numbers between bounds
    int i = 1;
    while (lower + i < upper) {
        printf("%d\n", lower + i);
        i++;
    }

    return 0;
}
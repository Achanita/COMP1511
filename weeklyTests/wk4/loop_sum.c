// 
// COMP1511 Week 4 Weekly Test - Loop Sum
// 
// By Soorriamoorthy Saruva (z5258068)
// 

#include <stdio.h>

int main(void) {
    int numCount;
    int sum = 0;

    printf("How many numbers: ");
    scanf("%d", &numCount);

    int i = 0;
    while (i < numCount) {
        int nextNumber;
        scanf("%d", &nextNumber);
        sum += nextNumber;
        i++;
    }

    printf("The sum is: %d\n", sum);

    return 0;
}
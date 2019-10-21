//
// COMP1511 Week 5 Weekly Test - Odd-Even ten
//
//  By Soorriamoorthy Saruva (z525806) on 20-10-19
//

#include <stdio.h>

#define MAX_SIZE 10

int main(void) {
    int numbers[MAX_SIZE] = {0};
    int odd[MAX_SIZE] = {0};
    int even[MAX_SIZE] = {0};
    int i;

    // Get all 10 numbers
    i = 0;
    while (i < MAX_SIZE) {
        scanf("%d", &numbers[i]);
        i++;
    }

    // Split the numbers
    int oddCount = 0;
    int evenCount = 0;
    i = 0;
    while (i < MAX_SIZE) {
        if (numbers[i] % 2 == 1) {
            odd[oddCount] = numbers[i];
            oddCount++;
        } else {
            even[evenCount] = numbers[i];
            evenCount++;
        }
        i++;
    }

    // Print odd numbers
    printf("Odd numbers were: ");
    i = 0;
    while (i < oddCount) {
        printf("%d ", odd[i]);
        i++;
    }
    printf("\n");
    // Print even numbers
    i = 0;
    printf("Even numbers were: ");
    while (i < evenCount) {
        printf("%d ", even[i]);
        i++;
    }
    printf("\n");

    return 0;
}
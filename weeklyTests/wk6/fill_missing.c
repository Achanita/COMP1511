//
// COMP1511 Week 6 Weekly Test - Return Common Elements Of Two Arrays
//
//  By Soorriamoorthy Saruva (z525806) on 28-10-19
//

#include <stdio.h>

#define MAX_SIZE 1000

int getMax(int length, int array[length]);

int includes(int length, int array[length], int search);

int main(void) {
    int numbers[MAX_SIZE] = {0};
    int length = 0;
    while ((length < MAX_SIZE) && (scanf("%d", &numbers[length]) == 1)) {
        length++;
    }
    int max = getMax(length, numbers);
    int currentNumber = 1;
    while (currentNumber <= max) {
        if (!includes(length, numbers, currentNumber)) {
            printf("%d ", currentNumber);
        }
        currentNumber++;
    }
    printf("\n");
    return 0;
}

int includes(int length, int array[length], int search) {
    int i = 0;
    while (i < length) {
        if (array[i] == search) {
            return 1;
        }
        i++;
    }
    return 0;
}

int getMax(int length, int array[length]) {
    int i = 1;
    int max = array[0];
    while (i < length) {
        if (array[i] > max) {
            max = array[i];
        }
        i++;
    }
    return max;
}
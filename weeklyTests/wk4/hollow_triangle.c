// 
// COMP1511 Week 4 Weekly Test - Print a Hollow Triangle
// 
// By Soorriamoorthy Saruva (z5258068)
// 

#include <stdio.h>

int main(void) {
    int size;

    printf("Enter size: ");
    scanf("%d", &size);

    // Print all but the last row
    int row = 0;
    while (row < size) {
        int i = 0;
        while (i <= row) {
            // Print `*` if it is the first or last character
            // or if it is the base of the triangle
            if (i == 0 || i == row || row == size - 1) {
                printf("*");
            } else {
                printf(" ");
            }

            i++;
        }
        printf("\n");

        row++;
    }

    return 0;
}
//
// COMP1511 Lab04 - Draw an X
//
// By Soorriamoorthy Saruva (z5258068)
//

#include <stdio.h>

int main(void) {
    int size;
    printf("Enter size: ");
    scanf("%d", &size);

    int count = 0;
    while (count < size / 2 + 1) {
        int i = 0;
        while (i < size) {
            if (count == i || count == size - 1 - i) {
                printf("*");
            } else {
                printf("-");
            }
            i++;
        }
        printf("\n");
        count++;
    }
    count = size / 2 - 1;
    while (count >= 0) {
        int i = 0;
        while (i < size) {
            if (count == i || count == size - 1 - i) {
                printf("*");
            } else {
                printf("-");
            }
            i++;
        }
        printf("\n");
        count--;
    }

    return 0;
}
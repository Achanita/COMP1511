//
// COMP1511 lab06 - Its a Case of Swapping
//
// By Soorriamoorthy Saruva (z5258068)
//

#include <stdio.h>

int swap_case(int character);

int main(void) {
    int character = getchar();
    while (character != EOF) {
        putchar(swap_case(character));
        character = getchar();
    }
    return 0;
}

int swap_case(int character) {
    if (character >= 'a' && character <= 'z') {
        int characterPosition = character - 'a';
        return 'A' + characterPosition;
    } else if (character >= 'A' && character <= 'Z') {
        int characterPosition = character - 'A';
        return 'a' + characterPosition;
    }
    return character;
}

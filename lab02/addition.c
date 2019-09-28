// 
// COMP1511 LAB02 - Addition
//
// By Soorriamoorthy S Saruva (z5259068)
//

#include <stdio.h>

int main(void) {
    int num1;
    int num2;
    
    printf("Please enter two integers: ");
    scanf("%d%d", &num1, &num2);
    int sum = num1 + num2;
    printf("%d + %d = %d\n", num1, num2, sum);
    
    return 0;
}

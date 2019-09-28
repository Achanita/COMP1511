// 
// COMP1511 LAB02 - Dice Range
//
// By Soorriamoorthy S Saruva (z5259068)
//

#include <stdio.h>

int main(void) {
    int num_sides;
    int num_dice;
    
    printf("Enter the number of sides on your dice: ");
    scanf("%d", &num_sides);
    
    printf("Enter the number of dice being rolled: ");
    scanf("%d", &num_dice);

    if (num_sides < 1 || num_dice < 1) {
        printf("These dice will not produce a range.\n");
    } else {
        int min = num_dice;
        int max = num_sides * num_dice;
        double average = (num_sides + 1.0) / 2 * num_dice;
        
        printf("Your dice range is %d to %d.\n", min, max);
        printf("The average value is %f\n", average);
    }
    
    

    return 0;
}

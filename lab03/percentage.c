//
// COMP1511 Lab03 - Calculating Exam Marks
//
// By Soorriamoorthy Saruva (z5258068)
//

#include <stdio.h>

int main(void) {
    int totalMarks;
    int studentMark;

    printf("Enter the total number of marks in the exam: ");
    scanf("%d", &totalMarks);
    printf("Enter the number of marks the student was awarded: ");
    scanf("%d", &studentMark);

    double percentage = 100.0 * studentMark / totalMarks;

    printf("The student scored %.0f%% in this exam.\n", percentage); 

    return 0;
}
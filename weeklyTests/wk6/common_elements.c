//
// COMP1511 Week 6 Weekly Test - Return Common Elements Of Two Arrays
//
//  By Soorriamoorthy Saruva (z525806) on 28-10-19
//

// copy all of the values in source1 which are also found in source2 into destination
// return the number of elements copied into destination
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

int common_elements(int length, int source1[length], int source2[length], int destination[length]) {
    int count = 0;

    int i = 0;
    while (i < length) {
        int search = source1[i];
        if (includes(length, source2, search)) {
            destination[count] = search;
            count++;
        }
        i++;
    }

    return count;
}

// You may optionally add a main function to test your common_elements function.
// It will not be marked.
// Only your common_elements function will be marked.

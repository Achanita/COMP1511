//
// COMP1511 lab08 - Find an element in a Linked List
//
// By Soorriamoorthy Saruva (z5258068)
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node *next;
    int data;
};

int contains(int value, struct node *head);
struct node *strings_to_list(int len, char *strings[]);

// DO NOT CHANGE THIS MAIN FUNCTION

int main(int argc, char *argv[]) {
    int value;
    scanf("%d", &value);
    // create linked list from command line arguments
    struct node *head = NULL;
    if (argc > 1) {
        // list has elements
        head = strings_to_list(argc - 1, &argv[1]);
    }

    int result = contains(value, head);
    printf("%d\n", result);

    return 0;
}

// Return 1 if value occurs in linked list, 0 otherwise
int contains(int value, struct node *head) {
    struct node *current = head;
    while (current != NULL) {
        if (current->data == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// DO NOT CHANGE THIS FUNCTION
// create linked list from array of strings
struct node *strings_to_list(int len, char *strings[]) {
    struct node *head = NULL;
    int i = len - 1;
    while (i >= 0) {
        struct node *n = malloc(sizeof(struct node));
        assert(n != NULL);
        n->next = head;
        n->data = atoi(strings[i]);
        head = n;
        i -= 1;
    }
    return head;
}

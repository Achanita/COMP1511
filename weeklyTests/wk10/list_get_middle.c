//
// COMP1511 Week 10 Weekly Test - Find the Middle Element of a Linked List
//
// By Soorriamoorthy Saruva (z525806)
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node *next;
    int data;
};

int get_middle(struct node *head);
struct node *strings_to_list(int len, char *strings[]);
int list_length(struct node *head);

// DO NOT CHANGE THIS MAIN FUNCTION

int main(int argc, char *argv[]) {
    // create linked list from command line arguments
    struct node *head = strings_to_list(argc - 1, &argv[1]);

    int result = get_middle(head);
    printf("%d\n", result);

    return 0;
}

int list_length(struct node *head) {
    int length = 0;
    while (head != NULL) {
        length++;
        head = head->next;
    }
    return length;
}

// Return middle element of a linked list
// if list contains [6,7,8,9,10]  8 is returned
// if a list has even number of elements, first of middle two elements returned
// if list contains [1,2,3,4] 2 is returned
// list can not be empty
int get_middle(struct node *head) {
    int i = 0;
    int middle_index = (list_length(head) + 1) / 2;

    while (i < middle_index - 1) {
        head = head->next;
        i++;
    }

    return head->data;
}

// DO NOT CHANGE THIS FUNCTION

// create linked list from array of strings
struct node *strings_to_list(int len, char *strings[]) {
    struct node *head = NULL;
    for (int i = len - 1; i >= 0; i = i - 1) {
        struct node *n = malloc(sizeof(struct node));
        assert(n != NULL);
        n->next = head;
        n->data = atoi(strings[i]);
        head = n;
    }
    return head;
}

//
// COMP1511 lab08 - Reverse a Linked List
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

struct node *reverse(struct node *head);
struct node *strings_to_list(int len, char *strings[]);
void print_list(struct node *head);

// DO NOT CHANGE THIS MAIN FUNCTION

int main(int argc, char *argv[]) {
    // create linked list from command line arguments
    struct node *head = strings_to_list(argc - 1, &argv[1]);

    struct node *new_head = reverse(head);
    print_list(new_head);

    return 0;
}

//
// Place the list pointed to by head into reverse order.
// The head of the list is returned.
//
struct node *reverse(struct node *head) {
    struct node *prev = NULL;
    struct node *current = head;
    struct node *next = NULL;
    while (current != NULL) {
        // get next item from original
        next = current->next;
        // set current node to point to the previous node
        current->next = prev;
        // step forward
        prev = current;
        current = next;
    }
    return prev;
}
// struct node *reverse(struct node *head) {
//     struct node *newHead = malloc(sizeof(struct node));
//     newHead->data = head->data;
//     newHead->next = NULL;
//     struct node *current = head->next;
//     while (current != NULL) {
//         // struct node *new = malloc(sizeof(struct node));
//         // struct node *new = current;
//         head = current;
//         head->data = current->data;
//         head->next = newHead;
//         newHead = new;
//         current = current->next;
//     }
//     return newHead;
// }

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

// DO NOT CHANGE THIS FUNCTION
// print linked list
void print_list(struct node *head) {
    printf("[");

    for (struct node *n = head; n != NULL; n = n->next) {
        // If you're getting an error here,
        // you have returned an invalid list
        printf("%d", n->data);
        if (n->next != NULL) {
            printf(", ");
        }
    }
    printf("]\n");
}

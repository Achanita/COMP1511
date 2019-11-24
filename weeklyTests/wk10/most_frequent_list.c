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

int most_frequent(struct node *head);
struct node *strings_to_list(int len, char *strings[]);
int count(struct node *head, int num);

// DO NOT CHANGE THIS MAIN FUNCTION

int main(int argc, char *argv[]) {
    // create linked list from command line arguments
    struct node *head = strings_to_list(argc - 1, &argv[1]);

    int result = most_frequent(head);
    printf("%d\n", result);

    return 0;
}

int count(struct node *head, int num) {
    int count = 0;
    while (head != NULL) {
        if (head->data == num) {
            count++;
        }
        head = head->next;
    }
    return count;
}

// return the value which occurs most frequently in a linked list
// if several values are equally most frequent
// the value that occurs earliest in the list is returned
int most_frequent(struct node *head) {
    int max_num = 0;
    int max_freq = 0;
    struct node *current = head;
    while (current != NULL) {
        int current_num = current->data;
        int freq = count(head, current->data);
        if (freq > max_freq) {
            max_num = current_num;
            max_freq = freq;

        }
        current = current->next;
    }
    return max_num;
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

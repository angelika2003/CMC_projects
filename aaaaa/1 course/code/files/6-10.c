#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node *next;
    struct Node *prev;
};

void print_list_file(struct Node* head, char filename[]) {
    FILE *f = fopen(filename, "w");
    while (head) {
        fprintf(f, "%d ", head->value);
        head = head->next;
    }

    fclose(f);
}

struct Node *create_new_node(int value) {
    struct Node *new_node = (struct Node*)calloc(1, sizeof(struct Node));
    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

struct Node* shift(struct Node *head, int a, int b, struct Node **arr) {
    if (head->value == a) {
        return head;
    }

    struct Node *cur1 = arr[a];

    struct Node *ans = cur1;

    struct Node *cur2 = arr[b];

    if (cur2->next != NULL) {
        cur1->prev->next = cur2->next;
        cur2->next->prev = cur1->prev;
    } else {
        cur1->prev->next = NULL;
    }

    cur2->next = head;
    head->prev = cur2;

    cur1->prev = NULL;

    return ans;
}

void delete(struct Node *head) {
    struct Node *next;
    while (head) {
        next = head->next;
        free(head);
        head = next;
    }
}

int main(void) {
    char filename[] = "input.txt";
    FILE *f1 = fopen(filename, "r");

    int n, m;
    fscanf(f1, "%d %d", &n, &m);

    struct Node **arr = (struct Node **)calloc(n + 1, sizeof(struct Node *));

    arr[0] = NULL;
    arr[1] = create_new_node(1);
    struct Node *head = arr[1];

    for (int i = 2; i <= n; ++i) {
        arr[i] = create_new_node(i);
        arr[i]->prev = arr[i - 1];
        arr[i - 1]->next = arr[i];
    }

    int a, b;
    for (int i = 0; i < m; ++i) {
        fscanf(f1, "%d %d", &a,  &b);
        head = shift(head, a, b, arr);
    }

    fclose(f1);

    print_list_file(head, "output.txt");

    delete(head);
    free(arr);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node *next;
};

struct Node *create_new_node(int value) {
    struct Node* new_node = (struct Node *)calloc(1, sizeof(struct Node));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

struct Node *shift(struct Node *head, int a) {
    if (head->value == a) {
        return head;
    }

    struct Node *cur1 = head;
    while (cur1->next->value != a) {
        cur1 = cur1->next;
    }

    struct Node *ans = cur1->next;
    struct Node *cur2 = ans;

    while (cur2->next != NULL) {
        cur2 = cur2->next;
    }

    cur2->next = head;
    cur1->next = NULL;

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

    struct Node *head = create_new_node(1);
    struct Node *cur = head;
    for (int i = 2; i <= n; ++i) {
        cur->next = create_new_node(i);
        cur = cur->next;
    }

    int a;
    for (int i = 0; i < m; ++i) {
        fscanf(f1, "%d", &a);
    }
    fclose(f1);

    head = shift(head, a);

    char file[] = "output.txt";
    FILE *f2 = fopen(file, "w");

    cur = head;
    while (cur) {
        fprintf(f2, "%d ", cur->value);
        cur = cur->next;
    }

    delete(head);
    fclose(f2);

    return 0;
}
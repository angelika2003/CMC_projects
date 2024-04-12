#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 102
#define MAX ((int)1e9+1)

struct Node {
    int value;
    char *s;
    char *subs;
    struct Node *next;
};

void print_list_file(struct Node *head, char filename[]) {
    FILE* f = fopen(filename, "w");

    while (head) {
        fprintf(f, "%s", head->s);
        head = head->next;
    }

    fclose(f);
}

struct Node *create_new_node(char *substr, int value, char *str) {
    struct Node *new_node = (struct Node *)malloc(1 * sizeof(struct Node));

    new_node->value = value;

    new_node->s = (char *)malloc(BUF_SIZE * sizeof(char));
    strcpy(new_node->s, str);

    new_node->subs = (char *)malloc(BUF_SIZE * sizeof(char));
    strcpy(new_node->subs, substr);

    new_node->next = NULL;

    return new_node;
}

void remove_spaces(char *s) {
    char *t = s;
    int not_string = 1;
    while (*s) {
        if (*s == '"') {
            *t = *s;
            s++;
            t++;

            while (*s != '"') {
                *t = *s;
                s++;
                t++;
            }

            *t = *s;
            s++;
            t++;
            not_string = 0;
        } else if (*s != ' ') {
            *t = *s;
            t++;
        }

        if (not_string) {
            s++;
        }

        not_string = 1;
    }
    *t = '\0';
}

int char_to_int(char c) {
    return c - '0';
}

int is_digit(char c) {
    if ((c >= '0') && (c <= '9')) {
        return 1;
    }
    return 0;
}

int get_value(char *s, int number) {
    int n = 0;
    int i = 0;
    if (number == 0) {
        int is_signed = 1;

        if (s[i] == '-') {
            is_signed = -1;
            i++;
        }

        int value = char_to_int(s[i]);

        i++;
        while (is_digit(s[i]) == 1) {
            value = value * 10 + char_to_int(s[i]);
            i++;
        }

        return value * is_signed;

    }

    int len = strlen(s);

    for (int i = 0; i < len; ++i) {
        if (s[i] == ';') {
            n++;
        }

        if (n == number) {
            i++;

            if (s[i] == '"') {
                return MAX;
            }

            int is_signed = 1;
            if (s[i] == '-') {
                is_signed = -1;
                i++;
            }

            int value = char_to_int(s[i]);

            i++;
            while (is_digit(s[i]) == 1) {
                value = value * 10 + char_to_int(s[i]);
                i++;
            }

            return value * is_signed;
        }
    }

    return MAX;
}

char *get_substr(char *s, int number) {
    int n = 0;

    for (int i = 0; i < BUF_SIZE; ++i) {
        if (s[i] == ';') {
            n++;
        }

        if (n == number) {
            i++;
            while (s[i] != '"') {
                i++;
            }
            i++;

            char *subs = (char *)malloc(BUF_SIZE * sizeof(char));
            int j = 0;
            while (s[i] != '"') {
                subs[j] = s[i];
                j++;
                i++;
            }

            return subs;
        }
    }

    return NULL;
}

struct Node *merge_lists_value(struct Node *head1, struct Node *head2) {
    struct Node *head = (head1->value <= head2->value) ? head1 : head2;
    struct Node *ans = head;
    if (head == head1) {
        head1 = head1->next;
    } else {
        head2 = head2->next;
    }

    while (head1 && head2) {

        int v1 = head1->value;
        int v2 = head2->value;

        if (v1 <= v2) {
            head->next = head1;
            head1 = head1->next;
        } else {
            head->next = head2;
            head2 = head2->next;
        }

        head = head->next;
    }

    if (head1 == NULL) {
        head->next = head2;
    } else {
        head->next = head1;
    }

    return ans;
}

struct Node *merge_value(struct Node *head, int len) {
    if (len == 1) {
        return head;
    }
    int part_len = len / 2;

    struct Node *head1 = head;
    part_len--;

    while (part_len) {
        head = head->next;
        part_len--;
    }
    struct Node *head2 = head->next;
    head->next = NULL;

    return merge_lists_value(merge_value(head1, len / 2 ), merge_value(head2, len - len / 2));
}

struct Node *merge_lists_subs(struct Node *head1, struct Node *head2) {
    struct Node *head = (strcmp(head2->subs, head1->subs) >= 0) ? head1 : head2;
    struct Node *ans = head;

    if (head == head1) {
        head1 = head1->next;
    } else {
        head2 = head2->next;
    }

    while (head1 && head2) {

        char *s1 = head1->subs;
        char *s2 = head2->subs;

        if (strcmp(s2, s1) >= 0) {
            head->next = head1;
            head1 = head1->next;
        } else {
            head->next = head2;
            head2 = head2->next;
        }

        head = head->next;
    }

    if (head1 == NULL) {
        head->next = head2;
    } else {
        head->next = head1;
    }

    return ans;
}

struct Node *merge_subs(struct Node *head, int len) {
    if (len == 1) {
        return head;
    }
    int l = len / 2;

    struct Node *head1 = head;
    l--;

    while (l) {
        head = head->next;
        l--;
    }
    struct Node *head2 = head->next;
    head->next = NULL;

    return merge_lists_subs(merge_subs(head1, len / 2 ), merge_subs(head2, len - len / 2));
}

void delete(struct Node *head) {
    struct Node *next;
    while (head) {
        next = head->next;
        free(head->s);
        free(head->subs);

        free(head);
        head = next;
    }
}

int main(void) {
    char filename[] = "input.txt";
    FILE *f1 = fopen(filename, "r");

    int number;
    fscanf(f1, "%d\n", &number);

    char *s = (char *)malloc(BUF_SIZE * sizeof(char));
    fgets(s, BUF_SIZE, f1);
    remove_spaces(s);
    int value = get_value(s, number);

    struct Node *head;

    if (value != MAX) {
        head = create_new_node("", value, s);
        struct Node *cur = head;

        int len = 1;

        while (fgets(s, BUF_SIZE, f1) != NULL) {
            remove_spaces(s);
            value = get_value(s, number);
            cur->next = create_new_node("", value, s);
            cur = cur->next;
            len++;
        }

        head = merge_value(head, len);

    } else {
        char *substr = get_substr(s, number);
        head = create_new_node(substr, 0, s);
        struct Node *cur = head;

        int len = 1;

        while (fgets(s, BUF_SIZE, f1) != NULL) {
            remove_spaces(s);
            substr = get_substr(s, number);
            cur->next = create_new_node(substr, 0, s);
            cur = cur->next;
            len++;
        }

        head = merge_subs(head, len);
    }

    free(s);

    fclose(f1);

    print_list_file(head, "output.txt");

    delete(head);

    return 0;
}
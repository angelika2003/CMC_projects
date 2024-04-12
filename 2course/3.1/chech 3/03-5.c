#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

struct Elem
{
    struct Elem *next;
    char *str;
};

enum
{
    BASE = 10
};

struct Elem *dup_elem(struct Elem *head) {
    struct Elem *cur = head;
    struct Elem *prev = NULL;
    while (cur) {
        char *eptr = NULL;
        errno = 0;
        long n = strtol(cur->str, &eptr, BASE);

        if (errno || *eptr || eptr == cur->str || (int)n != n) {
            prev = cur;
            cur = cur -> next;
            continue;
        }

        int n_int = n;

        if (__builtin_add_overflow(1, n_int, &n_int)) {
            prev = cur;
            cur = cur -> next;
            continue;
        }

        if (cur == head) {
            struct Elem *new_head = (struct Elem*)calloc(1, sizeof(struct Elem));

            char *s;
            asprintf(&s, "%d", n_int);

            new_head->next = head;
            new_head->str = s;

            head = new_head;

            prev = cur;
            cur = cur -> next;
            continue;
        }

        struct Elem *new = (struct Elem*)calloc(1, sizeof(struct Elem));
        prev->next = new;
        new->next = cur;

        char *s;
        asprintf(&s, "%d", n_int);

        new->str = s;

        prev = cur;
        cur = cur -> next;
    }

    return head;
}
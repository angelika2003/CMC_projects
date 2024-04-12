#include <stdio.h>
#include <stdlib.h>

struct list {
	int key;
	struct list* next;
	struct list* sublist;
};

struct list* create_new_node (int key) {
	struct list* new = (struct list *)malloc(sizeof(struct list));
	new->next = NULL;
	new->sublist = NULL;
	new->key = key;

	return new;
}

int examine(struct list* head) {
	static int max = 0;
	static int len = 0;

	if (head == NULL) {
		return -1;
	}

	struct list *cur = head;
	int cur_max = 0;
	int cur_len = 0;

	while (cur != NULL) {
		cur_max += cur->key;
		cur_len += 1;

		if (cur->sublist) {
			examine(cur->sublist);
		}

		cur = cur->next;
	}

	if (cur_len > len) {
		len = cur_len;
		max = cur_max;
	} else if (cur_len == len) {
		if (cur_max > max) {
			max = cur_max;
		}
	}

	return max;
}

int main(void) {
	struct list* head = (struct list *)malloc(sizeof(struct list));
	head->key = 1;
	head->next = create_new_node(1);
	head->next->next = create_new_node(1);
	head->next->next->sublist = create_new_node(4);
	head->next->next->sublist->next = create_new_node(4);
	head->sublist = create_new_node(2);
	head->sublist->next = create_new_node(2);
	head->sublist->next->next = create_new_node(2);
	head->sublist->next->sublist = create_new_node(3);
	head->sublist->next->sublist->next = create_new_node(3);
	head->sublist->next->sublist->next->next = create_new_node(3);

	printf("%d", examine(head));

	return 0;
}
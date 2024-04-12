#include <stdio.h>
#include <stdlib.h>

struct list {
	int key;
	struct list* next;
	struct list* sublist;
};

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
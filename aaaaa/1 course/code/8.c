#include <stdio.h>
#include <stdlib.h>

struct tree {
	int x;
	struct tree *left;
	struct tree *right;
};


void print_tree(struct tree *head) {
	if (head == NULL) {
		return;
	}
	print_tree(head->left);
	printf("%d ", head->x);
	print_tree(head->right);
}

int search(struct tree *head, int value) {
	if (head == NULL) {
		return 0;
	}

	if (head->x == value) {
		return 1;
	}

	if (value > head->x) {
		return search(head->right, value);

	}

	return search(head->left, value);
}

int is_subset(int size, struct tree *t1, struct tree *t2) {
	if (t1 == NULL) {
		return 1;
	}

	if (is_subset(size, t1->left, t2) == 0) {
		return 0;
	}

	if (search(t2, t1->x) == 0) {
		return 0;
	}


	if (is_subset(size, t1->left, t2) == 0) {
		return 0;
	}

	return 1;


}
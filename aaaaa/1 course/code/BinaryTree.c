#include <stdio.h>
#include <stdlib.h>

struct tree {
	int x;
	struct tree *left;
	struct tree *right;
};

struct tree *create_new_node(int x) {
	struct tree *new = (struct tree *)malloc(sizeof(struct tree));
	new->x = x;
	new->left = NULL;
	new->right = NULL;

	return new;
}

void add_node(struct tree *head, int x) {
	if (x < head->x) {
		if (head->left == NULL) {
			head->left = create_new_node(x);
			return;
		}
		return add_node(head->left, x);
	}

	if (x > head->x) {
		if (head->right == NULL) {
			head->right = create_new_node(x);
			return;
		}
		return add_node(head->right, x);
	}
}

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

int is_subset(struct tree *t1, struct tree *t2) {
	if (t1 == NULL) {
		return 1;
	}

	if (is_subset(t1->left, t2) == 0) {
		return 0;
	}

	if (search(t2, t1->x) == 0) {
		return 0;
	}

	if (is_subset(t1->left, t2) == 0) {
		return 0;
	}

	return 1;
}

int main(void) {
	struct tree *head = create_new_node(5);
	add_node(head, 3);
	add_node(head, 7);
	

	struct tree *head1 = create_new_node(5);
	add_node(head1, 6);
	add_node(head1, 7);
	add_node(head1, 1);
	add_node(head1, 6);
	add_node(head1, 10);



	

	printf("%d", is_subset(head, head1));








	return 0;
}
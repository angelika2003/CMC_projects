#include <stdio.h>
#include <stdlib.h>

struct Tree {
	int key;
	struct Tree *left;
	struct Tree *right;
};

struct Tree *create_new_node(int value) {
	struct Tree *new = (struct Tree *)malloc(sizeof(struct Tree));
	new->key = value;
	new->left = NULL;
	new->right = NULL;

	return new;
}

int layer_size (struct Tree *root, int n) {
	if (root == NULL) {
		return 0;
	}

	if (n == 1) {
		if (root != NULL) {
			return 1;
		}
		return 0;
	}

	return layer_size(root->left, n - 1) + layer_size(root->right, n - 1);
}

void add_node(struct Tree *root, int key) {
	if (key > root->key) {
		if (root->right == NULL) {
			root->right = create_new_node(key);
			return;
		}
		return add_node(root->right, key);
	}

	if (key < root->key) {
		if (root->left == NULL) {
			root->left = create_new_node(key);
			return;
		}
		return add_node(root->left, key);
	}
}

void print_tree(struct Tree *root) {
	if (root == NULL) {
		return;
	}
	print_tree(root->left);
	printf("%d ", root->key);
	print_tree(root->right);
}

int main(void) {
	struct Tree *root = create_new_node(5);
	add_node(root, 7);
	add_node(root, 1);
	add_node(root, 4);
	add_node(root, 6);
	add_node(root, 19);
	add_node(root, 23);
	add_node(root, 45);
	add_node(root, 9);
	add_node(root, 3);

	print_tree(root);
	printf("\n");
	printf("%d", layer_size(root, 8));



	return 0;
}
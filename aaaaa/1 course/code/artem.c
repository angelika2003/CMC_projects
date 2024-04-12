#include <stdio.h>
#include <stdlib.h>

struct Tree {
	int key;
	int height;

	struct Tree* left;
	struct Tree* right;
};

int height(struct Tree* t) {
	return t ? t->height : 0;
}

int max(int a, int b) {
	return (a >= b) ? a : b;
}

struct Tree *RR_turn(struct Tree *x) {
	struct Tree *y = x->right;

	x->right = y->left;
	y->left = x;

	x->height = max(height(x->right), height(x->right)) + 1;
	y->height = max(height(y->right), height(y->right)) + 1;

	return y;
}

struct Tree *LL_turn(struct Tree *x) {
	struct Tree *y = x->left;

	x->left = y->right;
	y->right = x;

	x->height = max(height(x->right), height(x->left)) + 1;
	y->height = max(height(y->right), height(y->left)) + 1;

	return y;
}

struct Tree *LR_turn(struct Tree *x) {
	x->left = RR_turn(x->left);

	return LL_turn(x);
}

struct Tree *RL_turn(struct Tree *x) {
	x->right = LL_turn(x->right);

	return RR_turn(x);
}

struct Tree *add (struct Tree* t, int key) {
	if (t == NULL) {
		t = (struct Tree *)malloc(sizeof(struct Tree));
		t->key = key;
		t->height = 1;
		t->left = t->right = NULL;
	} else if (key > t->key) {
		t->right = add(t->right, key);
		if (height(t->right) - height(t->left) == 2) {
			if (key > t->right->key) {
				t = RR_turn(t);
			} else {
				t = RL_turn(t);
			}
		}
	} else if (key < t->key) {
		t->left = add(t->left, key);
		if (height(t->left) - height(t->right) == 2) {
			if (key < t->left->key) {
				t = LL_turn(t);
			} else {
				t = LR_turn(t);
			}
		}
	}

	t->height = max(height(t->right), height(t->left)) + 1;
	return t;
}

void print_tree(struct Tree *root) {
	if (root == NULL) {
		return;
	}
	print_tree(root->left);
	printf("%d(%d) ", root->key, root->height );
	print_tree(root->right);
}

int main (void) {
	struct Tree *root = NULL;
	root = add(root, 3);
	print_tree(root);
	printf("\n");	
	root = add(root, 5);
	print_tree(root);
	printf("\n");		
	root = add(root, 7);
	print_tree(root);	
	printf("\n");	
	root = add(root, 2);
	print_tree(root);	
	printf("\n");	
	root = add(root, 23);
	//root = add(root, 3);

	print_tree(root);	

	return 0;
}
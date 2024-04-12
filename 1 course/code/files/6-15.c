#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 102
#define MAX(x, y) ((x) >= (y) ? (x) : (y))

struct tree {
	char *s;
	unsigned ip;
	int height;
	struct tree *left;
	struct tree *right;
};

int height(struct tree *root) {
	return root ? root->height : 0;
}

struct tree *turn_LL(struct tree *k2) {
	struct tree* k1;

	/* выполнение поворота */
	k1 = k2->left;
	k2->left = k1->right; /* k1 != NULL */
	k1->right = k2;

	/* корректировка высот переставленных узлов */
	k2->height = MAX(height (k2->left), height (k2->right)) + 1;
	k1->height = MAX(height (k1->left), k2->height) + 1;

	return k1; /* новый корень */
}

struct tree *turn_RR(struct tree *k2) {
	struct tree *k1;
	k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;

	k2->height = MAX(height (k2->right), height (k2->left)) + 1;   
	k1->height = MAX(height (k1->right), k2->height) + 1;

	return k1;
}

struct tree *turn_LR(struct tree* k3) {
	/* Поворот между K1 и K2 */
	k3->left = turn_RR(k3->left);
	/* Поворот между K3 и K2 */
	return turn_LL(k3);
}

struct tree *turn_RL(struct tree *k3) {
	/* Поворот между K1 и K2 */
	k3->right = turn_LL(k3->right);
	/* Поворот между K3 и K2 */
	return turn_RR(k3);
}

struct tree *insert(unsigned x, char *s, struct tree *t) {
	if (t == NULL) {
		/* создание дерева с одним узлом */
		t = malloc (sizeof (struct tree));
		t->ip = x;
		t->s = s;
		t->height = 1;
		t->left = t->right = NULL;
	}
	else if (strcmp(s, t->s) < 0) {                                     
		t->left = insert (x, s, t->left);
		if ((height (t->left) - height (t->right)) == 2) {
			if (strcmp(s, t->left->s) < 0) {
				t = turn_LL (t);
			} else {
				t = turn_LR (t);
			}
		}
	}
	else if (strcmp(s, t->s) > 0) {
		t->right = insert (x, s, t->right);
		if ((height (t->right) - height (t->left)) == 2) {
			if (strcmp(s, t->right->s) > 0) {
				t = turn_RR (t);
			} else {
				t = turn_RL (t);
			}
		}
	}
	/* иначе x уже в дереве */
	t->height = MAX (height (t->left), height (t->right)) + 1;
	return t;
}

long long find(char *s, struct tree *t) {
	if (t == NULL) {
		return -1;
	}

	if (strcmp(s, t->s) == 0) {
		return t->ip;
	}

	if (strcmp(s, t->s) > 0) {
		return find(s, t->right);
	}

	return find(s, t->left);
}

void delete_tree(struct tree *root) {
	if (root == NULL) {
		return;
	}
	delete_tree(root->left);
	delete_tree(root->right);
	free(root->s);
	free(root);
}

int main(void) {
	FILE *input = fopen("input.txt", "r");
	int n;
	fscanf(input, "%d", &n);

	struct tree *root = NULL;

	for (int i = 0; i < n; ++i) {
		char *s = malloc(BUF_SIZE * sizeof(char));
		fscanf(input, "%100s", s);

		unsigned ip;
		fscanf(input, "%u", &ip);

		root = insert(ip, s, root);
	}

	FILE*output = fopen("output.txt", "w");
	int m;
	fscanf(input, "%d", &m);

	char*str = malloc(BUF_SIZE * sizeof(char));
	for (int i = 0; i < m; ++i) {
		fscanf(input, "%100s", str);

		fprintf(output, "%lld\n", find(str, root));
	}
	free(str);

	fclose(input);
	fclose(output);

	delete_tree(root);

	return 0;
}
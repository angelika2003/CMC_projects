#include <stdio.h>
#include <stdlib.h>

int a = 0;

struct tree {
	int key;
	int height;
	struct tree* left;
	struct tree* right;
};

int height(struct tree* root) {
	return root ? root->height : 0;
}

int max(int x, int y) {
	return x >= y ? x : y;
}

struct tree* LL_turn (struct tree* k2) {
/*	if (k2->key == 9) {
		a++;
	}*/

	printf("L(%d) ", k2->key);

	struct tree* k1;

	k1 = k2->left;
	k2->left = k1->right; /* k1 != NULL */
	k1->right = k2;

	k2->height = max (height (k2->left), height (k2->right)) + 1;
	k1->height = max (height (k1->left), k2->height) + 1;

	return k1;
}

struct tree* RR_turn(struct tree* k2) {
	printf("R(%d) ", k2->key);
	struct tree* k1;
	k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;

	k2->height = max (height (k2->right), height (k2->left)) + 1;
	k1->height = max (height (k1->right), k2->height) + 1;

	return k1;
}

struct tree* LR_turn (struct tree* k3) {
	k3->left = RR_turn(k3->left);

	return LL_turn(k3);
}

struct tree* RL_turn (struct tree* k3) {
	k3->right = LL_turn(k3->right);

	return RR_turn(k3);
}

struct tree* insert (int x, struct tree* t) {
	if (t == NULL) {
		t = (struct tree *)malloc (sizeof (struct tree));
		t->key = x;
		t->height = 1;
		t->left = t->right = NULL;
	} else if (x < t->key) {
		t->left = insert (x, t->left);
		if ((height (t->left) - height (t->right)) == 2) {
			if (x < t->left->key) {
				t = LL_turn (t);
			} else {
				t = LR_turn (t);
			}
		}
	} else if (x > t->key) {
		t->right = insert (x, t->right);
		if ((height (t->right) - height (t->left)) == 2) {
			if (x > t->right->key) {
				t = RR_turn (t);
			} else {
				t = RL_turn (t);
			}
		}
	}

	t->height = max (height (t->left), height (t->right)) + 1;
	return t;
}

void print_tree(struct tree* root) {
	if (root == NULL) {
		return;
	}
	print_tree(root->left);
	printf("%d(%d) ", root->key, root->height);
	print_tree(root->right);
}

int find(int x, struct tree* t) {
	if (t == NULL) {
		return -1;
	}

	if (x == t->key) {
		return t->key;
	}

	if (x > t->key) {
		return find(x, t->right);
	}

	return find(x, t->left);
}

int main(void) {
	struct Tree *root =NULL;
	root = insert(1, root);
	root = insert(2, root);
	root = insert(3, root);
	root = insert(9, root);
	root = insert(4, root);
	root = insert(5, root);
	root = insert(6, root);
	root = insert(7, root);
	root = insert(8, root);
	root = insert(10, root);

	return 0;



	for (int a1 = 1; a1 <= 10; a1++) {
		for (int a2 = 1; a2 <= 10; a2++) {
			for (int a3 = 1; a3 <= 10; a3++) {
				for (int a4 = 1; a4 <= 10; a4++) {
					for (int a5 = 1; a5 <= 10; a5++) {
						for (int a6 = 1; a6 <= 10; a6++) {
							for (int a7 = 1; a7 <= 10; a7++) {
								for (int a8 = 1; a8 <= 10; a8++) {
									for (int a9 = 1; a9 <= 10; a9++) {
										for (int a10 = 1; a10 <= 10; a10++) {

											if (a1 != a2 && a1 != a3 && a1 != a4 && a1 != a5 && a1 != a6 && a1 != a7 && a1 != a8 && a1 != a9 && a1 != a10) {
												if (a2 != a3 && a2 != a4 && a2 != a5 && a2 != a6 && a2 != a7 && a2 != a8 && a2 != a9 && a2 != a10) {
													if (a3 != a4 && a3 != a5 && a3 != a6 && a3 != a7 && a3 != a8 && a3 != a9 && a3 != a10) {
														if (a4 != a5 && a4 != a6 && a4 != a7 && a4 != a8 && a4 != a9 && a4 != a10) {
															if (a5 != a6 && a5 != a7 && a5 != a8 && a5 != a9 && a5 != a10) {
																if (a6 != a7 && a6 != a8 && a6 != a9 && a6 != a10) {
																	if (a7 != a8 && a7 != a9 && a7 != a10) {
																		if (a8 != a9 && a8 != a10) {
																			if (a9 != a10) {
																				root = NULL;
																				root = insert(a1, root);
																				root = insert(a2, root);
																				root = insert(a3, root);
																				root = insert(a4, root);
																				root = insert(a5, root);
																				root = insert(a6, root);
																				root = insert(a7, root);
																				root = insert(a8, root);
																				root = insert(a9, root);
																				root = insert(a10, root);
																				
																				if (a == 3) {
																					printf("%d %d %d %d %d %d %d %d %d %d\n", a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
																					
																				}

																				a = 0;
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}


	//printf("%d\n", find(50, root));

	//print_tree(root);


	return 0;
}
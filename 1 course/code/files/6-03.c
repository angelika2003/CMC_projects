#include <stdio.h>
#include <stdlib.h>

struct Node {
	int value;
	struct Node *next;
};

void print_list(struct Node *head) {
	while (head) {
		printf("%d ", head->value);
		head = head->next;
	}
}

void print_list_file(struct Node* head, char filename[]) {
	FILE *f = fopen(filename, "w");
	while (head) {
		fprintf(f, "%d ", head->value);
		head = head->next;
	}
	fclose(f);
}

struct Node *create_new_node(int value) {
	struct Node* new_node = (struct Node *)calloc(1, sizeof(struct Node));
	new_node->value = value;
	new_node->next = NULL;
	return new_node;
}

void bubble_sort(struct Node *head, int len) {
	for (int i = 0; i < len; ++i) {
		struct Node *cur = head;
		while (cur->next) {
			int v1 = cur->value;
			int v2 = cur->next->value;
			if (v1 > v2) {
				cur->next->value = v1;
				cur->value = v2;
			}
			cur = cur->next;
		}

	}
}

void delete(struct Node *head) {
	struct Node *next;
	while (head) {
		next = head->next;
		free(head);
		head = next;
	}
}

int main(void) {
	char filename[] = "input.txt";
	FILE *f1 = fopen(filename, "r");

	int number;
	fscanf(f1, "%d", &number);

	struct Node *head = create_new_node(number);
	struct Node *cur = head;

	int len = 1;

	while (fscanf(f1, "%d", &number) == 1) {
		cur->next = create_new_node(number);
		cur = cur->next;
		len++;
	}

	fclose(f1);

	bubble_sort(head, len);

	print_list_file(head, "output.txt");

	delete(head);

	return 0;
}
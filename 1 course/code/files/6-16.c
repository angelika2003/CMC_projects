#include <stdio.h>
#include <stdlib.h>

struct Node {
	int value;
	struct Node *next;
};

void print_list_file(struct Node *head, char filename[]) {
	FILE *f = fopen(filename, "w");
	while (head) {
		fprintf(f, "%d ", head->value);
		head = head->next;
	}
	fclose(f);
}

struct Node *create_new_node(int value) {
	struct Node *new_node = (struct Node *)calloc(1, sizeof(struct Node));
	new_node->value = value;
	new_node->next = NULL;
	return new_node;
}

struct Node *merge_sorted_lists(struct Node *head1, struct Node *head2) {
	struct Node *head = (head1->value <= head2->value) ? head1 : head2;
	struct Node *ans = head;
	if (head == head1) {
		head1 = head1->next;
	} else {
		head2 = head2->next;
	}

	while (head1 && head2) {

		int v1 = head1->value;
		int v2 = head2->value;

		if (v1 <= v2) {
			head->next = head1;
			head1 = head1->next;
		} else {
			head->next = head2;
			head2 = head2->next;
		}

		head = head->next;
	}

	if (head1 == NULL) {
		head->next = head2;
	} else {
		head->next = head1;
	}

	return ans;
}

struct Node *merge(struct Node *head, int len) {
	if (len == 1) {
		return head;
	}
	int part_len = len / 2;

	struct Node *head1 = head;
	part_len--;

	while (part_len) {
		head = head->next;
		part_len--;
	}
	struct Node *head2 = head->next;
	head->next = NULL;

	return merge_sorted_lists(merge(head1, len / 2 ), merge(head2, len - len / 2));
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

	int value;
	fscanf(f1, "%d", &value);
	struct Node *head = create_new_node(value);
	struct Node *cur = head;

	int len = 1;

	while (fscanf(f1, "%d", &value) == 1) {
		cur->next = create_new_node(value);
		cur = cur->next;
		len++;
	}

	fclose(f1);

	head = merge(head, len);

	print_list_file(head, "output.txt");

	delete(head);

	return 0;
}

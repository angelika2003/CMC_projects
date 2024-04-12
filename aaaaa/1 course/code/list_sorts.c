#include <stdio.h>
#include <stdlib.h>

struct Node {
	int value;
	struct Node* next;
};

void print_list(struct Node* head) {
	while (head) {
		printf("%d ", head->value);
		head = head->next;
	}
}

struct Node* create_new_node(int value) {
	struct Node* new_node = (struct Node*)calloc(1, sizeof(struct Node));
	new_node->value = value;
	new_node->next = NULL;
	return new_node;
}

void bubble_sort (struct Node* head, int len) {
	for (int i = 0; i < len; ++i) {
		struct Node*cur = head;
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

struct Node* merge_sorted_lists(struct Node * head1, struct Node * head2) {
	//if NULL...
	struct Node* head = (head1->value <= head2->value) ? head1 : head2;
	struct Node* ans = head;
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
	struct Node* head = create_new_node(15);
	head->next = create_new_node(6);
	head->next->next = create_new_node(1);
	head->next->next->next = create_new_node(11);
	head->next->next->next->next = create_new_node(2);

	head = merge(head, 5);

	print_list(head);

	return 0;
}

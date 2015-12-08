#include <stdio.h>
#include <malloc.h>
#define MAX 15

struct testCases {
	int list[MAX], n, r[MAX], rSize;
}cases[] = {
	{
		{ 1, 5, 3, 4, 2, 6 }, 6,{ 1, 2, 3, 4, 5, 6 }, 6
	},
	{
		{ -1 }, 0,{ -1 }, 0
	},
	{
		{ 1 }, 1,{ 1 }, 1
	},
	{
		{ 2, 1 }, 2,{ 1, 2 }, 2
	},
	{
		{ 1, 2 }, 2,{ 1, 2 }, 2
	},
	{
		{ 1, 2, 3 }, 3,{ 1, 2, 3 }, 3
	},
	{
		{ 2, 1, 3, 4, 6 }, 5,{ 1, 2, 3, 4, 6 }, 5
	}
};

struct node {
	int n;
	struct node *next;
};


void sort(struct node* head) {
	if (!head || !(head->next)) return;
	if (!(head->next->next)) {
		if (head->n > head->next->n) {
			int temp = head->n;
			head->n = head->next->n;
			head->next->n = temp;
		}
		return;
	}
	struct node* first = NULL;
	struct node* second = NULL;
	struct node *temp = head;
	while (temp->next->next) {
		if (temp->n > temp->next->n) {
			if (first) {
				second = temp->next;
				break;
			}
			else {
				first = temp;
			}
		}
		temp = temp->next;
	}
	if (!second) {
		// already sorted
		if (!first) return;
		second = first->next;
	}
	// swapping first and second
	int swap = first->n;
	first->n = second->n;
	second->n = swap;
}

// creates linked list of elements from array
struct node * createList(int *list, int n) {
	struct node * head = NULL;
	while (n--) {
		struct node *temp = (struct node *)malloc(sizeof(struct node));
		temp->next = head;
		temp->n = list[n];
		head = temp;
	}
	return head;
}

int compareLists(struct node * a, struct node * b) {
	while (a && b && a->n == b->n) {
		a = a->next;
		b = b->next;
	}
	return !(a || b);
}

void tester(int n) {
	int i;
	for (i = 0; i < n; i++) {
		struct node * list = createList(cases[i].list, cases[i].n);
		sort(list);
		if (compareLists(list, createList(cases[i].r, cases[i].rSize)))
			printf("PASS\n");
		else
			printf("FAIL\n");
	}
}

int main(void) {
	tester(7);
	getchar();
}
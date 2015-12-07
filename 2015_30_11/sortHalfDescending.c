#include <stdio.h>
#include <malloc.h>
#define MAX 15

struct testCases {
	int list[MAX], n, r[MAX], rSize;
}cases[] = {
	{
		{ 1, 2, 7, 20, 15, 10 }, 6,{ 1, 2, 7, 10, 15, 20 }, 6
	},
	{
		{ 1, 2, 7 }, 3,{ 1, 2, 7}, 3
	},
	{
		{ 20, 15, 10 }, 3,{ 10, 15, 20 }, 3
	},
	{
		{ 1, 1, 1 }, 3,{ 1, 1, 1 }, 3
	},
	{
		{ -1 }, 0,{ 1 }, 0
	},
	{
		{ 65535 }, 1,{ 65535 }, 1
	},
	{
		{ 1, 2 }, 2,{ 1, 2 }, 2
	},
	{
		{ 2, 1 }, 2,{ 1, 2 }, 2
	}
};

struct node {
	int n;
	struct node *next;
};

void reverse(struct node** head) {
	// exceptions
	if (!(*head) || !((*head)->next))
		return;

	// dividing list to first element and rest of list
	struct node *first = *head, *rest = (*head)->next;
	reverse(&rest);
	// reversing links
	first->next->next = first;
	first->next = NULL;
	*head = rest;
}

void sort(struct node **headRef) {
	struct node *head = *headRef;
	// handling exceptions
	// null or singlenode
	if (!head || !(head->next)) return;
	// two nodes
	if (!(head->next->next)) {
		if (head->n > head->next->n) {
			int temp = head->n;
			head->n = head->next->n;
			head->next->n = temp;
		}
		return;
	}
	// completely descending
	if (head->n > head->next->n) {
		reverse(&head);
		*headRef = head;
	}
	while (head->next->next && head->next->n <= head->next->next->n)
		head = head->next;
	//pointing max ascending's next to min descending's least and reverse descending
	struct node *temp = head ->next;
	while (temp->next) temp = temp->next;
	reverse(&(head->next));
	head->next = temp;
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
		sort(&list);
		if (compareLists(list, createList(cases[i].r, cases[i].rSize)))
			printf("PASS\n");
		else
			printf("FAIL\n");
	}
}

int main(void) {
	tester(8);
	getchar();
}
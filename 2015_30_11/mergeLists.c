#include <stdio.h>
#include <malloc.h>
#define MAX 15

struct testCases {
	int a[MAX], n1, b[MAX], n2, r[MAX], n;
}cases[] = {
	{
		{ 1, 2, 3, 4, 5 }, 5, { 1, 2, 3, 4, 5}, 5, { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5 }, 10
	},
	{
		{ 1, 3, 5, 7 }, 4,{ 2, 4, 6, 8 }, 4,{ 1, 2, 3, 4, 5, 6, 7, 8 }, 8
	},
	{
		{ 1, 2, 3, 4, 5, 6 }, 6,{ 1, 2, 3, 4, 5 }, 5,{ 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6 }, 11
	},
	{
		{ 1, 2, 3, 4, 5 }, 5,{ 1, 2, 2, 4, 5, 6 }, 6,{ 1, 1, 2, 2, 2, 3, 4, 4, 5, 5, 6 }, 11
	},
	{
		{ -5, -4, -3, -2, -1 }, 5,{ 0, 1, 2, 3, 4, 5 }, 6,{ -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5 }, 11
	},
	{
		{ 1 }, 1, {-1}, 0, { 1 }, 1
	},
	{
		{-1}, 0, { 1 }, 1, { 1 }, 1
	},
	{
		{-1}, 0, {-1}, 0, {-1}, 0
	}
};

struct node {
	int n;
	struct node *next;
};

struct node * merge(struct node * a, struct node *b) {
	struct node* result = NULL;
	// returning a list if otehr list is empty
	if (a == NULL)
		return b;
	if (b == NULL)
		return a;
	// if a is smaller, taking it as head and sorting the remaining list
	if (a->n <= b->n) {
		result = a;
		result->next = merge(a->next, b);
	}
	// if b is smaller, taking it as head and sorting the remaining list
	else {
		result = b;
		result->next = merge(a, b->next);
	}
	return result;
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
	for (i = 0; i < n; i++)
		if (compareLists(merge(createList(cases[i].a, cases[i].n1), createList(cases[i].b, cases[i].n2)), createList(cases[i].r, cases[i].n)))
			printf("PASS\n");
		else
			printf("FAIL\n");
}

int main(void) {
	tester(8);
	getchar();
}
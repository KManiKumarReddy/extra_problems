#include <stdio.h>
#include <malloc.h>

struct testCases {
	int n1, n2, r, ans;
} cases[] = {
	{
		3, 5, 5, 10
	},
	{
	3, 5, 7, 15	
	},
	{
		3, 5, 8, 18
	},
	{
		1, 5, 8, 8
	},
	{
		1, 1, 1, 1
	},
	{
		0, 0, 8, 0
	},
	{
		0, 1, 8, 7
	}
};

struct node {
	int n;
	struct node *next;
};


// merging without duplicates
struct node * merge(struct node * a, struct node *b) {
	struct node* result = NULL;
	// returning a list if otehr list is empty
	if (a == NULL)
		return b;
	if (b == NULL)
		return a;
	// if a is smaller, taking it as head and sorting the remaining list
	if (a->n < b->n) {
		result = a;
		result->next = merge(a->next, b);
	}
	// if b is smaller, taking it as head and sorting the remaining list
	else if(a->n > b->n) {
		result = b;
		result->next = merge(a, b->next);
	}
	else {
		result = b;
		result->next = merge(a->next, b->next);
	}
	return result;
}

struct node * createTable(int n, int r) {
	if (!n) {
		struct node *newNode = malloc(sizeof(struct node));
		newNode->next = NULL;
		newNode->n = 0;
		return newNode;
	}
	struct node * head = NULL;
	while (r) {
		struct node *temp = (struct node *)malloc(sizeof(struct node));
		temp->next = head;
		temp->n = n * r;
		head = temp;
		r--;
	}
	return head;
}

int findR(int n1, int n2, int r) {
	if (r <= 0 || n1 < 0 || n2 < 0)
		return -1;
	struct node * tab1 = createTable(n1, r);
	struct node * tab2 = createTable(n2, r);
	tab1 = merge(tab1, tab2);
	while (--r && tab1->next) tab1 = tab1->next;
	return tab1->n;
}

void tester(int n) {
	int i;
	for (i = 0; i < n; i++)
		if (findR(cases[i].n1, cases[i].n2, cases[i].r) == cases[i].ans)
			printf("PASS\n");
		else
			printf("FAIL\n");
}

int main(void) {
	tester(7);
	getchar();
}
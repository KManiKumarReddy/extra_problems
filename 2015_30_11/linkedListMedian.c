#include <stdio.h>
#include <malloc.h>
#define MAX 15

struct testCases {
	int list[MAX], n;
	double r;
}cases[] = {
	{
		NULL, 0, 0
	},
	{
		{ 1, 2, 3, 4, 5 }, 5, 3
	},
	{
		{ 1, 2, 3, 5, 5, 6 }, 6, (double)8/2
	},
	{
		{1}, 1, 1
	},
	{
		{1, 127}, 2, (double)64
	},
	{
		{-1, 2, 3 }, 3, (double)2
	},
	{
		{1, 2, 3, 4}, 4, (double)5/2
	},
	{
		{ 0, 0, 0, 0 }, 4, 0.0
	},
	{
		{ -1, -1, 1, 1 }, 4, 0.0
	}
};

struct node {
	int n;
	struct node *next;
};

double findMedian(struct node * head) {
	// handling excepions
	if (!head)
		return 0;
	// taking two pointers for traversal, one moves twice as fast as other
	struct node *traverseOnce = head, *traverseTwice = head;
	int count = 1;
	while (traverseTwice->next) {
		count++;
		traverseTwice = traverseTwice->next;
		if (traverseTwice->next) {
			count++;
			traverseTwice = traverseTwice->next;
			traverseOnce = traverseOnce->next;
		}
	}
	// if even number of items, returning mean of 2 middle elements
	return count & 1 ? traverseOnce->n : (double)(traverseOnce->n + traverseOnce->next->n) / 2;
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

void tester(int n) {
	int i;
	for (i = 0; i < n; i++)
		if (findMedian(createList(cases[i].list, cases[i].n)) == cases[i].r)
			printf("PASS\n");
		else
			printf("FAIL\n");
}

int main(void) {
	tester(9);
	getchar();
}
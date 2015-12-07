#include <stdio.h>
#include <malloc.h>
#define MAX 15

struct testCases {
	int list[MAX], n, r[MAX], rSize;
}cases[] = {
	{
		{ 1, 2, 2, 5, 4 }, 5,{ 4, 5, 2, 2, 1 }, 5
	},
	{
		{ 1, 2, 3, 4, 5 }, 5,{ 5, 4, 3, 2, 1 }, 5
	},
	{
		{ 1, 1, 1, 1, 1 }, 5,{ 1, 1, 1, 1, 1 }, 5
	},
	{
		{ -1 }, 0, { -1 }, 0
	},
	{
		{ -1 }, 1,{ -1 }, 1
	}
};

struct node {
	int n;
	struct node *next;
};

// reversing the Links after reaching end
void reverse1(struct node ** head, struct node *ptr) {
	// handling excepional cases
	if (!ptr || !(ptr->next)) {
		*head = ptr;
		return;
	}
	reverse1(head, ptr->next);
	struct node *temp = ptr->next;
	temp->next = ptr;
	ptr->next = NULL;
}

// reverse by using reverse at beginning
void reverse2(struct node** head)
{
	//handling exceptions
	if (!(*head) || !((*head)->next))
		return;

	// dividing list to first element and rest of list
	struct node *first = *head, *rest = (*head)->next;
	reverse2(&rest);
	// reversing links
	first->next->next = first;
	first->next = NULL;
	*head = rest;
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
		reverse1(&list, list);
		if (compareLists(list, createList(cases[i].r, cases[i].rSize)))
			printf("PASS\n");
		else
			printf("FAIL\n");
		list = createList(cases[i].list, cases[i].n);
		reverse2(&list);
		if (compareLists(list, createList(cases[i].r, cases[i].rSize)))
			printf("PASS\n");
		else
			printf("FAIL\n");
	}
}

int main(void) {
	tester(5);
	getchar();
}
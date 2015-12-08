#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct testCases {
	char filename[100];
	int n;
} cases[] = {
	{
		"text.txt", 5
	},
	{
		"text.txt", 15
	},
	{
		"text.txt", 16
	},
	{
		"text.txt", 1
	},
	{
		"text.txt", 0
	},
	{
		"text.txt", -1
	},
	{
		"tex.txt", 10
	}
};

void print(char *filename, int n) {
	// handling exceptions
	if (n < 0) {
		printf("Invalid input\n");
		return;
	}
	if (!n) return;
	FILE *in;
	if (!(in = fopen(filename, "r"))) {
		printf("Error opening the file\n");
		return;
	}
	int lines = 1;
	char s[100];
	char ch;

	while ((ch = fgetc(in)) != EOF) {
		if (ch == '\n')
			lines++;
	}
	if (n > lines) {
		printf("Invalid input\n");
		fclose(in);
		return;
	}
	lines = lines - n;
	fseek(in, 0, SEEK_SET);
	while (lines) {
		ch = fgetc(in);
		if (ch == '\n')
			lines --;
	}
	while (fgets(s, sizeof(s), in) != NULL) {
		printf("%s", s);
	}
	fclose(in);
}

void tester(int n) {
	while (n--) {
		printf("\nFor file name = %s and n = %d\n", cases[n].filename, cases[n].n);
		print(cases[n].filename, cases[n].n);
	}
}

int main(void) {
	tester(7);
	getchar();
}
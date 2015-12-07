#include <stdio.h>
#include <limits.h>

#define MAX 15

struct testCases {
    int arr[MAX], size, lres, rres, sum;
} cases[] = {
    {
        {1, 2, 3, -1, 4, 4, 5, -2, 6, 7},
        10,
        0, 9,
        29
    },
    {
        {-1, -1, -1, -1},
        4,
        0, 0,
        -1
    },
    {
        {-4, -1, -2, -3, -5, -4, 0},
        7,
        6, 6,
        0
    },
    {
        {-4, -1, -2, -3, -5, -4},
        6,
        1, 1,
        -1
    },
    {
        {8},
        1,
        0, 0,
        8
    },
    {
        {-4, -1, 2, -3, -5, -4},
        6,
        2, 2,
        2
    },
    {
        {1, 2, 2, 3, 4},
        5,
        0, 4,
        12
    },
    {
        {1, 2, -4, 5, -2},
        5,
        3, 3,
        5
    },
    {
        {1, 2, -1, 5, -2},
        5,
        0, 3,
        7
    }
};

//functionality
int maxSeq(int sequence[], int len, int * res1, int * res2) {
    int i, j, maxIndex = 0;
    // special case for all negatives / zeros
    for (i = 0; i < len; i ++)
        if(sequence[i] > 0)
            break;
        else if(sequence[i] > sequence[maxIndex])
            maxIndex = i;
    if(i == len) {
        *res1 = *res2 = maxIndex;
        return sequence[maxIndex];
    }
    int max = 0, tempMax = 0;
    int start = 0, end = -1;
    for (i = 0, j = 0; j < len; j++) {
        tempMax += sequence[j];
        if (tempMax < 0) {
            i = j + 1;
            tempMax = 0;
        }
        else if (tempMax > max) {
            max = tempMax;
            start = i;
            end   = j;
        }
    }
    
    if (start <= end && start >= 0 && end >= 0) {
        *res1 = start;
        *res2 = end;
        return max;
    } else {
        *res1 = 0;
        *res2 = 0;
        return sequence[0];
    }
}

void tester(int n) {
    int i, lres, rres, sum;
    for(i = 0; i < n; i ++) {
        sum = maxSeq(cases[i].arr, cases[i].size, &lres, &rres);
        if(rres == cases[i].rres && lres == cases[i].lres && sum == cases[i].sum)
            printf("PASS\n");
        else
            printf("FAIL\t%d %d %d\n", lres, rres, sum);
    }
}
int main(void) {
    tester(9);
    return 0;
}
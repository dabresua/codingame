#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

#define MAX_N  (100000)
#define MAX_PI (10000000)

int binarySearch(int a[], int item, int low, int high)
{
	if (high <= low)
		return (item > a[low])?  (low + 1): low;

	int mid = (low + high)/2;

	if(item == a[mid])
		return mid+1;

	if(item > a[mid])
		return binarySearch(a, item, mid+1, high);
	return binarySearch(a, item, low, mid-1);
}

void insertionSort(int a[], int n)
{
	int i, loc, j, k, selected;

	for (i = 1;i < n;++i)
	{
		j = i - 1;
		selected = a[i];

		// find location where selected sould be inseretd
		loc = binarySearch(a, selected, 0, j);

		// Move all elements after location to create space
		while (j >= loc)
		{
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = selected;
	}
}

int findClosest(int *pi, int N)
{
	int closest = MAX_PI;
	for(int i = 0;i < N-1;i++){
		int cij = pi[i+1]-pi[i];
		if(cij < closest){
			closest = cij;
		}
	}
	return closest;
}

int main()
{
	int N;
	scanf("%d", &N);
	int pi[N];

	int max = 0, min = MAX_PI;
	fprintf(stderr, "N %d\n", N);
	for (int i = 0;i < N;i++){
		scanf("%d", &pi[N-i-1]);
		fprintf(stderr, "pi %d\n", pi[N-i-1]);
		if(min > pi[i])
			min = pi[i];
		if(max < pi[i])
			max = pi[i];
	}
	fprintf(stderr, "min %d, max %d\n", min, max);

	insertionSort(pi, N);

	for (int i = 0;i < N;i++){
		fprintf(stderr, "PI PI %d\n", pi[i]);
	}

	// Write an answer using printf(). DON'T FORGET THE TRAILING \n
	// To debug: fprintf(stderr, "Debug messages...\n");

	printf("%d\n", findClosest(pi, N));

	return 0;
}

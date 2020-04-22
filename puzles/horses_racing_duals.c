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

int main()
{
	int N;
	scanf("%d", &N);
	int pi[N];
	int min_diff = MAX_PI;
	fprintf(stderr, "N %d\n", N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &pi[i]);
		fprintf(stderr, "pi %d\n", pi[i]);
		int min = MAX_PI;
		for(int j = 0; j < i; j++) {
			int mij = (pi[j] > pi[i])?(pi[j] - pi[i]):(pi[i] - pi[j]);
			if(mij < min) {
				min = mij;
			}
		}
		if(min < min_diff) {
			min_diff = min;
		}
		if(min_diff == 1)
			break;
	}

	// Write an answer using printf(). DON'T FORGET THE TRAILING \n
	// To debug: fprintf(stderr, "Debug messages...\n");

	printf("%d\n", min_diff);

	return 0;
}

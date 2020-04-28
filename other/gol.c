#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define W_DEF 80
#define H_DEF 20

#define GOL_BOOL_FMT "%c"
#define GOL_BOOL_PRM(_b) (_b)?'x':' '

static void cell_set(unsigned int *world, int c, int f, int w, int h, bool value)
{
	if(c > w || f > h) {
		fprintf(stderr, "That doesn't fit\n");
		return;
	}
	int index = (f*w+c)/(8*sizeof(int));
	int rl = 8*sizeof(int)-1-(f*w+c)%(8*sizeof(int));
	if(value) {
		world[index] |= 1 << rl;
	} else {
		world[index] &= 0 << rl;
	}
}

static void generate_world(unsigned int *world, int w, int h)
{
	for (unsigned int i = 0; i < w; i++) {
		for (unsigned int j = 0; j < h; j++) {
			if(rand() < RAND_MAX / 10) {
				cell_set(world, i, j, w, h, true);
			}
		}
	}
}

static void print_world(unsigned int *world, unsigned int w, unsigned int h)
{
	int counter = 0;
	for (int i = 0; i < w*h/(8*sizeof(int)); i++) {
		//printf("--%d:%x--\n", i, world[i]);
		for (int j = 8*sizeof(int); j > 0 ; j--) {
			printf("%c", (world[i]&(1<<(j-1))) > 0?'x':'-');
			counter++;
			if(counter == w) {
				counter = 0;
				printf("|\n");
			}
		}
		//printf("%x ", world[i]);
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	unsigned int w = W_DEF;
	unsigned int h = H_DEF;
	if(argc > 2) {
		w = atoi(argv[1]);
		h = atoi(argv[2]);
	}
	printf("%ld\n", sizeof(int));
	printf("GOL %d %d\n", w, h);

	long len = w*h/(8*sizeof(int));
	printf("%ld\n", len);
	unsigned int world[len];
	for (int i = 0; i < len; i++) {
		world[i] = 0;
	}
	generate_world(world, w, h);
	/*
	cell_set(world, 0, 0, w, h, true);
	cell_set(world, 1, 0, w, h, true);
	cell_set(world, 5, 0, w, h, true);
	cell_set(world, 31, 0, w, h, true);
	cell_set(world, 32, 0, w, h, true);

	cell_set(world, 0, 1, w, h, true);
	cell_set(world, 1, 1, w, h, true);
	cell_set(world, 5, 1, w, h, true);
	cell_set(world, 31, 1, w, h, true);
	cell_set(world, 32, 1, w, h, true);
	printf("%x\n", world[0]);
	*/

	print_world(world, w, h);

	return 0;
}

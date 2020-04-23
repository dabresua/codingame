#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

#define DEBUG 1
#define DEBUG_VERBOSE 1

#define TO_UPPER(_c) (_c)+'A'-'a'

typedef struct ext_mime_t {
	char ext[12];
	char mt[51+1];
	int ext_len;
	unsigned long weigth;
} ext_mime_t;

#ifdef DEBUG
#define EXT_MIME_FMT "len [%d], w [%lu], ext[%s], mime[%s]"
#define EXT_MIME_PRM(_em) (_em)->ext_len, (_em)->weigth, (_em)->ext, (_em)->mt
#endif /* DEBUG */

int binarySearch(ext_mime_t a[], ext_mime_t item, int low, int high)
{
	if (high <= low)
		return (item.weigth > a[low].weigth)?  (low + 1): low;

	int mid = (low + high)/2;

	if(item.weigth == a[mid].weigth)
		return mid+1;

	if(item.weigth > a[mid].weigth)
		return binarySearch(a, item, mid+1, high);
	return binarySearch(a, item, low, mid-1);
}

void insertionSort(ext_mime_t a[], int n)
{
	int i, loc, j, k;
	ext_mime_t selected;

	for (i = 1;i < n;++i)
	{
		j = i - 1;
		ext_mime_cpy(&selected, &a[i]);

		// find location where selected sould be inseretd
		loc = binarySearch(a, selected, 0, j);

		// Move all elements after location to create space
		while (j >= loc)
		{
			ext_mime_cpy(&a[j+1], &a[j]);
			j--;
		}
		ext_mime_cpy(&a[j+1], &selected);
	}
}

void ext_mime_cpy(ext_mime_t *to, const ext_mime_t *from) {
	to->ext_len = from->ext_len;
	to->weigth = from->weigth;
	memcpy(to->ext, from->ext, 11);
	memcpy(to->mt, from->mt, 51);
}

void ext_mime_init(ext_mime_t *em, char *ext, char *mt)
{
	em->ext_len = 0;
	em->weigth = 0;
	while(em->ext_len < 12) {
		if(ext[em->ext_len] == 0)
		break;
		if(ext[em->ext_len] > 'Z') {
			em->ext[em->ext_len] = TO_UPPER(ext[em->ext_len]);
		} else {
			em->ext[em->ext_len] = ext[em->ext_len];
		}
		em->weigth += (em->ext[em->ext_len]-'0') << (5*em->ext_len);
		em->ext_len++;
	}
	em->ext[em->ext_len] = 0;
	memcpy(&em->mt, mt, 51);
}

int ext_extractor(const char *in, char *out, unsigned long *w)
{
	int end = 0;
	while(end < 257) {
		if(in[end] == '\n') {
			break;
		}
		end++;
	}
	if(end == 257)
	    return 0;

	int init = end-1;
	while(init > 0) {
		if(in[init] == '.')
		break;
		init--;
	}
	if(init == 0 && in[0] != '.')
	    return 0;

	int i_o = 0;
	for(int i = init+1; i < end; i++) {
		if(in[i] > 'Z') {
			out[i_o] = TO_UPPER(in[i]);
		} else {
			out[i_o] = in[i];
		}
		*w += (out[i_o]-'0') << (5*i_o);
		i_o++;
	}
	return (end-init-1);
}
#if 0
bool ext_mime_cmp(ext_mime_t *em, char *ext, int ext_len, unsigned long w)
{
	if(ext_len != em->ext_len || w != em->weigth)
	return false;
	/*
	for(int i = 0; i < ext_len; i++) {
	if((ext[i] != em->ext[i]))
	return false;
	}
	*/
	return true;
}
#endif /* 0 */

int max_on_table(int N)
{
	int ret = 1;
	while((1 << ret) < N) {
		ret++;
	}
	return ret;
}

int main()
{
	// Number of elements which make up the association table.
	int N;
	scanf("%d", &N);
	// Number Q of file names to be analyzed.
	int Q;
	scanf("%d", &Q);
	//fprintf(stderr, "N %d, Q %d\n", N, Q);

	ext_mime_t em[N];
	for (int i = 0; i < N; i++) {
		// file extension
		char EXT[11];
		// MIME type.
		char MT[51];
		scanf("%s%s", EXT, MT); fgetc(stdin);
		ext_mime_init(&em[i], EXT, MT);
	}

	insertionSort(em, N);
	unsigned long min = em[0].weigth;
	unsigned long max = em[N-1].weigth;
	unsigned long step = (max-min)/N;

	#ifdef DEBUG
	for (int i = 0; i < N; i++) {
		fprintf(stderr, "em[%d]: " EXT_MIME_FMT "\n", i, EXT_MIME_PRM(&em[i]));
	}
	fprintf(stderr, "min %lu, max %lu, step %lu\n", min, max, step);
	#endif /* DEBUG */

	for (int i = 0; i < Q; i++) {
		// One file name per line.
		char FNAME[257];
		fgets(FNAME, 257, stdin);
		#ifdef DEBUG
		fprintf(stderr, "FNAME [%s]\n", FNAME);
		#endif /* DEBUG */

		char ext[12];
		long w = 0;
		int len = ext_extractor(FNAME, ext, &w);
		#ifdef DEBUG
		fprintf(stderr, "len %d, w %ld, ext %s\n", len, w, ext);
		#endif /* DEBUG */
		if(len > 0 && w >= min && w <= max) {
		    unsigned long index = (w-min)/(step+1);
		    #ifdef DEBUG_VERBOSE
		    fprintf(stderr, "Starts with %lu\n", index);
			#endif /* DEBUG_VERBOSE */
		    bool up = false;
		    bool found = false;
		    int wi = em[index].weigth;
		    if(wi == w) {
					#ifdef DEBUG_VERBOSE
					fprintf(stderr, "Found!!! %s\n", em[index].mt);
					#endif /* DEBUG_VERBOSE */
					printf("%s\n", em[index].mt);
					found = true;
		    } else if(wi < w) {
		        //up
		        index++;
		        #ifdef DEBUG_VERBOSE
    		    fprintf(stderr, "Next up %d\n", index);
    			#endif /* DEBUG_VERBOSE */
		        while(index < N) {
		            wi = em[index].weigth;
		            if(wi == w) {
    					#ifdef DEBUG_VERBOSE
    					fprintf(stderr, "Found!!! %s\n", em[index].mt);
    					#endif /* DEBUG_VERBOSE */
    					printf("%s\n", em[index].mt);
					    found = true;
    					break;
		            } else if(wi > w) {
		                found = false;
		                break;
		            } else {
		                index++;
		            }
		        }
		    } else {
		        //down
		        index--;
		        #ifdef DEBUG_VERBOSE
    		    fprintf(stderr, "Next down %d\n", index);
    			#endif /* DEBUG_VERBOSE */
		        while(index >= 0) {
		            wi = em[index].weigth;
		            if(wi == w) {
    					#ifdef DEBUG_VERBOSE
    					fprintf(stderr, "Found!!! %s\n", em[index].mt);
    					#endif /* DEBUG_VERBOSE */
    					printf("%s\n", em[index].mt);
    					found = true;
    					break;
		            } else if(wi < w) {
		                found = false;
		                break;
		            } else {
		                index--;
		            }
		        }
		    }
			if(!found) {
				#ifdef DEBUG_VERBOSE
				fprintf(stderr, "---\n");
				#endif /* DEBUG_VERBOSE */
				printf("UNKNOWN\n");
			}
		} else {
			printf("UNKNOWN\n");
		}
	}

	// Write an answer using printf(). DON'T FORGET THE TRAILING \n
	// To debug: fprintf(stderr, "Debug messages...\n");


	// For each of the Q filenames, display on a line the corresponding MIME type. If there is no corresponding type, then display UNKNOWN.
	//printf("UNKNOWN\n");

	return 0;
}

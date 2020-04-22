#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

#define TO_UPPER(_c) (_c)+'A'-'a'

typedef struct ext_mime_t {
    char ext[12];
    char mt[51+1];
    int ext_len;
    unsigned long weigth;
} ext_mime_t;

void ext_mime_cpy(ext_mime_t *to, const ext_mime_t *from) {
    to->ext_len = from->ext_len;
    to->weigth = from->weigth;
    //fprintf(stderr, "len, %d\n", to->ext_len);
    //memcpy(to->ext, from->ext, to->ext_len);
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

    ext_mime_t unsorted[N];
    for (int i = 0; i < N; i++) {
        // file extension
        char EXT[11];
        // MIME type.
        char MT[51];
        scanf("%s%s", EXT, MT); fgetc(stdin);
        ext_mime_init(&unsorted[i], EXT, MT);
        //fprintf(stderr, "EXT[%s], MT[%s], len %d, w %lu\n",
        //        unsorted[i].ext, unsorted[i].mt, unsorted[i].ext_len,
        //        unsorted[i].weigth);
    }
    // TODO: sort by weigth
	int max = max_on_table(N);
	//fprintf(stderr, "max %d\n", max);
    ext_mime_t em[(1 << max)];
    bool sorted[N];
    for(int i = 0; i < N; i++) {
        unsigned int min = -1;
        int min_index = N;
        for(int j = 0; j < N; j++) {
            if(!sorted[j] && unsorted[j].weigth < min) {
                min_index = j;
                min = unsorted[j].weigth;
            }
        }
        sorted[min_index] = true;
        ext_mime_cpy(&em[i], &unsorted[min_index]);
        //fprintf(stderr, "%d: %lu[%s]\n", i, em[i].weigth, em[i].ext);
    }

    for (int i = 0; i < Q; i++) {
        // One file name per line.
        char FNAME[257];
        fgets(FNAME, 257, stdin);
        //fprintf(stderr, "FNAME [%s]\n", FNAME);

        char ext[12];
        long w = 0;
        int len = ext_extractor(FNAME, ext, &w);
        if(len > 0) {
            //fprintf(stderr, "ext %lu:[%s]\n", w, ext);
			int count = 1;
			int index = (1 << max)/(1 << count);
			bool found = false;
            while(count <= max) {
				//fprintf(stderr, "index %d\n", index-1);
                if(w == em[index-1].weigth) {
                    printf("%s\n", em[index-1].mt);
					found = true;
                    break;
                } else if(w == em[index].weigth) {
                    printf("%s\n", em[index].mt);
					found = true;
                    break;
                } else if(w > em[index-1].weigth) {
					count++;
					index+= (1 << max)/(1 << count);
                } else {
					count++;
					index-= (1 << max)/(1 << count);
                }
            }
            if(!found) {
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

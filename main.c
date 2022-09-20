






//#include "main2.h"
//#include "main3.h"
#include "main4.h"

#include "snglist.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct test {
    int val;
    char ch;
} test_t;


void free_func(void *d) {
    fflush(stdout);
    free((int *)d);
}

int cmp_func(void *cmp1, void *cmp2) {
    return  (*((int *)cmp1) == *((int *)cmp2));
}

int main (int argc, char** argv)
{

    sl_list_t *stlist;
    list_sl_init(stlist);



    int *iptr;
    for(int i = 0; i < 5; i++) {
        iptr = (int *)malloc(sizeof(int));
        *iptr = i;
        list_sl_push(stlist, iptr);
    }

    int tcmp = 8;

    void *d;
    list_find_func_data(stlist, &tcmp, cmp_func, d);
    printf("%d\n", *((int *)d));

    list_sl_func_free(stlist, free_func);

    list_sl_destroy(stlist);




    return 0;
}

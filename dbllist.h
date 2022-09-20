

#ifndef DBLLIST_H
#define DBLLIST_H

#include <malloc.h>
#include "sdlist.h"



typedef struct double_link_list_node {
    void *data;
    struct double_link_list_node *next;
    struct double_link_list_node *prev;
} dl_node_t;



typedef struct double_link_list {
    unsigned long cnt;
    dl_node_t *head;
    dl_node_t *tail;
} dl_list_t;





#define list_dl_init(l) LIST_DL_INIT(l)
#define LIST_DL_INIT(l) \
            l = (dl_list_t *)malloc(sizeof(dl_list_t));\
            l->cnt = 0; \
            l->head = NULL; \
            l->tail = NULL;




#define list_dl_destroy(l) LIST_DL_DESTROY(l)
#define LIST_DL_DESTROY(l) \
            free(l); \
            l = NULL;





#endif /* DBLLIST_H */

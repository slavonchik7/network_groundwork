

#ifndef SNGLIST_H
#define SNGLIST_H


#include <malloc.h>
#include <stdlib.h>
#include "sdlist.h"


typedef struct single_link_list_node {
    void *data;
    struct single_link_list_node *next;
} sl_node_t;



typedef struct single_link_list {
    unsigned long cnt;
    sl_node_t *head;
} sl_list_t;


/*
 * allocates memory under l->head and fills with initial values
 */
#define list_sl_init(l) LIST_SL_INIT(l)
#define LIST_SL_INIT(l) \
            l = (sl_list_t *)malloc(sizeof(sl_list_t));\
            l->cnt = 0; \
            l->head = NULL;


/*
 * free the memory of the pointer l->head
 */
#define list_sl_destroy(l) LIST_SL_DESTROY(l)
#define LIST_SL_DESTROY(l) \
            free(l); \
            l = NULL;




#define list_sl_push(l, dptr) LIST_SL_PUSH(l, dptr)
#define LIST_SL_PUSH(l, dptr) \
            do { \
                sl_node_t *m = (sl_node_t *)malloc(sizeof(sl_node_t)); \
                if ( !m ) \
                    break; \
                m->data = dptr; \
                m->next = NULL; \
                if (l->head) { \
                    sl_node_t *pos = l->head; \
                    while(pos->next) \
                        pos = pos->next; \
                    pos->next = m; \
                } else \
                    l->head = m; \
                ++(l->cnt); \
            } while(0)



/*
 * the func function is called to which the void * pointer is passed,
 * then the memory of the node that stored void *data is cleared
 */
#define list_sl_func_free(l, func) LIST_SL_FUNC_FREE(l, func)
#define LIST_SL_FUNC_FREE(l, func) \
            do { \
                sl_node_t *pos = l->head; \
                sl_node_t *next; \
                while( pos ) { \
                    next = pos->next; \
                    func(pos->data); \
                    free(pos); \
                    pos = next; \
                } \
                l->head = NULL; \
                pos = NULL; \
            } while(0)



#define list_sl_remove(l, psrch, pres) LIST_SL_REMOVE(l, psrch, pres)
#define LIST_SL_REMOVE(l, psrch, pres) \
            do { \
                sl_node_t *prev = NULL; \
                if ( (pres = l->head) ) { \
                    if ( pres == psrch ) { \
                        l->head = pres->next; \
                    } else { \
                        pres = pres->next; \
                        while ( pres ) { \
                            if ( pres == psrch ) { \
                                prev->next = pres->next; \
                                break; \
                            } \
                            prev = pres; \
                            pres = pres->next; \
                        } \
                    } \
                    if ( pres ) \
                        --(l->cnt); \
                } \
            } while(0)


                /* for (pres = (l->head); (pres != NULL) || (pres != psrch); pres = pres->next) */


/*
 * the definition finds a node of type sl_node_t * with a field value equal to pdata,
 * which needs to be excluded, by calling func(), which should return 1,
 * if the value of the data field of the current node should be excluded from the list,
 * at the end press will point to the node of the list that was excluded, if such was found,
 * otherwise on NULL
 */
#define list_sl_func_remove(l, pdata, pres, func) LIST_SL_FUNC_REMOVE(l, pdata, pres, func)
#define LIST_SL_FUNC_REMOVE(l, pdata, pres, func) \
            do { \
                sl_node_t *prev = NULL; \
                if ( (pres = l->head) ) { \
                    if ( func(pdata, pres->data) ) { \
                        l->head = pres->next; \
                    } else { \
                        pres = pres->next; \
                        while (pres) { \
                            if ( (func(pdata, pres->data)) ) {\
                                prev->next = pres->next; \
                                break; \
                            } \
                            prev = pres; \
                            pres = pres->next; \
                        } \
                    } \
                    if ( pres ) \
                        --(l->cnt); \
                } \
            } while(0)




#define node_sl_func_free(pnode, func) NODE_SL_FUNC_FREE(pnode, func)
#define NODE_SL_FUNC_FREE(pnode, func) \
            do { \
                func(pnode->data); \
                pnode->data = NULL; \
                free(pnode); \
                pnode = NULL; \
            } while (0)




#endif /* SNGLIST_H */

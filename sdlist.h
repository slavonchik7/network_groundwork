


#ifndef SDLIST_H
#define SDLIST_H

/* (struct foobar *) (((char *) &tmp.boo) - ((unsigned long) &((struct foobar *)0)->boo))); */


#define list_for_each(l, pos)  for (pos = (l->head); pos != NULL; pos = pos->next)



/*
 * the func function is called to which void * dptr and
 * void *data of each of the nodes are passed
 * will return NULL if it could not be found or void data
 */
#define list_find_func_data(l, dptr, func, pres) \
            do { \
                pres = NULL; \
                for (sl_node_t *pos = (l->head); (pos != NULL); pos = pos->next) \
                    if ( func(dptr, pos->data) ) \
                        pres = pos->data; \
            } while(0)



#if 0
static inline void *list_sl_find_data(sl_list_t *l, void *dptr, (int) func(void *, void *)) {
    void *pres = NULL; \
    for (sl_node_t *pos = l->head; pos != NULL; pos = pos->next) \
        if ( func(dptr, pos->data) ) \
            pres = pos->data; \

    return pres;
}
#endif // 0



#endif /* SDLIST_H */

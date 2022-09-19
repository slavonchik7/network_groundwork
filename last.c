

#include "last.h"



/*
 *the variable stores the value of the last descriptor
 * that was used in any of the wrappers function
 */
static MYSQL *last_mysql_operation_handle;


#if 1
MYSQL * get_last_mysql_oper_handle() {
    return last_mysql_operation_handle;
}

void set_last_mysql_oper_handle(MYSQL *handle) {
    last_mysql_operation_handle = handle;
}
#endif

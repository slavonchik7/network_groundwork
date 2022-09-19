


#ifndef LAST_H
#define LAST_H

#include <mysql/mysql.h>




/*
 * returns value last_mysql_operation_handle
 */
MYSQL * get_last_mysql_oper_handle();

/*
 * set last_mysql_operation_handle
 */
void set_last_mysql_oper_handle();


#endif /* LAST_H */


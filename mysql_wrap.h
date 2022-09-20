
#ifndef MYSQL_WRAP
#define MYSQL_WRAP

#include <mysql/mysql.h>

#define UNKNOW_ERROR_MSG ("unknow error")

/*
 * the function checks the input values, calls mysql_query(),
 * and then calls set_last_mysql_oper_handle()
 */
int Mysql_query(MYSQL *mysql_sock, const char *q);



unsigned int Mysql_query_store_res(MYSQL *mysql_sock, const char *q, MYSQL_RES **svres);

/*
 * the function checks the value returned by mysql_error and
 * returns UNKNOW_ERROR_MSG if mysql_error returned an empty string
 */
const char *Mysql_error(MYSQL *mysql_sock);




#endif /* MYSQL_WRAP */


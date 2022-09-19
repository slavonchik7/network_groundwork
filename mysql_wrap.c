


#include "mysql_wrap.h"
#include "msgee.h"
#include <assert.h>
#include <mysql/errmsg.h>
#include "last.h"

int Mysql_query(MYSQL *mysql_sock, const char *q) {
    int qres;

    assert(mysql_sock && q);

    if ( (qres = mysql_query(mysql_sock, q)) != 0 ) {
//        mysql_close(mysql_sock);
//        EXIT_WITH_LOG_ERROR(NULL, NULL, Mysql_error(mysql_sock), qres);
    }

    set_last_mysql_oper_handle(mysql_sock);

    return qres;
}


const char *Mysql_error(MYSQL *mysql_sock) {

    assert(mysql_sock);

    const char *estr = mysql_error(mysql_sock);

    if (*estr == '\0')
        return UNKNOW_ERROR_MSG;

//    last_mysql_operation_handle = mysql_sock;

    return estr;
}



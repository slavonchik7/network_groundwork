


#include "mysql_wrap.h"
#include "msgee.h"
#include <assert.h>
#include <mysql/errmsg.h>
#include "last.h"
#include "mysql_errdef.h"

int Mysql_query(MYSQL *mysql_sock, const char *q) {
    int qres;

    assert(mysql_sock && q);

    if ( (qres = mysql_query(mysql_sock, q)) != 0 ) {
        mysql_close(mysql_sock);
        MYSQL_EXIT_WITH_LOG_ERROR(NULL, NULL);
    }

    set_last_mysql_oper_handle(mysql_sock);

    return qres;
}


unsigned int Mysql_query_store_res(MYSQL *mysql_sock, const char *q, MYSQL_RES **svres) {
    unsigned int nfields;
    unsigned int nrows;

    assert(svres);

    Mysql_query(mysql_sock, q);


    if ( !(*svres = mysql_store_result(mysql_sock)) ) {
        /* query does return data */
        mysql_close(mysql_sock);
        MYSQL_EXIT_WITH_LOG_ERROR(NULL, NULL);
    }

    /* if nfields == 0
     * query does not return data
     * (it was not a SELECT) */
    nfields = mysql_field_count(mysql_sock);

    return nfields;
}


const char *Mysql_error(MYSQL *mysql_sock) {

    assert(mysql_sock);

    const char *estr = mysql_error(mysql_sock);

    if (*estr == '\0')
        return UNKNOW_ERROR_MSG;

//    last_mysql_operation_handle = mysql_sock;

    return estr;
}



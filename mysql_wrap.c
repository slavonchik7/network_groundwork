


#include "mysql_wrap.h"
#include "msgee.h"
#include <assert.h>
#include <mysql/errmsg.h>
#include "last.h"
#include "mysql_errdef.h"

int Mysql_query(MYSQL *mysql_sock, const char *q) {
    int qres;

    assert(mysql_sock);
    assert(q);

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

    return estr;
}


MYSQL_ROW Mysql_fetch_row(MYSQL_RES *res)  {
    MYSQL_ROW row;

    assert(res);

    if ( !(row = mysql_fetch_row(res)) ) {
//        const char *errmsg = mysql_error();
    }

    return row;
}

MYSQL_RES *Mysql_store_result(MYSQL *sql) {
    MYSQL_RES *res;

    assert(sql);

    if ( !(res = mysql_store_result(sql)) ) {
        const char *errmsg = mysql_error(sql);

        /* an error may have occurred */
        if ( *errmsg ) {
            int err = (int)mysql_errno(sql);

            mysql_close(sql);
            EXIT_WITH_LOG_ERROR(NULL, NULL, errmsg, err);
        }
    }

    return res;
}













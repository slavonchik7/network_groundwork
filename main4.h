

#ifndef MAIN4_H
#define MAIN4_H

#include <stdio.h>
#include <mysql/mysql.h>


#include "mysql_wrap.h"
#include "msgdefs.h"
#include "msgee.h"
#include "mysql_errdef.h"

#define UNAME "christmas"
#define UPASS "Camikadze228!"
#define UDB "capi_db"

#undef mysql_query
#define mysql_query(mysql, q) Mysql_query(mysql, q)

#undef finish_with_error
#define finish_with_error(sock) MYSQL_EXIT_WITH_LOG_ERROR(exit_mysql, sock)

void exit_mysql(void *d) {
    mysql_close((MYSQL *)d);
    printf("i closed\n");
}

int main4()
{

    MYSQL *con = mysql_init(NULL);
    uint nfields;
    int status;

    if (mysql_real_connect(con, "localhost", UNAME, UPASS,
          UDB, 0, NULL, CLIENT_MULTI_STATEMENTS) == NULL)
    {
        EXIT_WITH_LOG_ERROR(exit_mysql, con, Mysql_error(con), -4);
    }


    #if 0
    nfields = Mysql_query_store_res(con,
            "SELECT name FROM cars WHERE id=2;\
            SELECT name FROM cars WHERE id=3;SELECT name FROM cars WHERE id=6",
            &res);
    #endif // 0
      if (mysql_query(con, "SELECT name FROM cars WHERE id=2;\
            SELECT name FROM cars WHERE id=3; \
            SELECT name FROM cars WHERE id=6"))
      {
          finish_with_error(con);
      }

    do {
        MYSQL_RES *result = mysql_store_result(con);

        if (result == NULL)
        {
          finish_with_error(con);
        }

        MYSQL_ROW row = mysql_fetch_row(result);

        printf("%s\n", *row);

        mysql_free_result(result);

        status = mysql_next_result(con);

        if (status > 0) {
          finish_with_error(con);
        }

    } while(status == 0);

    mysql_close(con);

    return 0;
}


#endif /* MAIN2_H */

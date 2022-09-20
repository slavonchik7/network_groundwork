

#ifndef MAIN3_H
#define MAIN3_H

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

int main3()
{

    MYSQL *con = mysql_init(NULL);
    MYSQL_RES *res;
    uint nfields;
    MYSQL_FIELD *field; /* information about fields names */
    MYSQL_ROW *row;

    if (con == NULL)
    {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
    }

    if (mysql_real_connect(con, "localhost", UNAME, UPASS,
          UDB, 0, NULL, 0) == NULL)
    {
        EXIT_WITH_LOG_ERROR(exit_mysql, con, Mysql_error(con), -4);
    }

    nfields = Mysql_query_store_res(con, "SELECT * FROM cars LIMIT 3", &res);



    while ( (field = mysql_fetch_field(res)) )
        printf("%s ", field->name);
    printf("\n");

    while ( (row = mysql_fetch_row(res)) ) {
        for (int i = 0; i < nfields; i++, row++) {
            printf("%s ", *row);
        }
        printf("\n");
    }

    printf("\n");

    mysql_free_result(res);
    mysql_close(con);

    return 0;
}


#endif /* MAIN2_H */




#ifndef MAIN1_H
#define MAIN1_H




#include <stdio.h>
#include <stddef.h>
//#include <assert.h>


#include <mysql/mysql.h>
#include <mysql/client_plugin.h>
#include <mysql/my_list.h>
#include "mysql_wrap.h"


#include "msgdefs.h"
#include "msgee.h"
#include "dbgassrt.h"
#include "mysql_errdef.h"

#define UNAME "christmas"
#define UPASS "Camikadze228!"
#define UDB "capi_db"

MYSQL mysql;
MYSQL_RES *res;
MYSQL_ROW row;






void finish_with_error(MYSQL *mysql_sock) {
    const char *estr = mysql_error(mysql_sock);

    if (estr)
        LOG_ERR(estr);

    mysql_close(mysql_sock);
    exit(1);
}

void exit_mysql(void *d) {
    mysql_close((MYSQL *)d);
    printf("i closed\n");
}

char *alock() {
    char *b;
    b = malloc(10);
    sprintf(b, "hello");
    b[9] = 0;
    return b;
}

void exiterr(int exitcode)
{
  fprintf(stderr, "%s\n", mysql_error(&mysql));
  exit(exitcode);
}

int main1()
{

    MYSQL *con = mysql_init(NULL);

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


//    if (Mysql_query(con, "SELECT * FROM cars") ) {
//        MYSQL_EXIT_WITH_LOG_ERROR(exit_mysql, con);
//    }

    MYSQL_RES *res;

    int res_fields_num;
    int res_field_count;
//    if ( !(res = mysql_store_result(con)) ) {
//        MYSQL_EXIT_WITH_LOG_ERROR(exit_mysql, con);
//    }

    res_field_count = mysql_field_count(con);

    res_fields_num = Mysql_query_store_res(con, "SELECT * FROM cars", &res);

    printf("fields count: %d\n", res_field_count);
    printf("fields num: %d\n", res_fields_num);
    printf("rows num: %lu\n", mysql_num_rows(res));
    printf("id : %d\n", mysql_insert_id(con));


    MYSQL_ROW row;
    while ( (row = mysql_fetch_row(res)) ) {
        for (int i = 0; i < res_fields_num; i++, row++) {
            printf("%s ", *row ? *row : "NULL");
        }
        printf("\n");
    }


    mysql_free_result(res);
    mysql_close(con);

    return 0;
}










#endif /* MAIN1_H */





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

int main()
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
//      finish_with_error(con);
    }

    #if 0
    if (mysql_query(con, "DROP TABLE IF EXISTS cars")) {
      finish_with_error(con);
    }

    if (mysql_query(con, "CREATE TABLE cars(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(255), price INT)")) {
      finish_with_error(con);
    }

    if (mysql_query(con, "INSERT INTO cars VALUES(1,'Audi',52642)")) {
      finish_with_error(con);
    }

    if (mysql_query(con, "INSERT INTO cars VALUES(2,'Mercedes',57127)")) {
      finish_with_error(con);
    }

    if (mysql_query(con, "INSERT INTO cars VALUES(3,'Skoda',9000)")) {
      finish_with_error(con);
    }

    if (mysql_query(con, "INSERT INTO cars VALUES(4,'Volvo',29000)")) {
      finish_with_error(con);
    }

    if (mysql_query(con, "INSERT INTO cars VALUES(5,'Bentley',350000)")) {
      finish_with_error(con);
    }

    if (mysql_query(con, "INSERT INTO cars VALUES(6,'Citroen',21000)")) {
      finish_with_error(con);
    }

    if (mysql_query(con, "INSERT INTO cars VALUES(7,'Hummer',41400)")) {
      finish_with_error(con);
    }

    if (mysql_query(con, "INSERT INTO cars VALUES(8,'Volkswagen',21600)")) {
      finish_with_error(con);
    }

#endif

    if (Mysql_query(con, "SEECT * FROM cars") ) {
//        EXIT_WITH_LOG_ERROR(exit_mysql, con, Mysql_error(con), 3000);
        MYSQL_EXIT_WITH_LOG_ERROR(exit_mysql, con);
//      finish_with_error(con);
    }

    MYSQL_RES *res;

    int res_fields_num;
    if ( !(res = mysql_store_result(con)) ) {
        finish_with_error(con);
    }
//
//    if ( !(res = mysql_store_result(con)) ) {
//        finish_with_error(con);
//    }


    res_fields_num = mysql_num_fields(res);
    printf("fields num: %d\n", res_fields_num);
    printf("rows num: %lu\n", mysql_num_rows(res));


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

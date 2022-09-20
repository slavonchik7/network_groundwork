

#ifndef MAIN2_H
#define MAIN2_H

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

int main2()
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


    if (mysql_query(con, "DROP TABLE IF EXISTS writers"))
    {
      finish_with_error(con);
    }

    char *sql = "CREATE TABLE writers(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(255))";

    if (mysql_query(con, sql))
    {
      finish_with_error(con);
    }

    if (mysql_query(con, "INSERT INTO writers(name) VALUES('Leo Tolstoy')"))
    {
      finish_with_error(con);
    }

    if (mysql_query(con, "INSERT INTO writers(name) VALUES('Jack London')"))
    {
      finish_with_error(con);
    }

    if (mysql_query(con, "INSERT INTO writers(name) VALUES('Honore de Balzac')"))
    {
      finish_with_error(con);
    }

    int id = mysql_insert_id(con);

    printf("The last inserted row id is: %d\n", id);


    mysql_close(con);

    return 0;
}


#endif /* MAIN2_H */

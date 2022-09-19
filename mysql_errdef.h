

#ifndef MYSQL_ERRDEF_H
#define MYSQL_ERRDEF_H

#include "msgee.h"
#include "mysql_wrap.h"
#include "last.h"

#define MYSQL_EXIT_CODE (-8)

#define MYSQL_EXIT_WITH_LOG_ERROR(ehandel, ehdata) \
            do { \
                EXIT_WITH_LOG_ERROR(ehandel, \
                        ehdata, \
                        Mysql_error(get_last_mysql_oper_handle()), \
                        MYSQL_EXIT_CODE) \
            } while(0)

#endif /* MYSQL_ERRDEF_H */

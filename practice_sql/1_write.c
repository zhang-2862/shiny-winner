#include <func.h>
#include <mysql/mysql.h>

/* created on ...       */

int main(int argc, char* argv[]) {
    // 初始化MYSQL连接
    MYSQL conn;
    MYSQL* pconn = mysql_init(&conn);
    
    // 与服务器建立连接
    const char* host = "localhost";
    const char* user = "root";
    const char* passwd = "1234";
    const char* db = "60th";
    pconn = mysql_real_connect(&conn, host, user, passwd, db, 0, NULL, 0);
    if (pconn == NULL) {
        printf("%d, %s\n", mysql_errno(pconn),
               mysql_error(pconn));
        return EXIT_FAILURE;
    }

    printf("conn has connted.\n");

    // 进行查询操作
    const char* sql = "INSERT INTO t_order VALUES(2, '操作系统', '1')";
    int ret = mysql_real_query(pconn, sql, strlen(sql));
    if (ret) {
        printf("%d, %s\n", mysql_errno(pconn),
               mysql_error(pconn));
        return EXIT_FAILURE;
    } else {
        // 写入成功的情况
        int rows = mysql_affected_rows(pconn);
        printf("QUERY OK, %d row affected.\n", rows);
    }

    return 0;
}


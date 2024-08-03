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
    const char* sql = "select * from t_order";
    int ret = mysql_real_query(pconn, sql, strlen(sql));
    // 每一次查询之后，不能在没有获取信息之前，进行第二次查询
    if (ret) {
        printf("(%d, %s)\n",mysql_errno(pconn),
               mysql_error(pconn));    
    } else {
        // 读取数据
        // 使用mysql_use_result 不会真正获取数据，只是得到了一个结果集的指针而已
        MYSQL_RES* pres = mysql_use_result(pconn);
        if (pres) {
            // rows为0，因为此时还没有真正保存数据
            int rows = mysql_num_rows(pres);
            int cols = mysql_num_fields(pres);
            printf("rows: %d, cols: %d\n", rows, cols);
            // 读取结果集的列信息
            MYSQL_FIELD* pfiled = NULL;
            while ((pfiled = mysql_fetch_field(pres)) != NULL) {
                    printf("%s\t", pfiled->name);
            }
            printf("\n");

            // 读取结果集的每一行数据
            MYSQL_ROW row = NULL;
            // 真正获取数据的是mysql_fetch_row，调用一次就获取一行数据
            while ((row = mysql_fetch_row(pres)) != NULL) {
                for (int i = 0; i < cols; ++i) {
                    printf("%s\t", row[i]);
                }
                printf("\n");
            }
        }
        // 释放MYSQL_RES结构体
        mysql_free_result(pres);
    }
    mysql_close(pconn);
    return 0;
}


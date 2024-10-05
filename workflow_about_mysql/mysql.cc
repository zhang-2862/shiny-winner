#include <workflow/WFFacilities.h>
#include <workflow/MySQLUtil.h>
#include <workflow/MySQLResult.h>
#include <iostream>
#include <signal.h>
using std::string;
using std::cerr;
static WFFacilities::WaitGroup waitGroup(1);

// 信号处理函数
void sighandler(int signum){
    std::cout << "signum = " << signum << "\n";
    waitGroup.done();
}

// mysql回调函数
void mysqlCallback(WFMySQLTask * mysqlTask){
    if(mysqlTask->get_state() != WFT_STATE_SUCCESS){ //错误处理
        // 在系统层面报错，权限or密码
        cerr << "error_msg =  " << WFGlobal::get_error_string(mysqlTask->get_state(), mysqlTask->get_error()) << "\n";
        return;
    }
    protocol::MySQLResponse * resp = mysqlTask->get_resp(); // 获取mysql任务响应
    if(resp->get_packet_type() == MYSQL_PACKET_ERROR){ // 错误处理
        // 在SQL语句报错
        cerr << "error_code = " << resp->get_error_code() << " error_msg = " << resp->get_error_msg() << "\n";
        return;
    }
    protocol::MySQLResultCursor cursor(resp); // 获取遍历查询结果的光标
    // 对所有查询结果进行处理
    do{
        if(cursor.get_cursor_status() == MYSQL_STATUS_OK){ // 对写类型语句的响应信息进行打印
            // 写类型的SQL语句
            cerr << "write \n";
            cerr << cursor.get_affected_rows() << " rows affected\n";
        }
        else if(cursor.get_cursor_status() == MYSQL_STATUS_GET_RESULT){
            // 读类型的SQL语句
            cerr << "read \n";
            // 读表头 列的信息 field
            const protocol::MySQLField * const * fieldArr;
            fieldArr = cursor.fetch_fields(); //获取字段数组的首地址
            for(int i = 0; i < cursor.get_field_count(); ++i){ // 将每一行的字段对应值依次打印
                cerr << "db = " << fieldArr[i]->get_db()
                     << " table = " << fieldArr[i]->get_table()
                     << " name = " << fieldArr[i]->get_name()
                     << " type = " << datatype2str(fieldArr[i]->get_data_type()) << "\n";
            }
            // 读表的内容 每一行每一列
            // bool fetch_all(std::vector<std::vector<MySQLCell>>& rows);
            std::vector<std::vector<protocol::MySQLCell>> rows;
            cursor.fetch_all(rows); // 将每一行按照对应值类型进行打印
            for(auto &row:rows){
                for(auto &cell:row){
                    if(cell.is_int()){
                        cerr << cell.as_int();
                    }
                    else if(cell.is_string()){
                        cerr << cell.as_string();
                    }
                    else if(cell.is_datetime()){
                        cerr << cell.as_datetime();
                    }
                    cerr << "\t";
                }
                cerr << "\n";
            } 
        }
    }while(cursor.next_result_set()); //mysql 任务支持一个任务处理多个SQL语句
}
int main(){
    signal(SIGINT,sighandler); // 注册信号处理函数
    // 创建mysql任务
    WFMySQLTask * mysqlTask =  WFTaskFactory::create_mysql_task("mysql://root:123@localhost",1,mysqlCallback);
    // 设定查询语句 (往token表中插入值)
    string sql = "insert into mycloud.tbl_user_token (user_name,user_token) values ('Caixukun','singdancerap');";
    //string sql;
    sql += "select * from mycloud.tbl_user_token;"; // 并查询表中所有行数据
    mysqlTask->get_req()->set_query(sql); // 设定查询请求
    mysqlTask->start(); // 将任务交给框架
    waitGroup.wait(); // 等待任务完成
    return 0;
}

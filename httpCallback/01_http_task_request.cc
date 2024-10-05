// http客户端
#include <workflow/WFFacilities.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/HttpUtil.h>
#include <signal.h>
#include <iostream>
using std::cout;
using std::cerr;


static WFFacilities::WaitGroup waitGroup(1); // 创建一个等待组

// 信号处理函数
void sighandler(int signum){
    waitGroup.done(); // 将等待组中的一个wait结束
    cout << "done\n"; // 打印done信息
}

// 框架会在百度回复响应以后，调用http回调函数
void httpCallback(WFHttpTask *task){
	protocol::HttpRequest *req = task->get_req(); // 获取http请求
	protocol::HttpResponse *resp = task->get_resp(); // 获取http响应
	int state = task->get_state(); // 获取状态码
	int error = task->get_error(); // 获取错误码

	switch(state){ //根据状态码进行分支处理
	case WFT_STATE_SYS_ERROR: // 系统错误
		cerr <<"system error: " << strerror(error) << "\n"; // 打印错误信息
		break;
	case WFT_STATE_DNS_ERROR: // 域名解析错误
		cerr <<"DNS error: " << gai_strerror(error) << "\n"; // 打印错误信息
		break;
	case WFT_STATE_SSL_ERROR: // 安全套接字层错误，一般是证书有问题
		cerr <<"SSL error: " << error << "\n";
		break;
	case WFT_STATE_TASK_ERROR: // 任务错误
		cerr <<"Task error: "<< error << "\n";
		break;
	case WFT_STATE_SUCCESS: // 成功
		break;
	}
	if (state != WFT_STATE_SUCCESS){ //如果任务失败则打印相关信息提示退出进程
		cerr <<"Failed. Press Ctrl-C to exit.\n";
		return;
	}

	
	cerr << req->get_method() << " " // 打印http请求方法
		 << req->get_http_version() << " " // 打印http版本信息
	     << req->get_request_uri() << "\n"; // 打印请求的uri
	protocol::HttpHeaderCursor reqCursor(req); // 获取请求的光标,用于访问其中的元素(作用等同于迭代器)
	std::string name; // 以名字为键
	std::string value; // 值
	while (reqCursor.next(name, value)){ // 以键值对形式打印输出请求体
        cerr << "name = " << name << " value = " << value << "\n";
    }

	
	cerr << resp->get_http_version() << " " // 打印http版本信息
		 << resp->get_status_code()  << " " // 打印状态码
		 << resp->get_reason_phrase() << "\n"; // 打印原因短语，用来解释状态码
	protocol::HttpHeaderCursor respCursor(resp); // 获取响应体的光标
	while (respCursor.next(name, value)){ // 依次取出所有首部字段，打印所有键值对
        cerr << "name = " << name << " value = " << value << "\n";
    }
	
	const void *body; // 用于指向 请求/响应 体的指针
	size_t body_len; // 请求/响应 体的长度
	resp->get_parsed_body(&body, &body_len); // 获取并设置短语位置
    cerr << static_cast<const char *>(body) << "\n"; // 将指针转型为非const版本
}

int main() {
    signal(SIGINT,sighandler); // 注册 'ctrl+c' 信号处理函数
   
    // 创建httptask任务，传入相关参数
    WFHttpTask * httpTask = WFTaskFactory::create_http_task(
        "http://www.baidu.com", // 访问域名
        10, // 最大重定向次数
        10, // 最大重试次数
        httpCallback // 回调函数
    );

    // 找到请求
    protocol::HttpRequest *req  = httpTask->get_req();
    req->set_method("POST");
    req->set_request_uri("/?wd=123");
    req->add_header_pair("MyName", "Workflow");
    
    // 用户把任务交给框架,之后由框架执行http任务
    httpTask->start();  
    waitGroup.wait(); // 设置等待组,等待任务执行完毕
    cout << "finished!\n"; // 打印执行结束的信息
    return 0;
}

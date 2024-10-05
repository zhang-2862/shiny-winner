#include <workflow/WFFacilities.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>
#include <workflow/HttpUtil.h>

#include <signal.h>
#include <unistd.h>

#include <iostream>
#include <string>

using std::cout;
using std::cerr;
using std::string;

static WFFacilities::WaitGroup waitGroup(1);

void handler(int signum) {
    cout << "done\n";
    waitGroup.done();
}

void httpCallback(WFHttpTask *httpTask) {
    cout << "http callback is called\n";
    protocol::HttpResponse *resp = httpTask->get_resp();

    int state = httpTask->get_state();
    int error = httpTask->get_error();
    switch (state) {
    case WFT_STATE_SYS_ERROR:
        cerr << "system error: " << strerror(error) << "\n";
        break;
    case WFT_STATE_DNS_ERROR:
        cerr << "DNS error: " << gai_strerror(error) << "\n";
        break;
    case WFT_STATE_SSL_ERROR:
        cerr << "SSL error\n";
        break;
    case WFT_STATE_TASK_ERROR:
        cerr << "Task error\n";
    case WFT_STATE_SUCCESS:
        break;
    }
    if (state != WFT_STATE_SUCCESS) {
        cerr << "Failed. Press Ctrl-C to exit.\n";
        return;
    }

    const void *body;
    size_t body_len;
    resp->get_parsed_body(&body, &body_len);
    // 将内容赋值给data
    string data =  static_cast<const char*>(body);

    WFRedisTask *redisTask = WFTaskFactory::create_redis_task("redis://127.0.0.1:6379",
                                                              10,
                                                              nullptr);
    redisTask->get_req()->set_request("SET", {"www.taobao.com", data});
    series_of(httpTask)->push_back(redisTask);
    cout << data << "\n";
}


int main(int argc, char* argv[]) {
    signal(SIGINT, handler); 

    // 创建任务
    WFHttpTask *httpTask = WFTaskFactory::create_http_task("http://www.taobao.com",
                                                           10,
                                                           10,
                                                           httpCallback);

    // 将任务交给框架
    httpTask->start();

    waitGroup.wait();
    cout << "finish\n";

    return 0;
}


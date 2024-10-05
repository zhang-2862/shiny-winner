#include <workflow/WFFacilities.h>
#include <workflow/WFTaskFactory.h>
#include <iostream>
#include <signal.h>

using std::cout;
using std::endl;

static WFFacilities::WaitGroup waitGroup(1);

void handler(int signum) {
    cout << "done\n";
    waitGroup.done();
}

int main(int argc, char* argv[]) {
    signal(SIGINT, handler);
    // 创建任务
    WFRedisTask *redisTask = WFTaskFactory::create_redis_task("redis://127.0.0.1:6379",
                                                              10,
                                                              nullptr);
    // 找到请求并设置
    protocol::RedisRequest *req  = redisTask->get_req();
    req->set_request("SET", {"99999999", "value"});

    // 将任务交给框架
    redisTask->start();
    waitGroup.wait();
    cout << "finish\n";

    return 0;
}


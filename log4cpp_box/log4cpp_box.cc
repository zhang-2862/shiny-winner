#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/Appender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <string>
using std::string;
#define addPrefix(msg) string("[").append(__FILE__)\
    .append(":").append(__func__)\
    .append(":").append(std::to_string(__LINE__))\
    .append("]").append(msg).c_str()

#define logEmerg(msg) Mylogger::getInstance()\
    ->warn(addPrefix(msg))

#define logFatal(msg) Mylogger::getInstance()\
    ->warn(addPrefix(msg))

#define logAlert(msg) Mylogger::getInstance()\
    ->warn(addPrefix(msg))

#define logCrit(msg) Mylogger::getInstance()\
    ->warn(addPrefix(msg))

#define logError(msg) Mylogger::getInstance()\
    ->warn(addPrefix(msg))

#define logWarn(msg) Mylogger::getInstance()\
    ->warn(addPrefix(msg))

#define logNotice(msg) Mylogger::getInstance()\
    ->warn(addPrefix(msg))

#define logInfo(msg) Mylogger::getInstance()\
    ->warn(addPrefix(msg))

#define logDebug(msg) Mylogger::getInstance()\
    ->warn(addPrefix(msg))

using namespace log4cpp;

class Mylogger {
public:
	void emerg(const char *msg);
	void fatal(const char *msg);
	void alert(const char *msg);
	void crit(const char *msg);
	void error(const char *msg);
	void warn(const char *msg);
	void notice(const char *msg);
	void info(const char *msg);
	void debug(const char *msg);
	static Mylogger* getInstance();
    static void destroy();
private:
	Mylogger();
	~Mylogger();
    Mylogger(const Mylogger&) = delete;
    Mylogger& operator=(const Mylogger&) = delete;

private:
    static Mylogger* _pMylogoger;
    Category& _category; 
};
Mylogger* Mylogger::_pMylogoger = nullptr;

Mylogger::Mylogger()
    :_category(Category::getInstance("categ"))
{
    // 创建布局器
    PatternLayout* ptn1 = new PatternLayout();
    ptn1->setConversionPattern("%d %c [%p] %m%n");
    // 创建输出器
    RollingFileAppender* rollFileAppender =  new RollingFileAppender("roll_file", "box.log",
                                                                     5 * 1024, 9);
    // 给输出器设置布局模式
    rollFileAppender->setLayout(ptn1);
    // 给记录器添加输出器
    _category.addAppender(rollFileAppender);
    _category.setPriority(Priority::WARN);
}

Mylogger* Mylogger::getInstance() {
    if (_pMylogoger == nullptr) {
        _pMylogoger = new Mylogger();
    }
    return _pMylogoger;
}

Mylogger::~Mylogger() {
    Category::shutdown();
}

void Mylogger::destroy() {
    if (_pMylogoger != nullptr) {
        delete _pMylogoger;
        _pMylogoger = nullptr;
    }
}

void Mylogger::emerg(const char *msg) {
    _category.emerg(msg);
}

void Mylogger::fatal(const char *msg) {
    _category.fatal(msg);
}

void Mylogger::alert(const char *msg) {
    _category.alert(msg);
}

void Mylogger::crit(const char *msg) {
    _category.crit(msg);
}

void Mylogger::error(const char *msg) {
    _category.error(msg);
}

void Mylogger::warn(const char *msg) {
    _category.warn(msg);
}

void Mylogger::notice(const char *msg) {
    _category.notice(msg);
}

void Mylogger::info(const char *msg) {
    _category.info(msg);
}

void Mylogger::debug(const char *msg) {
    _category.debug(msg);
}


void test0()
{
    //第一步，完成单例模式的写法
    Mylogger *log = Mylogger::getInstance();

    log->info(addPrefix("The log is info message"));
    log->error(addPrefix("The log is info message"));
    log->fatal(addPrefix("The log is info message"));
    log->crit(addPrefix("The log is info message"));

    Mylogger::destroy();
}

void test1() 
{
    printf("hello,world\n");
    //第二步，像使用printf一样
    //只要求能输出纯字符串信息即可，不需要做到格式化输出
    logInfo("The log is info message");
    logError("The log is error message");
    logWarn("The log is warn message");
    logDebug("The log is debug message");

    Mylogger::destroy();
}

int main(int argc, char* argv[]) {
    test0();
    /* Category::shutdownForced(); */
    return 0;
}

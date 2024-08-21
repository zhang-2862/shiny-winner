#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/Appender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>
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
    Category& _category = Category::getInstance("categ");
};
Mylogger* Mylogger::_pMylogoger = nullptr;

Mylogger::Mylogger() {
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

inline 
void Mylogger::emerg(const char *msg) {
    _category.emerg("msg[%s:%s:%d]",
                    __FILE__,__func__, __LINE__);
}

inline 
void Mylogger::fatal(const char *msg) {
    _category.fatal("msg[%s:%s:%d]",
                    __FILE__,__func__, __LINE__);
}

inline 
void Mylogger::alert(const char *msg) {
    _category.alert("msg[%s:%s:%d]",
                    __FILE__,__func__, __LINE__);
}

inline 
void Mylogger::crit(const char *msg) {
    _category.crit("msg[%s:%s:%d]",
                    __FILE__,__func__, __LINE__);
}

inline 
void Mylogger::error(const char *msg) {
    _category.error("msg[%s:%s:%d]",
                    __FILE__,__func__, __LINE__);
}

inline 
void Mylogger::warn(const char *msg) {
    _category.warn("msg[%s:%s:%d]",
                    __FILE__,__func__, __LINE__);
}

inline 
void Mylogger::notice(const char *msg) {
    _category.notice("msg[%s:%s:%d]",
                    __FILE__,__func__, __LINE__);
}

inline 
void Mylogger::info(const char *msg) {
    _category.info("msg[%s:%s:%d]",
                    __FILE__,__func__, __LINE__);
}

inline 
void Mylogger::debug(const char *msg) {
    _category.debug("msg[%s:%s:%d]",
                    __FILE__,__func__, __LINE__);
}

void logEmerg(const char* msg) {
    Mylogger::getInstance()->emerg(msg);
}

void logFatal(const char* msg) {
    Mylogger::getInstance()->fatal(msg);
}

void logAlert(const char* msg) {
    Mylogger::getInstance()->alert(msg);
}

void logCrit(const char* msg) {
    Mylogger::getInstance()->crit(msg);
}

void logError(const char* msg) {
    Mylogger::getInstance()->error(msg);
}

void logWarn(const char* msg) {
    Mylogger::getInstance()->warn(msg);
}

void logNotice(const char* msg) {
    Mylogger::getInstance()->notice(msg);
}

void logInfo(const char* msg) {
    Mylogger::getInstance()->info(msg);
}

void logDebug(const char* msg) {
    Mylogger::getInstance()->debug(msg);
}

void test0()
{
    //第一步，完成单例模式的写法
    Mylogger *log = Mylogger::getInstance();

    log->info("The log is info message");
    log->error("The log is error message");
    log->fatal("The log is fatal message");
    log->crit("The log is crit message");

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
    test1();
    /* Category::shutdownForced(); */
    return 0;
}

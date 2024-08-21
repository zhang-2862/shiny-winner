#include <iostream>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Category.hh>
using std::cout;
using std::endl;
using namespace log4cpp;

void log() {
    PatternLayout* ptn1 = new PatternLayout();
    ptn1->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout* ptn2 = new PatternLayout();
    ptn2->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout* ptn3 = new PatternLayout();
    ptn3->setConversionPattern("%d %c [%p] %m%n");

    OstreamAppender* pos = new OstreamAppender("console", &cout);
    pos->setLayout(ptn1);

    FileAppender* filePos = new FileAppender("file", "l.log");
    filePos->setLayout(ptn2);

    RollingFileAppender* rollFilePos = new RollingFileAppender("rFile", "rf.log", 5*1024, 9);
    rollFilePos->setLayout(ptn3);
    
    Category& categ = Category::getInstance("categ");
    categ.setPriority(Priority::DEBUG);

    categ.addAppender(pos);
    categ.addAppender(filePos);
    categ.addAppender(rollFilePos);

    int count=30;
    while (count-- > 0) {
        categ.emerg("this is an emerg msg");
        categ.fatal("this is a fatal msg");
        categ.alert("this is an alert msg");
        categ.crit("this is a crit msg");
        categ.error("this is an error msg");
        categ.warn("this is a warn msg");
        categ.notice("this is a notice msg");
        categ.info("this is a info msg");
    }

    Category::shutdown();
}

int main(int argc, char* argv[]) {
    log();
    
    return 0;
}


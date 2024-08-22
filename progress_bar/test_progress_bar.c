#include <func.h>

void print_progress_bar(long sum_len, double percent) {
        // 打印进度条
        printf("has complete %5.2lf%%\r", percent);
}

void test(void) {
    long sum_len = 100000000;
    long segment = sum_len / 100; //百分之一的长度 
    long cur_size = 0;
    srand(time(NULL));
    while (cur_size < sum_len) {
        int ret = rand()%10000;
        cur_size += ret;
        double percent = (double)cur_size / sum_len * 100;
        print_progress_bar(sum_len, percent);
        usleep(10000);
    }
    printf("\n");
}

int main(void) {
    test();

    return 0;
}

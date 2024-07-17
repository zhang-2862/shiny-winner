#include <func.h>

/* created on      */

typedef struct {
    int id;
    int balance;
} Account;

Account acct1 = {1, 100};
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void cleanup(void* arg) {
    pthread_mutex_unlock(&mtx);
}

int withdraw(int money) {
    pthread_mutex_lock(&mtx);

    pthread_cleanup_push(cleanup, NULL);
    
    if (acct1.balance < money) {
        pthread_mutex_unlock(&mtx);
        return 0;
    }

    sleep(1);
    acct1.balance -= money;
    pthread_mutex_unlock(&mtx);
    return money;
    pthread_cleanup_pop(0);
}

void* start_routine(void* arg) {
    int money = (int)arg;
    int n = withdraw(money);
    printf("thread_id: %lu withdraw $%d\n",pthread_self(),n);
    return NULL;
}

int main(int argc, char* argv[]) {
    pthread_t threads[10]; 
    for(int i = 0; i < 10; i++) {
        pthread_create(threads + i, NULL, start_routine, (void*)100);
    }

    for(int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}


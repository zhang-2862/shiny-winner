#include <func.h>

/* created on      */
typedef struct {
    int id;
    int balance;
    pthread_mutex_t mutex;
} Account;

Account acct1 = {1, 100, PTHREAD_MUTEX_INITIALIZER};
Account acct2 = {1, 900, PTHREAD_MUTEX_INITIALIZER};

pthread_mutex_t glob_mtx = PTHREAD_MUTEX_INITIALIZER;

int transfer(Account* acct_A, Account* acct_B, int money) {
    pthread_mutex_lock(&glob_mtx);
    pthread_mutex_lock(&(acct_A->mutex));
    pthread_mutex_lock(&(acct_B->mutex));
    pthread_mutex_unlock(&glob_mtx);
    if(acct_A->balance < money) {
        // 解锁
        pthread_mutex_unlock(&(acct_B->mutex));
        pthread_mutex_unlock(&(acct_A->mutex));
        pthread_mutex_unlock(&glob_mtx);
        return 0;
    }
    sleep(1);
    acct_A->balance -= money;
    acct_B->balance += money;
    // 解锁
    pthread_mutex_unlock(&(acct_B->mutex));
    pthread_mutex_unlock(&(acct_A->mutex));
    return money;
}

void* start_routine1(void* arg) {
    int money = (int)arg;
    int n = transfer(&acct1, &acct2, money);
    printf("thread_id :%lu, acct1 -> acct2 $%d\n", pthread_self(), n);
    return NULL;
}

void* start_routine2(void* arg) {
    int money = (int)arg;
    int n = transfer(&acct2, &acct1, money);
    printf("thread_id :%lu, acct2 -> acct1 $%d\n", pthread_self(), n);
    return NULL;
}

int main(int argc, char* argv[]) {
    printf("before transfer :\n");
    printf("acct1->balance: %d\n",acct1.balance);
    printf("acct2->balance: %d\n",acct2.balance);

    pthread_t tid1;
    pthread_t tid2;
    pthread_create(&tid1, NULL, start_routine1, (void*)100);
    pthread_create(&tid2, NULL, start_routine2, (void*)900);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    printf("after transfer :\n");
    printf("acct1->balance: %d\n",acct1.balance);
    printf("acct2->balance: %d\n",acct2.balance);
    return 0;
}


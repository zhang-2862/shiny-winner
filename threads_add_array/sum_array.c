#include <func.h>

/* created on 24/7/15     */

int arr[10240000];

typedef struct Section {
    int start;
    int end;
    long long sum;
}section;

void init_arr() {
    for(int i = 0; i < 10240000; i++) {
        arr[i] = i;
    }
}

void* start_routine(void* arg) {
    section* psec = (section*)arg;
    int i = psec->start;
    int end = psec->end;
    printf("%d  %d \n",psec->start,psec->end);
    for(; i < end; i++) {
        psec->sum += arr[i];
    }
    return (long long *)psec->sum;
}


int main(int argc, char* argv[]) {
    long long n;
    printf("Please input a long long int: ");
    scanf("%lld", &n);

    init_arr();

    pthread_t tid1;
    section s1;
    s1.start = 0;
    s1.end = n/2;
    s1.sum = 0;

    pthread_t tid2;
    section s2;
    s2.start = n/2;
    s2.end = n;
    s2.sum = 0;
    int err = pthread_create(&tid1, NULL, start_routine, (void*)&s1);
    if (err) {
        error(1, err, "pthread_create no.1");
    }

    err = pthread_create(&tid2, NULL, start_routine, (void*)&s2);
    if (err) {
        error(1, err, "pthread_create no.2");
    }
    
    long long ret1;
    long long ret2;
    pthread_join(tid1, (void**)&ret1);
    pthread_join(tid2, (void**)&ret2);

    //printf("sum = %lld\n", ret1 + ret2);
    printf("sum1 = %lld\n", ret1);
    printf("sum2 = %lld\n", ret2);
    return 0;
}


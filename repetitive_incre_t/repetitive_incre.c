#include <func.h>

/* created on 24/7/15      */

void* start_routine(void* val) {
    long long* value = (long long*)val;
    for(int i = 0; i < 10000000; i++) {
        (*value)++;
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    long long* value = (long long*) calloc(1, sizeof(long long));
    pthread_t tid1;
    pthread_t tid2;
    int err = pthread_create(&tid1, NULL, start_routine, (void*)value);
    if (err) {
        error(1, err, "pthread_create no.1");
    }
    err = pthread_create(&tid2, NULL, start_routine, (void*)value);
    if (err) {
        error(1, err, "pthread_create no.2");
    }

    pthread_join(tid1, NULL); 
    pthread_join(tid2, NULL); 

    printf("value = %lld\n", *value);
    return 0;
}


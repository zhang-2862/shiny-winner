#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

long long* generatePrimes(int n) {
    long long* arr = (long long*)malloc(sizeof(long long) * n);
    arr[0] = 1;//将素数保存在数组中
    arr[1] = 2;
    int max_size = 2;//数组容量
    long long x = 3;//初始判断
    while (n) {
        for (int idx = 1; idx < max_size; idx++) {
            if (x % arr[idx] == 0) {
                x++;
                continue;
            }
        }
        arr[max_size++] = x++;
        n--;
    }
    return arr;
}

int main() {
    int n;
    printf("please input a num.\n");
    scanf("%d", &n);

    long long* arr = generatePrimes(n);

    for (int i = 0; i < n; i++) {
        printf("%lld ", arr[i]);
    }

    printf("\n\n");
    
    return 0;
}


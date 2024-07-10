#include <stdio.h>
#include <stdbool.h>

bool isPrime(long long n){
    if(n==1 || n==0){
        return false;
    }
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            return false;
        }
    }
    return true;;
}

int main()
{
    long long num;
    printf("please input a number.\n");
    scanf("%lld",&num);
    
    if(isPrime(num)){
        printf("%lld is prime!\n",num);
    }else{
        printf("%lld is not prime!\n",num);
    }    
    return 0;
}


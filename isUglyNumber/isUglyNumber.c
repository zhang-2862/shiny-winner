#include <stdio.h>
#include <stdbool.h>

bool isUglyNumber(long long n){
      while(n%5==0){
          n/=5;
        }
      while(n%3==0){
          n/=3;     
        }
      while(n%2==0){
          n/=2;
      }
      if(n==1){
          return true;
      }else{
          return false;
      }
}

int main()
{
    long long n;
    printf("please input a num\n");
    scanf("%lld",&n);
    if(isUglyNumber(n)){
        printf("isUglyNumber!\n");
    }else{
        printf("not a UglyNumber!\n");
    }
    return 0;
}


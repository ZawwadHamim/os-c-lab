#include<stdio.h>

int main(){
    int n,sum;

    printf("Value of n: ");
    scanf("%i",&n);

    sum = (n*(n+1))/2;

    printf("The sum of 1 to %i is %i", n,sum);

    return 0;
}
#include<stdio.h>

int main(){
    int a,b,c,sum;
    printf("Enter three angles: ");
    scanf("%i %i %i", &a,&b,&c);

    if(a==0 || b==0 || c==0){
        printf("All values must be more than 0");

        return 0;
    }
    sum = a+b+c;
    if(sum==180){
        printf("Valid triangle");
    }
    else{
        printf("Can't form a triangle");
    }

    return 0;
}
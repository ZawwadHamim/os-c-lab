#include<stdio.h>

int main(){
    int arr[5] = {10,20,30,40,50};
    int n = 5;
    int i = 0;
    int j = n-1;
    int temp;
    while (i<j){
        temp = arr[i];
        arr[i]=arr[j];
        arr[j]=temp;

        i++;
        j--;
    }
    for(int i = 0; i<n; i++){
        printf("arr[%i] = %i\n", n, arr[i]);
    }

    return 0;
}
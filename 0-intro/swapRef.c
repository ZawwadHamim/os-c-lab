#include<stdio.h>

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main(){
    int arr[100], pos1,pos2, n;

    printf("Enter size of array: ");
    scanf("%d",&n);

    for(int i=0; i<n;i++){
        printf("%dth elemet: ",i);
        scanf("%d",&arr[i]);
    }
    printf("Enter two positions to swap (0 to %d): ", n - 1);
    scanf("%d %d", &pos1, &pos2);
    swap(&arr[pos1],&arr[pos2]);

    printf("array after swap: ");
    for(int i = 0; i<n; i++){
        printf("the arr[%d] = %d ", i, arr[i]);
    }
}
#include<stdio.h>
void swap(int *num1,int *num2){
    int temp;

    temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}
int main(void){
    int num1, num2;

    printf("Enter two numbers that needed to be swapped: ");
    scanf("%d %d",&num1,&num2);

    printf("Before swap %d %d\n", num1,num2);
    swap(&num1,&num2);
    printf("After swap %d %d\n", num1,num2);


}
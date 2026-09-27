#include<stdio.h>
#define PI 3.14159
float diameter(float r){
    return 2*r;
}

float circumference(float r){
    return 2*PI*r;
}
float area(float r){
    return PI*r*r;
}

int main(void){
    float r;
    printf("Enter radius of a circle: ");
    scanf("%f",&r);

    float d, c, a;

    d = diameter(r);
    c = circumference(r);
    a = area(r);
    
    printf("diameter of circle %.2f\n", d);
    printf("circumference of circle %.2f\n", c);
    printf("area of circle %.2f\n", a);
}
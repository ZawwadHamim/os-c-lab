#include <stdio.h>

int main() {
    int p = 20;
    int *a;

    a = &p;

    printf("value of a: %p\n", (void *)a);
    printf("location of p: %p\n", (void *)&p);
    printf("value of p: %d\n", *a);

    return 0;
}
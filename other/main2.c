#include <stdio.h>
#include <stdlib.h>

int main3() {

    int a = 119;
    int b = 35;

    printf("a: %d, b: %d, (a mod b): %d\n", a, b, a % b);


    while( (a % b) != 0){
        int rem = a % b;
        a = b;
        b = rem;
        printf("a: %d, b: %d, (a mod b): %d\n", a, b, a % b);
    }

    return 0;
}
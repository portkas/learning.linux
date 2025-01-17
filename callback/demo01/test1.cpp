#include <stdio.h>
int ADD(int (*callback)(int, int), int a, int b){
    return (*callback)(a,b);
}

int add(int a, int b){
    return a+b;
}

int main(){
    printf("add function:%d\n", add(1, 2));
    printf("callback func:%d\n", ADD(add, 1, 2));
    return 0;
}
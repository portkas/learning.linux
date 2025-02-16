#include <stdio.h>

// 定义宏
#define CALL_WITH_MAX(a, b) f((a) > (b) ? (a) : (b))

// 定义一个简单的函数f，用于打印参数值
void f(int value) {
    printf("f(%d)\n", value);
}

int main() {
    int a = 5, b = 0;

    printf("Before first CALL_WITH_MAX: a = %d, b = %d\n", a, b);
    CALL_WITH_MAX(++a, b);
    printf("After first CALL_WITH_MAX: a = %d, b = %d\n", a, b);

    printf("Before second CALL_WITH_MAX: a = %d, b = %d\n", a, b);
    CALL_WITH_MAX(++a, b + 10);
    printf("After second CALL_WITH_MAX: a = %d, b = %d\n", a, b);

    return 0;
}
#include <iostream>

int main() {
    int* ptr = new int(10);  // 动态分配一个整数，值为10
    std::cout << "Before delete: " << *ptr << std::endl;  // 输出：10

    delete ptr;  // 释放内存
    // 注意：此时ptr仍然是一个野指针，指向已经被释放的内存
    std::cout << "After delete: " << *ptr << std::endl;  // 输出可能是随机值，也可能导致程序崩溃
    ptr = nullptr;

    // 尝试访问nullptr（安全的，不会崩溃）
    if (ptr == nullptr) {
        std::cout << "ptr is now nullptr" << std::endl;
    } else {
        std::cout << "ptr still points to something" << std::endl;
    }

    return 0;
}
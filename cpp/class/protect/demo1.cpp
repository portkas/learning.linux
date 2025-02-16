#include <iostream>

class Base {
public:
    void publicFunc() { std::cout << "Base publicFunc" << std::endl; }
protected:
    void protectedFunc() { std::cout << "Base protectedFunc" << std::endl; }
private:
    void privateFunc() { std::cout << "Base privateFunc" << std::endl; }
};

class Derived : public Base {
public:
    void test() {
        publicFunc();       // 可以访问
        protectedFunc();    // 可以访问
        // privateFunc();    // 错误，无法访问
    }
};

int main() {
    Derived d;
    d.publicFunc();     // 可以访问
    // d.protectedFunc();   // 错误，protected成员不能被对象直接访问（派生类中）

    Base b;
    b.publicFunc();     // 可以访问
    // b.protectedFunc();   // 错误，protected成员不能被对象直接访问（基类中）
    return 0;
}
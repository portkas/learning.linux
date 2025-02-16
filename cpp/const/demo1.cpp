#include <iostream>
#include <string>

template<class T>
class NameObject {
public:
    NameObject(std::string& name, T value) 
        : nameValue(name), objectValue(std::move(value)) {}
    
    // 自定义赋值运算符
    NameObject& operator=(const NameObject& rhs) {
        if (this != &rhs) {
            nameValue = rhs.nameValue; // 修改引用的内容
            objectValue = rhs.objectValue; // 假设 T 可以赋值
        }
        return *this;
    }

private:
    std::string& nameValue;
    T objectValue; // 去掉 const
};

int main() {
    std::string newDog("persephone");
    std::string oldDog("satch");
    NameObject<int> p(newDog, 2);
    NameObject<int> s(oldDog, 36);

    p = s; // 现在可以正确赋值

    // 输出结果
    std::cout << "newDog: " << newDog << std::endl; // 输出 "satch"
    std::cout << "oldDog: " << oldDog << std::endl; // 输出 "satch"
    return 0;
}
// template<class T>
// class NameObject{
// public:
//     NameObject(std::string& name, const T& value);

// private:
//     std::string& nameValue;
//     const T objectValue;
// };

// int main(){
//     std::string newDog("persehone");
//     std::string oldDog("satch");
//     NameObject<int> p(newDog, 2);
//     NameObject<int> s(oldDog, 36);
//     p = s;
// }
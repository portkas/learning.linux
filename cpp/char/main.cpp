#include <iostream>

int main(){
    using std::cout;
    using std::endl;
    cout << "\'A\' size : " << sizeof('A') << " and type is : " << typeid('A').name() << endl;
    cout << "\"A\" size : " << sizeof("A") << " and type is : " << typeid("A").name() << endl;
    return 0;
}

// 'A' 是一个字符量，类型为char;
// "A" 是一个字符串常量，类型为char[2];
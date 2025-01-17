#include <iostream>
#include <functional>
using namespace std;

typedef function<void(int)> CallBackFunc;

void executeCallback(CallBackFunc callback, int value){
    callback(value);
}

void freeFunction(int value){
    cout << "普通函数回调，传入的参数为：" << value << endl;
}

class CallbackHandler{
public:
    void memberCallback(int value){
        cout << "成员函数回调，传入的参数为：" << value << endl;
    }
};

int main(){
    CallbackHandler handler;
    // 1. 传递普通函数作为回调
    executeCallback(freeFunction, 42);

    // 2. 传递Lambda表达式作为回调
    executeCallback([](int value){
        cout << "Lambda 回调，传入的参数为：" << value << endl;
    }, 43);

    // 3. 传递成员函数作为回调
    executeCallback(std::bind(&CallbackHandler::memberCallback, &handler, std::placeholders::_1), 44);

    return 0;
}
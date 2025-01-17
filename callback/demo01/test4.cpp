#include <iostream>
using namespace std;

class CallbackHandler{
public:
    // 成员函数作为回调函数
    void memberCallback(int value){
        cout << "成员函数回调，被调用时传入的值是:" << value << endl;
    }
};

// 一个执行回调的函数
void executableMemberCallback(CallbackHandler* obj, void (CallbackHandler::*callback)(int), int value){
    // 通过对象指针和成员函数指针调用成员函数
    (obj->*callback)(value);
}

int main(){
    // 传递对象和成员函数指针进行回调
    CallbackHandler handler;
    executableMemberCallback(&handler, &CallbackHandler::memberCallback, 42);
    return 0;
}
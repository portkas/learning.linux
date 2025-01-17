#include<iostream>
using namespace std;

void constValue(){
    int x = 10;
    int y = 20;
    const int *p = &x;
    cout<<"p: "<<p<<" : "<<*p<<endl;
    x = 20;     // 正确
    cout<<"p: "<<p<<" : "<<*p<<endl;
    p = &y;     // 正确
    cout<<"p: "<<p<<" : "<<*p<<endl;
    // *p = 30; // 错误
}

void constPointer(){
    int x = 10;
    int y = 20;
    int *const p = &x;
    cout<<"p: "<<p<<" : "<<*p<<endl;
    x = 20;     // 正确
    cout<<"p: "<<p<<" : "<<*p<<endl;
    *p = 30;    // 正确 
    cout<<"p: "<<p<<" : "<<*p<<endl;
    // p = &y;  // 错误
}

int main(){
    constPointer();
    return 0;
}
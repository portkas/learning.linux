#include <iostream>
#include <stack>
#include <queue>

void stackDemo(){
    int count = 0;
    std::stack<int> stk;
    stk.push(10);
    stk.push(20);
    stk.push(30);
    stk.push(40);
    stk.push(50);
    stk.push(60);
    stk.push(70);
    stk.push(80);
    std::cout<<stk.size()<<std::endl;
    while(!stk.empty()){
        std::cout<<"NO"<<++count<<":"<< stk.top()<<std::endl;
        stk.pop();
    }
}

void queueDemo(){
    int count = 0;
    std::queue<int> stk;
    stk.push(10);
    stk.push(20);
    stk.push(30);
    stk.push(40);
    stk.push(50);
    stk.push(60);
    stk.push(70);
    stk.push(80);
    std::cout<<stk.size()<<std::endl;
    while(!stk.empty()){
        std::cout<<"NO"<<++count<<":"<< stk.front()<<std::endl;
        stk.pop();
    }
}

int main(){
    stackDemo();
    queueDemo();
    return 0;
}
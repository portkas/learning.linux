#include <iostream>
#include <queue>
using namespace std;

class MyStack {
private:
    queue<int> que1;
    queue<int> que2;
public:
    MyStack() {
        
    }
    
    void push(int x) {
        que1.push(x);
    }
    
    int pop() {
        if (que1.empty()) return -1;
        int len = que1.size();
        for(int i=0; i < len - 1; ++i){
            cout<<que1.size()<<endl;
            que2.push(que1.front());
            que1.pop();
        }
        int result = que1.front();
        que1.pop();
        que1 = que2;
        while(!que2.empty()){
            que2.pop();
        }
        return result;
    }
    
    int top() {
        if (que1.empty()) return -1;
        int result = que1.back();
        return result;
    }
    
    bool empty() {
        return que1.empty();
    }
};

int main(){
    MyStack stk;
    stk.push(1);
    stk.push(2);
    stk.push(3);
    stk.push(1);
    stk.push(2);
    stk.push(3);
    cout<<"---------------"<<endl;
    stk.pop();
    cout<<"---------------"<<endl;
    stk.pop();
    cout<<"---------------"<<endl;
    stk.pop();
    cout<<"---------------"<<endl;
    return 0;
}
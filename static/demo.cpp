#include <iostream>

void func(){
    static int count = 0;
    count++;
    std::cout<<count<<std::endl;
}

int main(){
    int count = 0;
    std::cout<<"**"<<count<<"**"<<std::endl;
    for (int i = 0; i < 5; i++)
    {
        func();
    }
    std::cout<<"**"<<count<<"**"<<std::endl;
    return 0;
}
#include <iostream>

int main(){
    const int* constIntPtr = new int(10);
    std::cout<<"**"<<sizeof(constIntPtr)<<":"<<*constIntPtr<<"**"<<std::endl;

    int* intPtr = const_cast<int*>(constIntPtr);
    *intPtr = 20;

    std::cout<<"**"<<sizeof(intPtr)<<":"<<*intPtr<<"**"<<std::endl;
    return 0;
}
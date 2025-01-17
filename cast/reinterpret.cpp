#include <iostream>

int main(){
    int* intPtr = new int(10);
    std::cout<<"**"<<sizeof(intPtr)<<":"<<intPtr<<"**"<<std::endl;
    char* charPtr = reinterpret_cast<char*>(intPtr);
    std::cout<<"**"<<sizeof(intPtr)<<":"<<static_cast<void*>(charPtr)<<"**"<<std::endl;
    std::cout<<"**"<<sizeof(intPtr)<<":"<<*charPtr<<"**"<<std::endl;
    std::cout<<"**"<<sizeof(intPtr)<<":"<<charPtr<<"**"<<std::endl;

    long intValue = reinterpret_cast<long>(intPtr);
    int *intPtr2 = reinterpret_cast<int*>(intValue);
    std::cout<<"**"<<sizeof(intPtr2)<<":"<<*intPtr2<<"**"<<std::endl;
    return 0;
}
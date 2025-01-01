#include<iostream>
#include<string>

int main(){
    std::string s = "hello";
    std::cout<<s.size()<<std::endl;
    std::cout<<s.c_str()<<std::endl;
    std::cout<<s<<std::endl;
    std::cout<<s[0]<<std::endl;
    return 0;
}
#include <iostream>
#include <string>
using namespace std;

int main(){
    string s = "h1ll0";
    string t;
    for(int i=0; i<s.size(); ++i){
        cout<<static_cast<int>(s[i])<<endl;
        if(s[i] - '0' < 10){
            t = t + "number";
        }else{
            t = t + s[i]; 
        }
    }
    std::cout << t << std::endl;
}
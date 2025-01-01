#include <iostream>
#include <string>
using namespace std;

int main(){
    int k = 2;
    string s = "abcdefg";
    string t;
    int size = s.size();
    int left = 0;
    int right = size - k;
    if(k > size) {
        return 0;
    }
    while(right < size){
        t += s[right++];
    }
    while(left < size - k){
        t += s[left++];
    }
    std::cout << t << std::endl;
    return 0;
}
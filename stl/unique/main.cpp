#include <vector>
#include <algorithm>
#include <iostream>

int main() {
    std::vector<int> data = {1, 2, 2, 2, 2, 2, 2, 3, 4, 4, 4, 5, 5};
    std::cout<<"before unique : ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    auto last = std::unique(data.begin(), data.end());
    std::cout<<"after unique :  ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    data.erase(last, data.end());
    std::cout<<"after erase : ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
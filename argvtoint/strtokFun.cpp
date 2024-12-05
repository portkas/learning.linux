#include <iostream>
#include <cstring>
#include <vector>
#include <cstdlib>

int main() {
    // 假设输入保存在 buf 中
    char buf[1024] = "set exposure 5000";
    
    // 使用 vector 来存储分割后的字符串
    std::vector<char*> parts;

    // 使用 strtok 进行分割
    char* token = strtok(buf, " ");
    printf("token:%s\n", token);
    while (token != nullptr) {
        parts.push_back(token);
        token = strtok(nullptr, " ");
    }
    
    // 打印解析结果
    for (size_t i = 0; i < parts.size(); ++i) {
        std::cout << "Part " << i + 1 << ": " << parts[i] << std::endl;
    }
    
    // 将最后一部分转换为整数
    int number = 0;
    if (parts.size() >= 3) {
        number = std::stoi(parts.back());  // 使用 std::stoi 将字符串转换为整数
        std::cout << "Number: " << number << std::endl;
    } else {
        std::cout << "No number found." << std::endl;
    }

    return 0;
}
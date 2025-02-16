#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm> // std::copy

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    // 使用ostream_iterator将vector中的元素输出到标准输出流，以空格分隔
    std::ostream_iterator<int> out_it(std::cout, " ");
    std::copy(vec.begin(), vec.end(), out_it); // 使用算法将数据写入输出流
    std::cout << std::endl;

    // 另一个示例：输出到文件
    std::ofstream file("output.txt");
    std::ostream_iterator<int> file_it(file, "\n");
    std::copy(vec.begin(), vec.end(), file_it); // 将数据写入文件，每行一个元素
    file.close();
    return 0;
}
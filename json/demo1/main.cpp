#include <json/json.h>
#include <iostream>
 
int main() 
{
    // 创建一个Json::Value对象
    Json::Value root;
 
    // 向对象中添加数据
    root["name"] = "John Doe";
    root["age"] = 30;
    root["isAlive"] = true;
    root["address"]["city"] = "New York";
    root["address"]["state"] = "NY";
 
    // 创建一个Json::StreamWriterBuilder
    Json::StreamWriterBuilder writer;
 
    // 将Json::Value对象转换为字符串
    std::string output = Json::writeString(writer, root);
 
    // 打印输出
    std::cout << output << std::endl;
 
    return 0;
}
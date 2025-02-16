#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>

void outint(int n){
    std::cout << n << " ";
}

int main(){
    using namespace std;
    list<int> one(5,2);                         // 5个2
    int stuff[5] = {1,2,4,8,6};
    list<int> two;
    two.insert(two.begin(), stuff, stuff+5);
    int more[6] = {6,4,2,4,6,5};
    list<int> three(two);
    three.insert(three.end(), more, more+6);

    cout << "List one: ";
    for_each(one.begin(),one.end(), outint);        // List one: 2 2 2 2 2
    cout << endl << "List two: ";
    for_each(two.begin(), two.end(), outint);       // List two: 1 2 4 8 6
    cout << endl << "List three: ";
    for_each(three.begin(), three.end(), outint);   // List three: 1 2 4 8 6 6 4 2 4 6 5
    three.remove(2);                                // 移除2
    cout << endl << "List three minus 2s: ";
    for_each(three.begin(), three.end(), outint);   // List three minus 2s: 1 4 8 6 6 4 4 6 5 
    three.splice(three.begin(), one);               // 把one移动到three.begin()前面，然后one被清空
    cout << endl << "List three after splice: ";
    for_each(three.begin(), three.end(), outint);   // List three after splice: 2 2 2 2 2 1 4 8 6 6 4 4 6 5
    cout << endl << "List one: ";
    for_each(one.begin(), one.end(), outint);       // List one:
    three.unique();                                 // 压缩，将相邻重复元素压缩（但是还是会有重复元素，但是不相邻）
    cout << endl << "List three after unique: ";
    for_each(three.begin(), three.end(), outint);   // List three after unique: 2 1 4 8 6 4 6 5 
    three.sort();                                   // 排序
    three.unique();                                 // 压缩
    cout << endl << "List three after sort & unique: ";
    for_each(three.begin(), three.end(), outint);   // List three after sort & unique: 1 2 4 5 6 8 
    two.sort();                                     // two排序
    three.merge(two);                               // 两个排序的list合并在一起，合并成three，并且two被清空
    cout << endl << "Sorted two merged into three: ";
    for_each(three.begin(), three.end(), outint);   // Sorted two merged into three: 1 1 2 2 4 4 5 6 6 8 8
    cout << endl;

    return 0; 
}
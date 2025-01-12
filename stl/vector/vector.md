

# 基本概念

1. vector数据结构和数组非常相似，也称单端数组；
2. 数组是静态空间，vector可以动态扩展；
3. 动态扩展：找一个更大的内存空间，然后将原数据拷贝到新空间，释放原空间；
4. vector容器的迭代器支持随机访问；


# 构造函数

1. `vector<T> v;`：默认构造函数；
2. `vector(v.begin(), v.end());`：将迭代器区间的元素拷贝给本身，左闭右开；
3. `vector(n, elem);`：构造函数将n个elem拷贝给本身；
4. `vector(const vector& v);`：拷贝构造函数；


# 操作

1. 赋值操作
   1. =
   2. assign(begin(), end())
   3. assign(n, elem)
2. 容量和大小
   1. empty()
   2. capacity()
   3. size()
   4. resize(int num)
   5. resize(int num, elem)
3. 插入和删除
   1. push_back(ele)
   2. pop_back()
   3. insert(const_iterator pos, ele)
   4. insert(const_iterator pos, int count, ele)
   5. erase(const_iterator pos)
   6. erase(const_iterator start, const_iterator end)
   7. clear()
4. 数据存取
   1. at(int index)
   2. operator[]
   3. front()
   4. back()
5. 互换容器
   1. v1.swap(v2)
6. 预留空间
   1. v1.reserve(100)

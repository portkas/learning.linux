#include <memory>

template <class T>
struct __list_node
{
    typedef void *void_pointer;
    void_pointer prev; // 类型为void*。其实可设为__list_node<T>*
    void_pointer next;
    T data;
};

template <class T, class Ref, class Ptr>
struct list_iterator
{
    typedef list_iterator<T, T &, T *> iterator;
    typedef list_iterator<T, Ref, Ptr> self;

    // 表示迭代器的类别bidirectional_iterator_tag表示这是一个双向迭代器
    typedef bidirectional_iterator_tag iterator_category;
    typedef T value_type;              // 表示迭代器操作的数据类型
    typedef Ptr pointer;               // 表示指针类型
    typedef Ref reference;             // 表示引用类型
    typedef list_node<T> *link_type;   // 表示链表节点的指针类型
    typedef size_t size_type;          // 表示大小类型
    typedef ptrdiff_t difference_type; // 表示迭代器之间的差值类型

    link_type node; // 迭代器内部当然要有一个原生指标，指向list的节点

    // constructor
    list_iterator(link_type x) : node(x) {}            // 通过节点指针初始化迭代器
    list_iterator() {}                                 // 默认构造函数
    list_iterator(const iterator &x) : node(x.node) {} // 通过另一个迭代器初始化当前迭代器

    bool operator==(const self &x) const { return node == x.node; }
    bool operator!=(const self &x) const { return node != x.node; }
    // 解引用迭代器，返回当前节点存储的数据值
    reference operator*() const { return (*node).data; }

    // 通过解引用获取当前节点数据的地址
    pointer operator->() const { return &(operator*()); }

    // 对迭代器累加1，就是前进一个节点
    self &operator++()
    {
        node = (link_type)((*node).next);
        return *this;
    }

    // 后缀递增，返回当前迭代器的副本，然后将迭代器向前移动一个节点
    self operator++(int)
    {
        self tmp = *this;
        ++*this;
        return tmp;
    }

    // 对迭代器递减1，就是后退一个节点
    self &operator--()
    {
        node = (link_type)((*node).prev);
        return *this;
    }

    // 后缀递减，返回当前迭代器的副本，然后将迭代器向后移动一个节点
    self operator--(int)
    {
        self tmp = *this;
        --*this;
        return tmp;
    }

    // 返回一个指向链表第一个元素的迭代器
    // node是超尾节点，list是一个循环链表
    // 所以超尾的下一个节点即begin()
    iterator begin() { return (link_type)((*node).next); }
    iterator end() { return node; }

    bool empty() const { return node->next == node; }

    size_type size() const
    {
        size_type result = 0;
        // 全局函数，计算两个迭代器之间的距离
        distance(begin(), end(), result);
        return result;
    }

    // 取头节点的内容（元素值）
    reference front() { return *begin(); }

    // 取尾节点的内容（元素值）
    reference back() { return *(--end()); }
};

template <class T, class Alloc = alloc> // 默认使用alloc为配置器
class list
{
protected:
    typedef __list_node<T> list_node;
    typedef simple_alloc<list_node, Alloc> list_node_allocator;

    // 分配一个链表节点的内存，并返回指向该节点的指针
    link_type get_node() { return list_node_allocator::allocate(); }

    // 释放传入的节点指针p所指向的内存
    void put_node(link_type p) { list_node_allocator::deallocate(p); }

    // 创建一个链表节点，并使用传入的值x构造节点的数据成员
    link_type create_node(const T& x) {
        link_type p = get_node();
        construct(&p->data, x); // 全局函数，用于构造对象
        return p;
    }

    // 销毁一个链表节点，包括析构其数据成员并释放内存
    void destroy_node(link_type p) {
        destroy(&p->data); // 全局函数，用于析构对象
        put_node(p);
    }

public:
    typedef list_node *link_type;

protected:
    link_type node; // 只要一个指针，便可表示整个环状双向链表
};
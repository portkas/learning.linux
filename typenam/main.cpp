#include <iostream>
#include <vector>

template <typename T>
class MyClass
{
    using valueType = typename T::value_type;
};

int main()
{
    using valueType = std::vector<int>::value_type;

    return 0;
}


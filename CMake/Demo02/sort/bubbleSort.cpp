#include "sort.h"

void bubbleSort(std::vector<int> &a)
{
    int len = a.size();
    for (int i = 0; i < len - 1; i++) //需要循环次数
    {
        for (int j = 0; j < len - 1 - i; j++) //每次需要比较个数
        {
            if (a[j] > a[j + 1])
            {
                std::swap(a[j], a[j + 1]); //不满足偏序，交换
            }
        }
    }
}
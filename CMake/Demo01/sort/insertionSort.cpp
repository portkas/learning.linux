#include "sort.h"

void insertionSort(std::vector<int> &a)
{
    int len = a.size();
    for (int i = 0, j, temp; i < len - 1; i++) //需要循环次数
    {
        j = i;
        temp = a[i + 1];
        while (j >= 0 && a[j] > temp)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = temp;
    }
}
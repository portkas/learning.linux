#include <stdio.h>
#include "sort.h"

int main()
{
    std::vector<int> nums1 = {100, 1, 21, 32, 34, 23, 45, 65, 32, 3};
    std::vector<int> nums2 = {100, 1, 21, 32, 34, 23, 45, 65, 32, 3};
    std::vector<int> nums3 = {100, 1, 21, 32, 34, 23, 45, 65, 32, 3};
    bubbleSort(nums1);
    insertionSort(nums2);
    selectionSort(nums3);

    for(auto num:nums1){
        printf("%d ", num);
    }
    printf("\n");

    for(auto num:nums2){
        printf("%d ", num);
    }
    printf("\n");

    for(auto num:nums3){
        printf("%d ", num);
    }
    printf("\n");
    return 0;
}
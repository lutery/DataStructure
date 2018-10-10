//
// Created by yanghui on 2018/8/2.
//

#include "SortTestHelper.h"

int *SortTestHelper::generalNearOrderArray(int count, int swapTimes)
{
        int* arr = new int[count];
        for (int i = 0; i < count; ++i)
        {
            arr[i] = i;
        }

        std::random_device rd;
        for (int i = 0; i < swapTimes; ++i)
        {
            int posSrc = rd() % count;
            int posDst = rd() % count;
            std::swap(arr[posSrc], arr[posDst]);
        }

        return arr;
}

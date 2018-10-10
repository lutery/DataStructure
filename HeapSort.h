//
// Created by yanghui on 2018/9/21.
//

#ifndef DATASTRUCTURE_HEAPSORT_H
#define DATASTRUCTURE_HEAPSORT_H

#include "BasicSort.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <utility>

template <typename Item>
class MaxHeap
{
private:
    Item* mData;
    int mCount;
    int mCapacity;

public:
    MaxHeap(int capacity);
    ~MaxHeap();

    int size();
    bool isEmpty();
    void insert(Item item);
    void testPrint();
    Item extractMax();

private:
    void shiftUp(int k);
    void shiftDown(int k);
};

class HeapSort
{
public:
    template <typename T>
    static void heapSort1(T* arr, int length);
};

template<typename T>
void HeapSort::heapSort1(T *arr, int length)
{
    MaxHeap<T> maxHeap{ length + 1 };

    for (int i = 0; i < length; ++i)
    {
        maxHeap.insert(arr[i]);
    }

    for (int i = length - 1; i >= 0;  --i)
    {
        arr[i] = maxHeap.extractMax();
    }

//    for (int i = 0; i < length;  ++i)
//    {
//        arr[i] = maxHeap.extractMax();
//    }
}

template <typename Item>
MaxHeap<Item>::MaxHeap(int capacity)
{
    mData = new Item[capacity + 1];
    mCount = 0;
    mCapacity = capacity;
}

template <typename Item>
MaxHeap<Item>::~MaxHeap()
{
    delete[] mData;
}

template<typename Item>
bool MaxHeap<Item>::isEmpty()
{
    return mCount == 0;
}

template<typename Item>
int MaxHeap<Item>::size()
{
    return mCount;
}

template<typename Item>
void MaxHeap<Item>::insert(Item item)
{
    if (mCount > mCapacity)
    {
        int newCapacity = mCapacity * 2;
        Item* data = new Item[newCapacity];
        memset(data, 0, newCapacity);

        memcpy(data, mData, mCount);

        delete[] mData;

        mData = data;
        mCapacity = newCapacity;
    }

    mData[++mCount] = item;
    shiftUp(mCount);
}

template<typename Item>
void MaxHeap<Item>::shiftUp(int k)
{
    while (k > 1 && mData[k / 2] < mData[k])
    {
        std::swap(mData[k / 2], mData[k]);
        k /= 2;
    }
}

template<typename Item>
void MaxHeap<Item>::testPrint()
{
    for (int i = 1; i <= mCount; ++i)
    {
        std::cout << mData[i] << " ";
    }

    std::cout << std::endl;
}

template<typename Item>
Item MaxHeap<Item>::extractMax()
{

    assert(mCount > 0);

    Item maxItem = mData[1];

    std::swap(mData[1], mData[mCount]);

    mCount--;

    shiftDown(1);

    return maxItem;
}

template<typename Item>
void MaxHeap<Item>::shiftDown(int k)
{
    // 这里注意，不能使用2*k+1，因为很可能没有右孩子有左孩子导致无法进入循环
    // 进行排序
    while (2*k <= mCount)
    {
        int maxIndex = 2 * k;
        if (mCount >= (2*k + 1) && mData[maxIndex] < mData[maxIndex + 1])
        {
            maxIndex += 1;
        }

        if (mData[k] < mData[maxIndex])
        {
            std::swap(mData[k], mData[maxIndex]);
        }

        k = maxIndex;
    }
}


#endif //DATASTRUCTURE_HEAPSORT_H

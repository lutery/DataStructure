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

/**
 * 最大堆，什么是最大堆，每个节点的左右孩子都不会比父节点大
 * 该类使用的是数组的方式存储二叉树，所以每个节点的下标除以2就是其父节点
 * @tparam Item
 */
template <typename Item>
class MaxHeap
{
private:
    // 每个节点的数据类型
    Item* mData;
    // 当前存储了几个节点
    int mCount;
    // 最大能存储几个节点
    int mCapacity;

public:
    MaxHeap(int capacity);
    MaxHeap(Item arr[], int length);
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

    template <typename T>
    static void heapSort2(T* arr, int length);

    template <class T>
    static void heapSort3(T* arr, int length);

private:
    template <class T>
    static void shiftdown(T* arr, int length, int k);
};

/**
 * 堆排序第一个版本，使用insert的方法完成排序
 * @iparam T 数组的数据类型
 * @param arr 数组对象
 * @param length 数组长度 
 */
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

/**
 * 堆排序第二个版本，使用构造函数完成数组的排序
 * @tparam T 数组的数据类型
 * @param arr 数组对象
 * @param length 数组的长度
 */ 
template<typename T>
void HeapSort::heapSort2(T* arr, int length)
{
    MaxHeap<T> maxHeap{arr, length};

    for (int i = length - 1; i >= 0; --i)
    {
        arr[i] = maxHeap.extractMax();
    }
}

/**
 * 堆排序第三个版本，本地排序，不需要开辟额外的存储空间
 * @tparam T 数组的数据类型
 * @param arr 数组对象
 * @param length 数组的长度
 */ 
template <class T>
void HeapSort::heapSort3(T *arr, int length)
{
    for (int i = (length - 1) / 2; i >= 0; --i)
    {
        HeapSort::shiftdown(arr, length, i);
    }

    for (int i = length - 1; i > 0; --i)
    {
        std::swap(arr[0], arr[i]);
        HeapSort::shiftdown(arr, i, 0);
    }
}

template<class T>
void HeapSort::shiftdown(T *arr, int length, int k)
{
    while ((2 * k + 1) < length)
    {
        // 假设左孩子大于右孩子
        int maxChild = 2 * k + 1;
        // 将左孩子与右孩子进行比较，如果右孩子大于左孩子，那么保存右孩子索引
        if (length > maxChild + 1 && arr[maxChild] < arr[maxChild + 1])
        {
            maxChild += 1;
        }

        if (arr[k] >= arr[maxChild])
        {
            break;
        }

        // 将最大的孩子与父节点比较，如果大于父节点则进行交换曹祖
        std::swap(arr[k], arr[maxChild]);

        // 保存最大孩子的索引进行重新的一轮遍历
        k = maxChild;
    }
}

template <typename Item>
MaxHeap<Item>::MaxHeap(int capacity)
{
    // 多申请一个节点，因为第一个位置不用于存储节点数据
    mData = new Item[capacity + 1];
    // 初始化当前存储的数量
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

/**
 * 插入一个节点
 * @tparam Item
 * @param item
 */
template<typename Item>
void MaxHeap<Item>::insert(Item item)
{
    // 如果当前已经存储的节点数量大于等于最大容量，则重新创建新的存储空间
    if (mCount >= mCapacity)
    {
        // 重新申请新的存储空间，大小为原来的2倍，并将原来的数据拷贝到新的缓存上
        int newCapacity = mCapacity * 2;
        Item* data = new Item[newCapacity];
        memset(data, 0, newCapacity);

        memcpy(data, mData, mCount);

        delete[] mData;

        mData = data;
        mCapacity = newCapacity;
    }

    // 将当前的节点插入到二叉树最末端
    mData[++mCount] = item;
    shiftUp(mCount);
}

/**
 * 更新整个二叉树，使新插入的节点能够满足最大堆的性质
 * @tparam Item 需要进行更新节点的目前所在的索引位置
 * @param k
 */
template<typename Item>
void MaxHeap<Item>::shiftUp(int k)
{
    // 只要k大于1并且其父节点小于该节点，那么就进行交换操作，并且更新k值
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

/**
 * 获取最大的数，并更新整个二叉树
 * @tparam Item
 * @return
 */
template<typename Item>
Item MaxHeap<Item>::extractMax()
{
    assert(mCount > 0);

    Item maxItem = mData[1];

    // 将对末端的节点与第一个节点进行交换
    std::swap(mData[1], mData[mCount]);

    mCount--;

    // 将更整个二叉树
    shiftDown(1);

    return maxItem;
}

/**
 * 从顶向下的更新整个二叉树
 * @tparam Item 需要进行更新的节点位置
 * @param k
 */
template<typename Item>
void MaxHeap<Item>::shiftDown(int k)
{
    // 这里注意，不能使用2*k+1，因为很可能没有右孩子有左孩子导致无法进入循环
    // 进行排序
    while (2*k <= mCount)
    {
        // 假设左孩子大于右孩子
        int maxIndex = 2 * k;
        // 将左孩子与右孩子进行比较，如果右孩子大于左孩子，那么保存右孩子索引
        if (mCount >= (2*k + 1) && mData[maxIndex] < mData[maxIndex + 1])
        {
            maxIndex += 1;
        }

        // 将最大的孩子与父节点比较，如果大于父节点则进行交换曹祖
        if (mData[k] < mData[maxIndex])
        {
            std::swap(mData[k], mData[maxIndex]);
        }

        // 保存最大孩子的索引进行重新的一轮遍历
        k = maxIndex;
    }
}

/**
 * 构造函数，再构建堆对象的时候进行排序
 * @ tparam Item 模板类型
 * @ param arr[] 待排序的数组对象
 * @ param length 数组的长度 
 */
template<typename Item>
MaxHeap<Item>::MaxHeap(Item arr[], int length)
{
    // 创建一个比数组大于1的缓存存储数组，但是更好的办法是创建只要大于两倍的空间
    mData = new Item[length + 1];
    memcpy(mData + 1, arr, length);
    mCount = length;
    mCapacity = length;

    // 从末端父节点开始，进行排序
    for (int i = length / 2; i >= 1; --i)
    {
        shiftDown(i);
    }

//    for (int i = length; i >= 1; --i)
//    {
//        int parent = i / 2;
//
//        shiftDown(parent);
//    }

//    下面这个算法之所以会失败，主要由于对存储结构不熟悉导致的
//    因为申请的内存会比实际存储的数据多一个，即首个节点是用来存储临时最大节点使用
//    所以实际比较的数据结尾其实就是从length开始，而不是length - 1，这样就可以修复问题
//    for (int i = length - 1; i >= 1; --i)
//    {
//        int parent = i / 2;
//
//        shiftDown(parent);
//
//        if ((i - 1) / 2 == parent)
//        {
//            --i;
//        }
//    }
}


#endif //DATASTRUCTURE_HEAPSORT_H

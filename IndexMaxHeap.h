//
// Created by yanghui on 2018/11/5.
//

#ifndef DATASTRUCTURE_INDEXMAXHEAP_H
#define DATASTRUCTURE_INDEXMAXHEAP_H

#include "BasicSort.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <utility>
#include <cstring>

/**
 * 索引堆
 * 以索引的方式存储堆内容，编译在进行堆排序的时候效率稳定
 * @tparam Item
 */
template <typename Item>
class IndexMaxHeap
{
private:
    // 存储每个节点对应的索引
    int* mIndexes;
    // 每个节点的数据类型
    int* mReverse;
    Item* mData;
    // 当前存储了几个节点
    int mCount;
    // 最大能存储几个节点
    int mCapacity;

public:
    IndexMaxHeap(int capacity);
    IndexMaxHeap(Item arr[], int length);
    ~IndexMaxHeap();

    int size();
    bool isEmpty();
    void insert(Item item);
    void testPrint();
    Item extractMax();
    int extractMaxIndex();
    Item getItem(int index);
    void change(int i, Item newItem);
    bool contain(int i);

private:
    void shiftUp(int k);
    void shiftDown(int k);
};

template <typename Item>
IndexMaxHeap<Item>::IndexMaxHeap(int capacity)
{
    // 多申请一个节点，因为第一个位置不用于存储节点数据
    mData = new Item[capacity + 1];
    // 申请索引节点
    mIndexes = new int[capacity + 1];
    mReverse = new int[capacity + 1];
    for (int i = 0, count = capacity + 1; i < count; ++i)
    {
        mReverse[i] = 0;
    }

    // 初始化当前存储的数量
    mCount = 0;
    mCapacity = capacity + 1;
}

template <typename Item>
IndexMaxHeap<Item>::~IndexMaxHeap()
{
    delete[] mData;
    delete[] mIndexes;
    delete[] mReverse;
}

template<typename Item>
bool IndexMaxHeap<Item>::isEmpty()
{
    return mCount == 0;
}

template<typename Item>
int IndexMaxHeap<Item>::size()
{
    return mCount;
}

/**
 * 插入一个节点
 * @tparam Item
 * @param item
 */
template<typename Item>
void IndexMaxHeap<Item>::insert(Item item)
{
    // 如果当前已经存储的节点数量大于等于最大容量，则重新创建新的存储空间
    if (mCount >= mCapacity)
    {
        // 重新申请新的存储空间，大小为原来的2倍，并将原来的数据拷贝到新的缓存上
        int newCapacity = mCapacity * 2;
        Item* data = new Item[newCapacity];
        int* indexes = new int[newCapacity];
        int* reverse = new int[newCapacity];
        memset(data, 0, newCapacity);
        memcpy(data, mData, mCount);

        memset(indexes, 0, newCapacity);
        memcpy(indexes, mIndexes, mCount);

        memset(reverse, 0, newCapacity);
        memcpy(reverse, mReverse, mCount);

        delete[] mData;
        delete[] mIndexes;
        delete[] mReverse;

        mData = data;
        mIndexes = indexes;
        mCapacity = newCapacity;
        mReverse = reverse;
    }

    mData[mCount + 1] = item;
    mIndexes[mCount + 1] = mCount + 1;
    mReverse[mCount + 1] = mCount + 1;
    mCount++;

    shiftUp(mCount);

//    // 将当前的节点插入到二叉树最末端
//    mData[++mCount] = item;
//    // 对于新插入的节点，其索引值等于当前最大的节点数（有问题，如果进行移除节点操作，那么这个索引值可能会重复）
//    mIndexes[mCount] = mCount;
//    shiftUp(mIndexes[mCount]);
}

/**
 * 更新整个二叉树，使新插入的节点能够满足最大堆的性质
 * @tparam Item 需要进行更新节点的目前所在的索引位置
 * @param k
 */
template<typename Item>
void IndexMaxHeap<Item>::shiftUp(int k)
{
    // 只要k大于1并且其父节点小于该节点，那么就进行交换操作，并且更新k值
    while (k > 1 && mData[mIndexes[k / 2]] < mData[mIndexes[k]])
    {
        std::swap(mIndexes[k / 2], mIndexes[k]);
        mReverse[mIndexes[k / 2]] = k / 2;
        mReverse[mIndexes[k]] = k;
        k /= 2;
    }
}

template<typename Item>
void IndexMaxHeap<Item>::testPrint()
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
Item IndexMaxHeap<Item>::extractMax()
{
    assert(mCount > 0);

    Item maxItem = mData[mIndexes[1]];

    // 将对末端的节点与第一个节点进行交换
    std::swap(mIndexes[1], mIndexes[mCount]);
    mReverse[mIndexes[1]] = 1;
    mReverse[mIndexes[mCount]] = 0;

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
void IndexMaxHeap<Item>::shiftDown(int k)
{
    // 这里注意，不能使用2*k+1，因为很可能没有右孩子有左孩子导致无法进入循环
    // 进行排序
    while (2*k <= mCount)
    {
        // 假设左孩子大于右孩子
        int maxIndex = 2 * k;
        // 将左孩子与右孩子进行比较，如果右孩子大于左孩子，那么保存右孩子索引
        if (mCount >= (2*k + 1) && mData[mIndexes[maxIndex]] < mData[mIndexes[maxIndex + 1]])
        {
            maxIndex += 1;
        }

        // 将最大的孩子与父节点比较，如果大于父节点则进行交换曹祖
        if (mData[mIndexes[k]] < mData[mIndexes[maxIndex]])
        {
            std::swap(mIndexes[k], mIndexes[maxIndex]);
            mReverse[mIndexes[k]] = k;
            mReverse[mIndexes[maxIndex]] = maxIndex;
        }

        // 保存最大孩子的索引进行重新的一轮遍历
        k = maxIndex;
    }
}

template<typename Item>
IndexMaxHeap<Item>::IndexMaxHeap(Item arr[], int length)
{
    mData = new Item[length + 1];
    mIndexes = new int[length + 1];
    memcpy(mData + 1, arr, length);

    for (int i = 0, count = length + 1; i < count; ++i)
    {
        mIndexes[i] = i;
    }

    mReverse = new int[length + 1];
    for (int i = 0, count = length + 1; i < count; ++i)
    {
        mReverse[i] = 0;
    }

    mCount = length;
    mCapacity = length;

    for (int i = length / 2; i >= 1; --i)
    {
        shiftDown(i);
    }
}

template<typename Item>
int IndexMaxHeap<Item>::extractMaxIndex()
{
    assert(mCount > 1);

    int ret = mIndexes[1] - 1;
    std::swap(mIndexes[1], mIndexes[mCount]);
    mReverse[mIndexes[1]] = 1;
    mReverse[mIndexes[mCount]] = 0;

    mCount--;
    shiftDown(1);

    return ret;
}

template<typename Item>
Item IndexMaxHeap<Item>::getItem(int index)
{
//    assert((index + 1) < mCount);
    assert(contain(index));

    return mData[index + 1];
}

template<typename Item>
void IndexMaxHeap<Item>::change(int i, Item newItem)
{
    if (!this->contain(i))
    {
        return;
    }

    mData[i + 1] = newItem;
    this->shiftUp(mReverse[i + 1]);
    this->shiftDown(mReverse[i + 1]);

//    for (int j = 0; j <= mCount; ++j)
//    {
//        if (mIndexes[j] == index)
//        {
//            this->shiftDown(j);
//            this->shiftUp(j);
//            break;
//        }
//    }
}

template<typename Item>
bool IndexMaxHeap<Item>::contain(int i)
{
    assert(i + 1 >= 0 && i + 1 <= mCapacity);
    return mReverse[i + 1] != 0;
}


#endif //DATASTRUCTURE_INDEXMAXHEAP_H

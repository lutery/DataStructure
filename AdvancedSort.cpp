//
// Created by yanghui on 2018/8/6.
//

#include "AdvancedSort.h"
#include <iostream>

/**
 * 第n个节点的父节点索引
 * @param n
 * @return
 */
int TopN::parent(int n)
{
    return (n - 1) / 2;
}

/**
 * 第n个节点的左节点
 * @param n
 * @return
 */
int TopN::left(int n)
{
    return 2 * n + 1;
}

/**
 * 第n个节点的右节点
 * @param n
 * @return
 */
int TopN::right(int n)
{
    return 2 * n + 2;
}

/**
 * 首先将数组中的前n个树构建一个二分树，从小往大排列
 * @param n
 * @param data
 * @param length
 */
void TopN::buildHeap(int n, int *data, int length)
{

    assert(n <= length);

    for (int i = 1; i < n; ++i)
    {
        int t = i;

        // 如果父节点大于子节点大于当前节点，那么就调换两个节点的位置
        while (t != 0 && data[parent(t)] > data[t])
        {
            int temp = data[t];
            data[t] = data[parent(t)];
            data[parent(t)] = temp;
            t = parent(t);
        }
    }
}

/**
 * 当顶端最小节点被数组中新的最小数替换的时候，那么就开始重新的循环遍历整个数，将新加入的数位置调整到合适的位置
 * @param i
 * @param n
 * @param data
 * @param length
 */
void TopN::adjust(int i, int n, int *data, int length)
{
    if (data[i] <= data[0])
    {
        return;
    }

    int temp = data[i];
    data[i] = data[0];
    data[0] = temp;

    int t = 0;
    while ((left(t) < n && data[t] > data[left(t)])
            || (right(t) < n && data[t] > data[right(t)]))
    {
        if (right(t) < n && data[right(t)] < data[left(t)])
        {
            temp = data[t];
            data[t] = data[right(t)];
            data[right(t)] = temp;
            t = right(t);
        }
        else
        {
            temp = data[t];
            data[t] = data[left(t)];
            data[left(t)] = temp;
            t = left(t);
        }
    }
}

/**
 * 寻找前n个最大数，首先线构建一个n个数据的堆，然后在不断的将剩下的数加入调整
 * @param n
 * @param data
 * @param length
 */
void TopN::findTopN(int n, int *data, int length)
{
    buildHeap(n, data, length);

    for (int i = n; i < length; ++i)
    {
        adjust(i, n, data, length);
    }
}

/**
 * 打印调整后的元素
 * @param data
 * @param length
 */
void TopN::print(int *data, int length)
{
    for (int i = 0;  i < length; ++i)
    {
        std::cout << data[i] << " ";
    }

    std::cout << std::endl;
}

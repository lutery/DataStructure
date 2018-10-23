//
// Created by yanghui on 2018/8/6.
//

#ifndef DATASTRUCTURE_ADVANCEDSORT_H
#define DATASTRUCTURE_ADVANCEDSORT_H


#include "BasicSort.h"
#include <random>
#include <algorithm>
#include <iostream>

//进阶排序
class AdvancedSort {

private:
    template <typename T>
    static void innerMergeSort(T* arr, int start, int end);

    template <typename T>
    static void innserMegeSort(T* arr, int start, int middle, int end);

    template <typename T>
    static void innerQuickSort(T* arr, int start, int end);

    template <typename T>
    static void innerQuickSort2(T* arr, int start, int end);

    template <typename T>
    static void innerQuickSort3(T* arr, int start, int end);

public:
    template <typename T>
    static void mergeSort(T* arr, int length);

    template <typename T>
    static void mergeSortBU(T* arr, int length);

    template <typename T>
    static void quickSort(T* arr, int length);

    template <typename T>
    static void quickSort2(T* arr, int length);

    template <typename T>
    static void quickSort3(T* arr, int length);
};

/**
 * 归并排序
 * @tparam T
 * @param arr
 * @param length
 */
template<typename T>
void AdvancedSort::mergeSort(T *arr, int length)
{
    AdvancedSort::innerMergeSort(arr, 0, length - 1);
}

/**
 * 归并排序
 * @tparam T
 * @param arr
 * @param start
 * @param end
 */
template<typename T>
void AdvancedSort::innerMergeSort(T *arr, int start, int end)
{
//    if (start >= end)
//    {
//        return;
//    }

    // 当长度小于指定的长度时，采用插入排序会更加的快速
    if ((end - start) <= 25)
    {
        BasicSort::insertSortRange(arr, start, end);
        return;
    }

    int middle = start + (end - start) / 2;

    // 将每次要排序的序列分为前半部分，后半部分，等前后两部分排序完成后，进行前后两部分的组合
    AdvancedSort::innerMergeSort(arr, start, middle);
    AdvancedSort::innerMergeSort(arr, middle + 1, end);
    AdvancedSort::innserMegeSort(arr, start, middle, end);
}

/**
 * 将排序完成的前后两部分队列组合在一起
 * @tparam T
 * @param arr
 * @param start
 * @param middle
 * @param end
 */
template<typename T>
void AdvancedSort::innserMegeSort(T *arr, int start, int middle, int end)
{
    // 原队列数据备份
    int copyLength = end - start + 1;
    T copyArr[copyLength];
    for (int i = 0, j = start; i < copyLength; ++i, ++j)
    {
        copyArr[i] = arr[j];
    }

    // 从两个队列的头开始进行遍历，直到所有的元素都遍历一遍
    for (int i = start, j = middle + 1, k = start; k <= end; ++k)
    {
        // 当前面队列全部遍历完成
        // 此时将后队列剩余的内容全部填充
        if (i > middle)
        {
            arr[k] = copyArr[j - start];
            ++j;
        }
        // 当后面的队列全部遍历完成
        // 此时将前面队列剩余的内容全部填充
        else if (j > end)
        {
            arr[k] = copyArr[i - start];
            ++i;
        }
        // 比如前后两个队列大小，将小的数填写到队列中
        else if (copyArr[i - start] < copyArr[j - start])
        {
            arr[k] = copyArr[i - start];
            ++i;
        }
        else
        {
            arr[k] = copyArr[j - start];
            ++j;
        }
    }
}

/**
 * 归并排序，由底向上
 * @tparam T
 * @param arr
 * @param length
 */
template<typename T>
void AdvancedSort::mergeSortBU(T *arr, int length)
{
    // 由宽度为1开始，根据归并排序的特点，排序宽度为1、2、4、8......
    for (int sz = 1; sz <= length; sz += sz)
    {
        // 每块进行归并排序两块进行排序
        for (int i = 0; (i + sz) < length; i += (sz + sz))
        {
            AdvancedSort::innserMegeSort(arr, i , i + sz - 1, std::min(i + sz + sz - 1, length - 1));
        }
    }
}

/**
 * 快速排序
 * @tparam T
 * @param arr
 * @param length
 */
template<typename T>
void AdvancedSort::quickSort(T *arr, int length)
{
    srand(time(NULL));
    AdvancedSort::innerQuickSort(arr, 0, length - 1);
//    int l = 0;
//    int j = 0;
//    int i = 1;
//
//    T first = arr[l];
//
//    for (int x = 1; x < length; ++x)
//    {
//        if (first < arr[l + x])
//        {
//            std::swap(arr[l + x], arr[j + 1])
//            ++j;
//
//        }
//        else
//        {
//            ++i;
//        }
//    }
//
//    std::swap(arr[l], arr[j]);
//
//    AdvancedSort::innerQuickSort(arr, l, j - 1);
//    AdvancedSort::innerQuickSort(arr, j + 1, i - 1);
}

/**
 * 快速排序
 * @tparam T
 * @param arr
 * @param start
 * @param end
 */
template <typename T>
void AdvancedSort::innerQuickSort(T *arr, int start, int end)
{
//    if (start >= end)
//    {
//        return;
//    }

    if (abs(start - end) <= 15)
    {
        BasicSort::insertSortRange(arr, start, end);
        return;
    }

//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution distribution(start, end);
//
//    std::swap(arr[start], arr[distribution(gen)]);

    // 快速排序原理：随机选取数组中的一个数与第一个数进行交换
    // 从第二个节点进行比较，当当前遍历的节点小于第一个节点，
    // 将该节点交换到左边
    std::swap(arr[start], arr[rand() % (end - start + 1) + start]);

    int l = start;
    int j = start;

    T first = arr[start];

    for (int x = l + 1; x <= end; ++x)
    {
        if (first > arr[x])
        {
            std::swap(arr[x], arr[j + 1]);
            ++j;
        }
    }

    // 当遍历完毕之后，将第一个节点与最后一个小于第一个节点进行交换
    // 然后将左右两个部分进行分别快速排序，实现整个数组的从小到大的排序
    std::swap(arr[start], arr[j]);
    AdvancedSort::innerQuickSort(arr, l, j - 1);
    AdvancedSort::innerQuickSort(arr, j + 1, end);
}

/**
 * 快速排序版本2，与版本1对比，多了一个左右同时遍历的流程
 * @tparam T
 * @param arr
 * @param start 当前数组的第一个元素索引
 * @param end 当前数组最后一个元素索引
 */
template<typename T>
void AdvancedSort::innerQuickSort2(T *arr, int start, int end)
{
    if ((end - start) <= 15)
    {
        BasicSort::insertSortRange(arr, start, end);
        return;
    }

    // 随机选择一个元素与第一个元素交换
    std::swap(arr[start], arr[rand() % (end - start + 1) + start]);

    int l = start;
    int i = l + 1;
    int r = end;
    int j = r;

    // 存储第一个元素
    T V = arr[l];

    // 从左开始开始遍历，找到第一个大于v的元素
    // 从右开始遍历，找到第一个小于v的元素
    // 将两个元素进行交换
    // 最后将v元素与停止遍历的元素进行交换
    while (i < j)
    {
        for (; i < j; ++i)
        {
            if (arr[i] > V)
            {
                break;
            }
        }

        for (; j >= i; --j)
        {
            if (arr[j] < V)
            {
                break;
            }
        }

        if (i >= j)
        {
            break;
        }

        std::swap(arr[i++], arr[j--]);
    }

    std::swap(arr[l] , arr[i]);
    AdvancedSort::innerQuickSort2(arr, l, i);
    AdvancedSort::innerQuickSort2(arr, j, r);
}

/**
 * 快速排序版本2
 * @tparam T
 * @param arr
 * @param length
 */
template<typename T>
void AdvancedSort::quickSort2(T *arr, int length)
{
    srand(time(NULL));
    AdvancedSort::innerQuickSort2(arr, 0, length - 1);
}

/**
 * 快速排序版本3
 * @tparam T
 * @param arr
 * @param start 起始索引
 * @param end 结束索引
 */
template <typename T>
void AdvancedSort::innerQuickSort3(T *arr, int start, int end)
{
    // 对于小规模数组, 使用插入排序进行优化
//    if( r - l <= 15 ){
//        BasicSort::insertSortRange(arr,l,r);
//        return;
//    }
//
//    // 随机在arr[l...r]的范围中, 选择一个数值作为标定点pivot
//    std::swap( arr[l], arr[rand()%(r-l+1)+l ] );
//
//    T v = arr[l];
//
//    int lt = l;     // arr[l+1...lt] < v
//    int gt = r + 1; // arr[gt...r] > v
//    int i = l+1;    // arr[lt+1...i) == v
//    while( i < gt ){
//        if( arr[i] < v ){
//            std::swap( arr[i], arr[lt+1]);
//            i ++;
//            lt ++;
//        }
//        else if( arr[i] > v ){
//            std::swap( arr[i], arr[gt-1]);
//            gt --;
//        }
//        else{ // arr[i] == v
//            i ++;
//        }
//    }
//
//    std::swap( arr[l] , arr[lt] );
//
//    innerQuickSort3(arr, l, lt-1);
//    innerQuickSort3(arr, gt, r);

    if ((end - start) <= 15)
    {
        BasicSort::insertSortRange(arr, start, end);
        return;
    }

    // 这个版本的快速排序，在前面版本2的基础上增加了等于随机选取的比较点
    // 进行排序，等于每次排序，将整个数组分为三个部分，进一步减少了每次需要
    // 进行排序的数组长度，进一步的增块了速度
    std::swap(arr[start], arr[rand() % (end - start + 1) + start]);

    T V = arr[start];

    int lt = start; // lt索引表示等于v的队列起始索引
    int gt = end + 1; // gt索引表示大于v的队列起始索引
    int i = start + 1; // i索引表示当前遍历的位置

    while (i < gt)
    {
        // 如果当前的索引大于V，那么将当前节点与最后一个节点进行交换
        // 但不改变索引i的值
        if (arr[i] > V)
        {
            std::swap(arr[i], arr[gt - 1]);
            --gt;
        }
        // 如果当前索引小于v，将当前索引lt索引进行交换
        // 同时改变lt i两个索引值
        else if (arr[i] < V)
        {
            std::swap(arr[i], arr[lt + 1]);
            lt++;
            i++;
        }
        // 如果只是等于，进改变i索引
        else
        {
            ++i;
        }
    }

    std::swap(arr[start], arr[lt]);
    AdvancedSort::innerQuickSort3(arr, start, lt - 1);
    AdvancedSort::innerQuickSort3(arr, gt, end);
}

/**
 * 快速排序版本3
 * @tparam T
 * @param arr
 * @param length
 */
template<typename T>
void AdvancedSort::quickSort3(T *arr, int length)
{
    srand(time(NULL));
    AdvancedSort::innerQuickSort3(arr, 0, length - 1);
}


#endif //DATASTRUCTURE_ADVANCEDSORT_H

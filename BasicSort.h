//
// Created by yanghui on 2018/8/6.
//

#ifndef DATASTRUCTURE_BASICSORT_H
#define DATASTRUCTURE_BASICSORT_H

#include <utility>

//基础排序
class BasicSort {

public:
    template<typename T>
    static void insertSort(T* arr, int length);

    template<typename T>
    static void selectSort(T* arr, int length);

    template <typename T>
    static void shellSort(T* arr, int length);

    template <typename T>
    static void bubbleSort(T* arr, int length);

    template <typename T>
    static void insertSortRange(T* arr, int left, int right);
};

/**
 * 指定范围内的插入排序
 * @tparam T
 * @param arr
 * @param left
 * @param right
 */
template<typename T>
void BasicSort::insertSortRange(T *arr, int left, int right)
{
    int length = right - left + 1;

    if (length <= 0)
    {
        return;
    }

    // 插入排序的原理在于从第二各元素开始，不断的将当前遍历的元素
    // 向前比较，直到找到右边大于这个元素，左边小于这个元素的位置
    // 直到遍历到最后一个元素即可完成排序
    for (int i = 1; i < length; ++i)
    {
        T tmp = arr[left + i];

        int j = i;
        for (; j > 0 && arr[left + j - 1] > tmp; --j)
        {
            arr[left + j] = arr[left + j - 1];
        }

        if (j != i)
        {
            arr[left + j] = tmp;
        }
    }
}

/**
 * 默认全队列插入排序
 * @tparam T
 * @param arr
 * @param length
 */
template<typename T>
void BasicSort::insertSort(T *arr, int length)
{
    for (int i = 1; i < length; ++i)
    {
        T tmp = arr[i];

        int j = i;
        for (; j > 0 && arr[j - 1] > tmp; --j)
        {
            arr[j] = arr[j - 1];
        }

        if (j != i)
        {
            arr[j] = tmp;
        }
    }

//    for (int i = 1; i < length; ++i)
//    {
//        for (int j = i; j > 0 && arr[j] < arr[j - 1]; --j)
//        {
//            // 由于插入排序的特性，只需要比较前后两个相邻的元素大小即可
////            if (arr[j] < arr[j - 1])
////            {
//                std::swap(arr[j], arr[j - 1]);
////            }
////            else
////            {
//                // 由于插入排序的特性，如果前一个元素没有比后一个元素大，那么就可以直接跳出循环
////                break;
////            }
//        }
//    }
}

/**
 * 选择排序
 * @tparam T
 * @param arr
 * @param length
 */
template<typename T>
void BasicSort::selectSort(T *arr, int length)
{
    // 从第一个元素开始，寻找最小的元素，将其排列当前遍历的开头位置
    for (int i = 0; i < length; ++i)
    {
        int minIndex = i;

        for (int j = i + 1; j < length; ++j)
        {
            if (arr[minIndex] > arr[j])
            {
                minIndex = j;
            }
        }

        if (i != minIndex)
        {
            std::swap(arr[i], arr[minIndex]);
        }
    }
}

template<typename T>
void BasicSort::shellSort(T *arr, int length)
{

}

/**
 * 冒泡排序
 * @tparam T
 * @param arr
 * @param length
 */
template<typename T>
void BasicSort::bubbleSort(T *arr, int length)
{
    // 从最后一个元素开始，不断的向上遍历，相邻的
    // 两个元素大小顺序相反的情况下进行交换
    for (int i = 0; i < length; ++i)
    {
        for (int j = length - 1; j > i; --j)
        {
            if (arr[j] < arr[j - 1])
            {
                std::swap(arr[j], arr[j - 1]);
            }
        }
    }
}


#endif //DATASTRUCTURE_BASICSORT_H

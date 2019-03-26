//
// Created by yanghui on 2018/8/2.
//

#ifndef DATASTRUCTURE_SORTTESTHELPER_H
#define DATASTRUCTURE_SORTTESTHELPER_H

#include <random>
#include <chrono>
#include <iostream>
#include <functional>

namespace SortTestHelper{

    template <typename  T>
    bool checkSort(T* arr, int length, std::function<bool(T&, T&)> compare)
    {
        for (int i = 1; i < length; ++i)
        {
            if (!compare(arr[i - 1], arr[i]))
            {
                std::cout  << "index " << i << " ";

                return false;
            }
        }

        return true;
    }

    template <typename  T>
    bool checkSortBTS(T* arr, int length)
    {
        // 由于c++的模版自动推导类型对多级模版、指针和引用之间的推导类型存在差异
        // 所以这里需要显示的指明模版的类型
        return SortTestHelper::checkSort<T>(arr, length, [](T& a, T& b) -> bool {
            return a >= b;
        });
    }

    template <typename  T>
    bool checkSortSTB(T* arr, int length)
    {
        return SortTestHelper::checkSort<T>(arr, length, [](T& a, T& b) -> bool {
            return b >= a;
        });
    }

    template<typename T>
    T* generalAssignArray(const std::initializer_list<T> array)
    {
        T* t = new T[array.size()];

        int i = 0;
        for (auto& a : array)
        {
            t[i++] = a;
        }

        return t;
    }

    template <typename T>
    T* generalRandomArray(int count, T rangeL, T rangeR)
    {
        assert(rangeL <= rangeR);

        unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::mt19937 randGenerator(seed);

        if (typeid(T) == typeid(float) || typeid(T) == typeid(double) || typeid(T) == typeid(long double))
        {
            std::uniform_real_distribution<T> dist(rangeL, rangeR);

            T* testA = new T[count];

            for (int i = 0; i < count; ++i)
            {
                testA[i] = dist(randGenerator);
            }

            return testA;
        }
        else
        {
            std::uniform_int_distribution<T> dist(rangeL, rangeR);

            T* testA = new T[count];

            for (int i = 0; i < count; ++i)
            {
                testA[i] = dist(randGenerator);
            }

            return testA;
        }
    }

    int* generalNearOrderArray(int count, int swapTimes);

    template<typename T>
    T* copyArray(T* srcArr, int length)
    {
        T* dstArr = new T[length];

        memcpy(dstArr, srcArr, sizeof(T) * length);

        return dstArr;
    }
}

#endif //DATASTRUCTURE_SORTTESTHELPER_H

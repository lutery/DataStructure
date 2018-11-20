#include <iostream>
#include <utility>
#include "ToolUtil.h"
#include "SortTestHelper.h"
#include "BasicSort.h"
#include "AdvancedSort.h"
#include "HeapSort.h"

//ToDo 写出所有排序算法的时间复杂度以及空间复杂度

template<class TimeUnit, class Fun>
void testRandomSort(int* testArr, int length, Fun&& fun, std::string sortName)
{
    std::cout << "-------------------" << sortName << "-------------------" << std::endl;

    int* testCurArr = SortTestHelper::copyArray(testArr, length);

    int clockCount = ToolUtil::funNClock<TimeUnit>(fun, testCurArr, length);

    std::cout << sortName << " microseconds is " << clockCount << std::endl;

    std::cout << std::endl << "sort " << (SortTestHelper::checkSortSTB<int>(testCurArr, length) ? "success" : "failed") << std::endl;

    delete[] testCurArr;

    std::cout << std::endl;
}

int generatorRnage(int min, int max)
{
    unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 rand_generator(seed);
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rand_generator);
}

void testRandomArr()
{
    std::cout << "**********************************testRandomArr**********************************" << std::endl;

    std::cout << std::endl;

    int testLength = generatorRnage(100, 10000);

//    if (testLength < 100)
//    {
//        testLength = 100;
//    }

    std::cout << "testLength = " << testLength << std::endl;

    int* testSelect = SortTestHelper::generalRandomArray(testLength, 0, testLength);

    for (int i = 0; i < 100; ++i)
    {
        std::cout << testSelect[i] << " ";
    }

    std::cout << std::endl;

    testRandomSort<std::chrono::microseconds>(testSelect, testLength, BasicSort::selectSort<int>, "selectSort");
    testRandomSort<std::chrono::microseconds>(testSelect, testLength, BasicSort::insertSort<int>, "insertSort");
    testRandomSort<std::chrono::microseconds>(testSelect, testLength, BasicSort::bubbleSort<int>, "testBubble");
    testRandomSort<std::chrono::microseconds>(testSelect, testLength, AdvancedSort::mergeSort<int>, "mergeSort");
    testRandomSort<std::chrono::microseconds>(testSelect, testLength, AdvancedSort::mergeSortBU<int>, "mergeSortBU");
    testRandomSort<std::chrono::microseconds>(testSelect, testLength, AdvancedSort::quickSort<int>, "quickSort");
    testRandomSort<std::chrono::microseconds>(testSelect, testLength, AdvancedSort::quickSort2<int>, "quickSort2");
    testRandomSort<std::chrono::microseconds>(testSelect, testLength, AdvancedSort::quickSort3<int>, "quickSort3");
    testRandomSort<std::chrono::microseconds>(testSelect, testLength, HeapSort::heapSort1<int>, "heapSort1");
    testRandomSort<std::chrono::microseconds>(testSelect, testLength, HeapSort::heapSort2<int>, "heapSort2");
    testRandomSort<std::chrono::microseconds>(testSelect, testLength, HeapSort::heapSort3<int>, "heapSort3");
    testRandomSort<std::chrono::microseconds>(testSelect, testLength, HeapSort::indexHeapSort1<int>, "indexHeapSort1");
    testRandomSort<std::chrono::microseconds>(testSelect, testLength, HeapSort::indexHeapSort2<int>, "indexHeapSort2");

    delete[] testSelect;
}

void testNearOrderArr()
{
    std::cout << std::endl << "**********************************testNearOrderArr**********************************" << std::endl;

//    int testLength = 10000;
    int testLength = generatorRnage(100, 10000);

//    if (testLength < 100)
//    {
//        testLength = 100;
//    }

    std::cout << "testLength = " << testLength << std::endl;

    int* testSelect = SortTestHelper::generalNearOrderArray(testLength, 10);

    for (int i = 0; i < 100; ++i)
    {
        std::cout << testSelect[i] << " ";
    }

    std::cout << std::endl;

    testRandomSort<std::chrono::microseconds>(testSelect, testLength, BasicSort::selectSort<int>, "selectSort");
    testRandomSort<std::chrono::microseconds>(testSelect, testLength, BasicSort::insertSort<int>, "insertSort");
    testRandomSort<std::chrono::microseconds>(testSelect, testLength, BasicSort::bubbleSort<int>, "testBubble");
    testRandomSort<std::chrono::microseconds>(testSelect, testLength, AdvancedSort::mergeSort<int>, "mergeSort");
    testRandomSort<std::chrono::microseconds>(testSelect, testLength, AdvancedSort::mergeSortBU<int>, "mergeSortBU");
    testRandomSort<std::chrono::microseconds>(testSelect, testLength, AdvancedSort::quickSort<int>, "quickSort");
    testRandomSort<std::chrono::microseconds>(testSelect, testLength, AdvancedSort::quickSort2<int>, "quickSort2");
    testRandomSort<std::chrono::microseconds>(testSelect, testLength, AdvancedSort::quickSort3<int>, "quickSort3");
    testRandomSort<std::chrono::microseconds>(testSelect, testLength, HeapSort::heapSort1<int>, "heapSort1");
    testRandomSort<std::chrono::microseconds>(testSelect, testLength, HeapSort::heapSort2<int>, "heapSort2");
    testRandomSort<std::chrono::microseconds>(testSelect, testLength, HeapSort::heapSort3<int>, "heapSort3");
    testRandomSort<std::chrono::microseconds>(testSelect, testLength, HeapSort::indexHeapSort1<int>, "indexHeapSort1");
    testRandomSort<std::chrono::microseconds>(testSelect, testLength, HeapSort::indexHeapSort2<int>, "indexHeapSort2");

    delete[] testSelect;
}

int main()
{
    std::cout << "Hello, World!" << std::endl;

    testRandomArr();
    testNearOrderArr();

    const int heapLength = 10;
    const int insertLength = 10;
    MaxHeap<int> maxHeap{heapLength};
    std::cout << maxHeap.size() << std::endl;

    srand(time(NULL));
    for (int i = 0; i < insertLength; ++i)
    {
        maxHeap.insert(rand() % 1000);
    }

    maxHeap.testPrint();

    int maxArray[insertLength];
    memset(maxArray, 0, insertLength);
    int indexMaxArray = 0;

    while (!maxHeap.isEmpty())
    {
        int current = maxHeap.extractMax();
        maxArray[indexMaxArray++] = current;
        std::cout << current << " ";
    }

    std::cout << std::endl << "sort " << (SortTestHelper::checkSortBTS<int>(maxArray, insertLength) ? "success" : "failed") << std::endl;

    return 0;
}
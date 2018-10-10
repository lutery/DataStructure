#include <iostream>
#include <utility>
#include "ToolUtil.h"
#include "SortTestHelper.h"
#include "BasicSort.h"
#include "AdvancedSort.h"
#include "HeapSort.h"

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

void testRandomArr()
{
    std::cout << "----------testRandomArr----------" << std::endl;

    std::cout << std::endl;

    int testLength = 10000;

    if (testLength < 100)
    {
        testLength = 100;
    }

    int* testSelect = SortTestHelper::generalRandomArray(testLength, 0, testLength);

    for (int i = 0; i < 100; ++i)
    {
        std::cout << testSelect[i] << " ";
    }

    std::cout << std::endl;

    int* testInsert = SortTestHelper::copyArray(testSelect, testLength);
    int* testBubble = SortTestHelper::copyArray(testSelect, testLength);
    int* testMerge = SortTestHelper::copyArray(testSelect, testLength);
    int* testMergeBU = SortTestHelper::copyArray(testSelect, testLength);
    int* testQuick = SortTestHelper::copyArray(testSelect, testLength);
    int* testQuick2 = SortTestHelper::copyArray(testSelect, testLength);
    int* testQuick3 = SortTestHelper::copyArray(testSelect, testLength);
    int* testHeap1 = SortTestHelper::copyArray(testSelect, testLength);

    std::cout << std::endl;

    //-----------------------------------------//

    int clockCount = ToolUtil::funNClock<std::chrono::microseconds>(BasicSort::selectSort<int>, testSelect, testLength);

    std::cout << "selectSort microseconds is " << clockCount << std::endl;

    for (int i = 0; i < 100; ++i)
    {
        std::cout << testSelect[i] << " ";
    }

    std::cout << std::endl;

    //-----------------------------------------//

    clockCount = ToolUtil::funNClock<std::chrono::microseconds>(BasicSort::insertSort<int>, testInsert, testLength);

    std::cout << "insertSort microseconds is " << clockCount << std::endl;

    for (int i = 0; i < 100; ++i)
    {
        std::cout << testInsert[i] << " ";
    }

    std::cout << std::endl;

    //-----------------------------------------//

    clockCount = ToolUtil::funNClock<std::chrono::microseconds>(BasicSort::bubbleSort<int>, testBubble, testLength);

    std::cout << "bubbleSort microseconds is " << clockCount << std::endl;

    for (int i = 0; i < 100; ++i)
    {
        std::cout << testBubble[i] << " ";
    }

    std::cout << std::endl;

    //-----------------------------------------//

    clockCount = ToolUtil::funNClock<std::chrono::microseconds>(AdvancedSort::mergeSort<int>, testMerge, testLength);

    std::cout << "mergeSort microseconds is " << clockCount << std::endl;

    for (int i = 0; i < 100; ++i)
    {
        std::cout << testMerge[i] << " ";
    }

    std::cout << std::endl;

    //-----------------------------------------//

    clockCount = ToolUtil::funNClock<std::chrono::microseconds>(AdvancedSort::mergeSortBU<int>, testMergeBU, testLength);

    std::cout << "mergeSortBU microseconds is " << clockCount << std::endl;

    for (int i = 0; i < 100; ++i)
    {
        std::cout << testMergeBU[i] << " ";
    }

    std::cout << std::endl;

    //-----------------------------------------//

    clockCount = ToolUtil::funNClock<std::chrono::microseconds>(AdvancedSort::quickSort<int>, testQuick, testLength);

    std::cout << "quickSort microseconds is " << clockCount << std::endl;

    for (int i = 0; i < 100; ++i)
    {
        std::cout << testQuick[i] << " ";
    }

    std::cout << std::endl;

    //-----------------------------------------//

    clockCount = ToolUtil::funNClock<std::chrono::microseconds>(AdvancedSort::quickSort2<int>, testQuick2, testLength);

    std::cout << "quickSort2 microseconds is " << clockCount << std::endl;

    for (int i = 0; i < 100; ++i)
    {
        std::cout << testQuick2[i] << " ";
    }

    std::cout << std::endl;

    //-----------------------------------------//

    clockCount = ToolUtil::funNClock<std::chrono::microseconds>(AdvancedSort::quickSort3<int>, testQuick3, testLength);

    std::cout << "quickSort3 microseconds is " << clockCount << std::endl;

    for (int i = 0; i < 100; ++i)
    {
        std::cout << testQuick3[i] << " ";
    }

    std::cout << std::endl;

    //-----------------------------------------//
    testRandomSort<std::chrono::microseconds>(testHeap1, testLength, HeapSort::heapSort1<int>, "heapSort1");

//    clockCount = ToolUtil::funNClock<std::chrono::microseconds>(HeapSort::heapSort1<int>, testHeap1, testLength);
//
//    std::cout << "heapSort1 microseconds is " << clockCount << std::endl;
//
//    for (int i = 0; i < 100; ++i)
//    {
//        std::cout << testHeap1[i] << " ";
//    }
//
//    std::cout << std::endl;

    delete[] testSelect;
    delete[] testInsert;
    delete[] testBubble;
    delete[] testMerge;
    delete[] testMergeBU;
    delete[] testQuick;
    delete[] testQuick2;
    delete[] testQuick3;
    delete[] testHeap1;
}

void testNearOrderArr()
{
    std::cout << std::endl << "----------testNearOrderArr----------" << std::endl;

    int testLength = 10000;

    if (testLength < 100)
    {
        testLength = 100;
    }

    int* testSelect = SortTestHelper::generalNearOrderArray(testLength, 10);

    for (int i = 0; i < 100; ++i)
    {
        std::cout << testSelect[i] << " ";
    }

    std::cout << std::endl;

    int* testInsert = SortTestHelper::copyArray(testSelect, testLength);
    int* testBubble = SortTestHelper::copyArray(testSelect, testLength);
    int* testMerge = SortTestHelper::copyArray(testSelect, testLength);
    int* testMergeBU = SortTestHelper::copyArray(testSelect, testLength);
    int* testQuick = SortTestHelper::copyArray(testSelect, testLength);
    int* testQuick2 = SortTestHelper::copyArray(testSelect, testLength);
    int* testQuick3 = SortTestHelper::copyArray(testSelect, testLength);
    int* testHeap1 = SortTestHelper::copyArray(testSelect, testLength);

    std::cout << std::endl;

    int clockCount = ToolUtil::funNClock<std::chrono::microseconds>(BasicSort::selectSort<int>, testSelect, testLength);

    std::cout << "selectSort microseconds is " << clockCount << std::endl;

    for (int i = 0; i < 100; ++i)
    {
        std::cout << testSelect[i] << " ";
    }

    std::cout << std::endl;

    clockCount = ToolUtil::funNClock<std::chrono::microseconds>(BasicSort::insertSort<int>, testInsert, testLength);

    std::cout << "insertSort microseconds is " << clockCount << std::endl;

    for (int i = 0; i < 100; ++i)
    {
        std::cout << testInsert[i] << " ";
    }

    std::cout << std::endl;

    clockCount = ToolUtil::funNClock<std::chrono::microseconds>(AdvancedSort::mergeSort<int>, testMerge, testLength);

    std::cout << "mergeSort microseconds is " << clockCount << std::endl;

    for (int i = 0; i < 100; ++i)
    {
        std::cout << testMerge[i] << " ";
    }

    std::cout << std::endl;

    clockCount = ToolUtil::funNClock<std::chrono::microseconds>(AdvancedSort::mergeSortBU<int>, testMergeBU, testLength);

    std::cout << "mergeSortBU microseconds is " << clockCount << std::endl;

    for (int i = 0; i < 100; ++i)
    {
        std::cout << testMergeBU[i] << " ";
    }

    std::cout << std::endl;

    clockCount = ToolUtil::funNClock<std::chrono::microseconds>(AdvancedSort::quickSort<int>, testQuick, testLength);

    std::cout << "testQuick microseconds is " << clockCount << std::endl;

    for (int i = 0; i < 100; ++i)
    {
        std::cout << testQuick[i] << " ";
    }

    std::cout << std::endl;

    clockCount = ToolUtil::funNClock<std::chrono::microseconds>(AdvancedSort::quickSort2<int>, testQuick2, testLength);

    std::cout << "testQuick2 microseconds is " << clockCount << std::endl;

    for (int i = 0; i < 100; ++i)
    {
        std::cout << testQuick2[i] << " ";
    }

    std::cout << std::endl;

    clockCount = ToolUtil::funNClock<std::chrono::microseconds>(AdvancedSort::quickSort3<int>, testQuick3, testLength);

    std::cout << "testQuick3 microseconds is " << clockCount << std::endl;

    for (int i = 0; i < 100; ++i)
    {
        std::cout << testQuick3[i] << " ";
    }

    std::cout << std::endl;

    clockCount = ToolUtil::funNClock<std::chrono::microseconds>(HeapSort::heapSort1<int>, testHeap1, testLength);

    std::cout << "heapSort1 microseconds is " << clockCount << std::endl;

    for (int i = 0; i < 100; ++i)
    {
        std::cout << testHeap1[i] << " ";
    }

    std::cout << std::endl;

    delete[] testSelect;
    delete[] testInsert;
    delete[] testBubble;
    delete[] testMerge;
    delete[] testMergeBU;
    delete[] testQuick;
    delete[] testQuick2;
    delete[] testQuick3;
    delete[] testHeap1;
}

int main() {
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
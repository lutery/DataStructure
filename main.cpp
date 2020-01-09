#include <iostream>
#include <utility>
#include <climits>
#include "ToolUtil.h"
#include "SortTestHelper.h"
#include "BasicSort.h"
#include "AdvancedSort.h"
#include "HeapSort.h"
#include "BinarySearch.h"
#include "ISearch.h"
#include "UnionSearch.h"
#include "SparseGraph.h"
#include "DenseGraph.h"
#include "RenderGraph.h"
#include "Path.h"
#include "EditDistance.h"
#include "ShortPathGraph.h"
#include "BFCompare.h"

int generatorRnage(int min, int max)
{
    unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 rand_generator(seed);
    std::uniform_int_distribution<int> dist(min, max);
    int range = dist(rand_generator);

    if (range < 10)
    {
        range = 10;
    }

    return range;
}

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

template<class TimeUnit, class Item>
void testSearchSort(Item* testArr, int length, ISearch<Item, Item>* search, std::string sortName)
{
    std::cout << "-------------------" << sortName << "-------------------" << std::endl;

    int* testCurArr = SortTestHelper::copyArray(testArr, length);
    Item searchkey = generatorRnage(0, 10000);
    bool containKey = false;

    for (int i = 0; i < length; ++i) {
        search->insert(testArr[i], testArr[i]);

        if (!containKey && searchkey == testArr[i])
        {
            containKey = true;
        }
    }

    auto [clockCount, ret] = ToolUtil::cfunClock<TimeUnit>(&ISearch<Item, Item>::search, search, searchkey);
//    auto [clockCount, ret] = ToolUtil::funClock<TimeUnit>(fun, testCurArr, length, generatorRnage(100, 10000));
//    int clockCount = ToolUtil::funNClock<TimeUnit>(fun, testCurArr, length);
//
    std::cout << sortName << " nanoseconds is " << clockCount << std::endl;
//
    std::cout << std::endl << "search key is " << searchkey << " contain key is " << (containKey ? " exist " : "not exist") << " search result is " << ret << ", search " << (ret >= 0 ? "success" : "failed") << std::endl;
//
    delete[] testCurArr;
    delete search;

    search->traverse();
    search->levelorder();

    std::cout << std::endl;
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

void testBinarySearch()
{
    std::cout << std::endl << "**********************************BSTSearch**********************************" << std::endl;

    int testLength = generatorRnage(0, 10);

    std::cout << "testLength = " << testLength << std::endl;

    int* testSelect = SortTestHelper::generalRandomArray(testLength, 0, 20);
//    int* testSelect = SortTestHelper::generalAssignArray({8, 10, 16, 4, 19, 2, 1, 0, 15, 14});

    for (int i = 0, count = testLength % 100; i < count; ++i)
    {
        std::cout << testSelect[i] << " ";
    }

    std::cout << std::endl;

//    testSearchSort<std::chrono::nanoseconds, int>(testSelect, testLength, new BST<int, int>(), "BSTSearch");
    BST<int, int>* search = new BST<int, int>();

    int* testCurArr = SortTestHelper::copyArray(testSelect, testLength);
    int searchkey = generatorRnage(0, 20);
    bool containKey = false;
    int maxValue = INT_MIN;
    int minValue = INT_MAX;

    for (int i = 0; i < testLength; ++i) {
        search->insert(testSelect[i], testSelect[i]);

        if (!containKey && searchkey == testSelect[i])
        {
            containKey = true;
        }

        if (maxValue < testSelect[i])
        {
            maxValue = testSelect[i];
        }

        if (minValue > testSelect[i])
        {
            minValue = testSelect[i];
        }
    }

    auto [clockCount, ret] = ToolUtil::cfunClock<std::chrono::nanoseconds>(&ISearch<int, int>::search, search, searchkey);
//    auto [clockCount, ret] = ToolUtil::funClock<TimeUnit>(fun, testCurArr, length, generatorRnage(100, 10000));
//    int clockCount = ToolUtil::funNClock<TimeUnit>(fun, testCurArr, length);

    std::cout << "search maxValue " << search->maxmum() << " is " << (maxValue == search->maxmum() ? " right " : " failed ") << ", minValue " << search->minimum() << " is " << (minValue == search->minimum() ? " right " : " failed ") << std::endl;

    std::cout << "del max value is " << search->delMax()->value << " del min value is " << search->delMin()->value <<  ", after del after maxValue is " << search->search(search->maxmum()) << ", minValue is " << search->search(search->minimum()) << std::endl;

    std::cout << "BSTSearch nanoseconds is " << clockCount << std::endl;

    std::cout << std::endl << "search key is " << searchkey << " contain key is " << (containKey ? " exist " : "not exist") << " search result is " << ret << ", search " << (ret >= 0 ? "success" : "failed") << std::endl;

    if (containKey)
    {
        search->delNode(containKey);

        std::cout << std::endl << "search key is delete " << (search->contain(containKey) ? "failed" : "success") << std::endl;
    }

    search->traverse();
    search->levelorder();

    delete[] testCurArr;
    delete search;

    std::cout << std::endl;


    delete[] testSelect;
}

template <class T>
void testUnionSearch(UnionSearch<T>* pUnionSearch)
{
    srand(time(nullptr));

    int countElement = pUnionSearch->count();
    for (int i = 0; i < countElement; ++i)
    {
        int a = rand() % countElement;
        int b = rand() % countElement;

        pUnionSearch->unionGroup(a, b);
    }

    for (int i = 0; i < countElement; ++i)
    {
        int a = rand() % countElement;
        int b = rand() % countElement;

//        std::cout << a << " and " << b << (pUnionSearch->isConnect(a, b) ? " connect ;;; " : " disconnect ;;; ");// << std::endl;
        pUnionSearch->isConnect(a, b);
    }

    std::cout << std::endl;
}

template <class T>
void testQuickUnion(IUnion<T>* pUnionSearch)
{
    srand(time(nullptr));

    int countElement = pUnionSearch->count();
    for (int i = 0; i < countElement; ++i)
    {
        int a = rand() % countElement;
        int b = rand() % countElement;

        pUnionSearch->unionGroup(a, b);
    }

    for (int i = 0; i < countElement; ++i)
    {
        int a = rand() % countElement;
        int b = rand() % countElement;

//        std::cout << a << " and " << b << (pUnionSearch->isConnect(a, b) ? " connect ;;; " : " disconnect ;;; ");// << std::endl;
        pUnionSearch->isConnect(a, b);
    }

    std::cout << std::endl;
}

template <class T>
void testRankUnion(IUnion<T>* pUnionSearch)
{
    srand(time(nullptr));

    int countElement = pUnionSearch->count();
    for (int i = 0; i < countElement; ++i)
    {
        int a = rand() % countElement;
        int b = rand() % countElement;

        pUnionSearch->unionGroup(a, b);
    }

    for (int i = 0; i < countElement; ++i)
    {
        int a = rand() % countElement;
        int b = rand() % countElement;

//        std::cout << a << " and " << b << (pUnionSearch->isConnect(a, b) ? " connect ;;; " : " disconnect ;;; ");// << std::endl;
        pUnionSearch->isConnect(a, b);
    }

    std::cout << std::endl;
}


void testUnionSearch()
{
    std::cout << std::endl << "**********************************UnionSearch**********************************" << std::endl;

    UnionSearch<int> unionSearch(generatorRnage(1000, 10000));
    QuickUnion<int> quickUnion(generatorRnage(1000, 10000));
    RankUnion<int> rankUnion(generatorRnage(1000, 10000));
    PathUnion<int> pathUnion(generatorRnage(1000, 10000));

    auto clockCount = ToolUtil::funNClock<std::chrono::milliseconds>(testUnionSearch<int>, &unionSearch);
    std::cout << "unionsearch union and isconnect time is " << clockCount << " millseconds" << std::endl;

    auto clockCount1 = ToolUtil::funNClock<std::chrono::milliseconds>(testQuickUnion<int>, &quickUnion);
    std::cout << "quick union search and isconnect time is " << clockCount1 << " millseconds" << std::endl;

    auto clockCount2 = ToolUtil::funNClock<std::chrono::milliseconds>(testRankUnion<int>, &rankUnion);
    std::cout << "rank union search and isconnect time is " << clockCount2 << " millseconds" << std::endl;

    auto clockCount3 = ToolUtil::funNClock<std::chrono::milliseconds>(testRankUnion<int>, &pathUnion);
    std::cout << "path union search and isconnect time is " << clockCount3 << " millseconds" << std::endl;
}

void testTopN()
{
    std::cout << "*******************TopN*******************" << std::endl;
    TopN topN;

//    int* arr1 = SortTestHelper::generalAssignArray({5, 93, 48, 12, 22, 35, 49, 9, 26, 71});
    std::cout << "*******************arr1*******************" << std::endl;
    int* arr1 = SortTestHelper::generalRandomArray(10, 0, 100);
    topN.print(arr1, 10);
    topN.findTopN(5, arr1, 10);
    topN.print(arr1, 10);
    std::cout << "*******************end*******************" << std::endl;
    std::cout << "*******************arr2*******************" << std::endl;
    int* arr2 = SortTestHelper::generalRandomArray(1000, 0, 1000000);
    topN.print(arr2, 100);
    topN.findTopN(1000 / 2, arr2, 1000);
    topN.print(arr2, 1000);
    std::cout << "*******************end*******************" << std::endl;
    std::cout << "*******************arr3*******************" << std::endl;
    int* arr3 = SortTestHelper::generalRandomArray(100000, 0, 100000000);
    topN.print(arr3, 1000);
    topN.findTopN(100000 / 2, arr3, 100000);
    topN.print(arr3, 100000);
    std::cout << "*******************end*******************" << std::endl;

}

void testSparseGraph()
{
    std::cout << "*******************SparseGraph*******************" << std::endl;

    int dotCount = generatorRnage(10, 1000);
    SparseGraph sparseGraph(dotCount, false);
    for (int i = 0; i < generatorRnage(90000, 900000); ++i)
    {
        int a = generatorRnage(0, dotCount - 1);
        int b = generatorRnage(0, dotCount - 1);

        sparseGraph.addEdge(a, b);
    }

    for (int i = 0; i < dotCount; ++i)
    {
        std::cout << i << " : ";

        SparseGraph::ITerator iTerator(sparseGraph, i);
        for (int j = iTerator.begin(); !iTerator.end(); j = iTerator.next())
        {
            std::cout << j << ", ";
        }

        std::cout << std::endl;
    }

    std::cout << "*******************SparseGraph*******************" << std::endl;

}

void testDenseGraph()
{
    std::cout << "*******************DenseGraph*******************" << std::endl;

    int dotCount = generatorRnage(10, 1000);
    DenseGraph denseGraph(dotCount, false);
    for (int i = 0; i < generatorRnage(900, 9000); ++i)
    {
        int a = generatorRnage(0, dotCount - 1);
        int b = generatorRnage(0, dotCount - 1);

        denseGraph.addEdge(a, b);
    }

    for (int i = 0; i < dotCount; ++i)
    {
        std::cout << i << " : ";

        DenseGraph::ITerator iTerator(denseGraph, i);
        for (int j = iTerator.begin(); !iTerator.end(); j = iTerator.next())
        {
            std::cout << j << ", ";
        }

        std::cout << std::endl;
    }

    std::cout << "*******************DenseGraph*******************" << std::endl;

}

void testRenderGraph()
{
    std::cout << "*******************RenderGraph*******************" << std::endl;

    std::string filename1 = "../testG1.txt";
    std::cout << "filename is " << filename1 << std::endl;
    SparseGraph sparseGraph(13, false);
    RenderGraph<SparseGraph>::readGraph(sparseGraph, filename1);
    Component<SparseGraph> componentSparse(sparseGraph);
    sparseGraph.show();
    std::cout << "TestG1.txt, Component Count: " << componentSparse.getDotCount() << std::endl;

    std::string filename2 = "../testG2.txt";
    std::cout << "filename is " << filename2 << std::endl;
    SparseGraph sparseGraph1(7, false);
    RenderGraph<SparseGraph>::readGraph(sparseGraph1, filename2);
    Component<SparseGraph> componentSparse1(sparseGraph1);
    sparseGraph1.show();
    std::cout << "TestG2.txt, Component Count: " << componentSparse1.getDotCount() << std::endl;

    std::cout << "*******************RenderGraph*******************" << std::endl;
}

void testPath()
{
    std::cout << "*******************test Path*******************" << std::endl;

    std::string filename2 = "../testG2.txt";
    std::cout << "filename is " << filename2 << std::endl;
    SparseGraph sparseGraph1(7, false);
    RenderGraph<SparseGraph>::readGraph(sparseGraph1, filename2);
    sparseGraph1.show();
    std::cout << std::endl;

    Path<SparseGraph> dfsPath(sparseGraph1, 0);
    std::cout << "DFS : ";
    dfsPath.showPath(6);

    ShortPathGraph<SparseGraph> bfs(sparseGraph1, 0);
    std::cout << "BFS : ";
    bfs.showPath(6);

    std::cout << "*******************test Path*******************" << std::endl;
}

int main()
{
    std::cout << "Hello, World!" << std::endl;

//    testRandomArr();
//    testNearOrderArr();
//    testBinarySearch();
//    testUnionSearch();
//    testTopN();
//    testSparseGraph();
//    testDenseGraph();
//    testRenderGraph();
    testPath();

//    auto s1 = "sunday";
//    auto s2 = "saturday";
//
//    std::cout << "The Edit Distance of " << EditDistance::editDistDP(s1, s2);

    std::string a = "abcddecf";
    std::string b = "dec";

    int index = BFCompare::index(a, b, 0);

    std::cout << "index is " << index << std::endl;

    return 0;
}
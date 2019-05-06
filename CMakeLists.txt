cmake_minimum_required(VERSION 3.12)
project(DataStructure)

set(CMAKE_CXX_STANDARD 17)

add_executable(DataStructure main.cpp SortTestHelper.cpp SortTestHelper.h ToolUtil.cpp ToolUtil.h BasicSort.cpp BasicSort.h AdvancedSort.cpp AdvancedSort.h HeapSort.cpp HeapSort.h IndexMaxHeap.h BinarySearch.cpp BinarySearch.h ISearch.h UnionSearch.cpp UnionSearch.h DenseGraph.cpp DenseGraph.h SparseGraph.cpp SparseGraph.h)
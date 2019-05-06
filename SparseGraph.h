//
// Created by yanghui on 2019-05-05.
//

#ifndef DATASTRUCTURE_SPARSEGRAPH_H
#define DATASTRUCTURE_SPARSEGRAPH_H

#include <vector>

class SparseGraph
{
public:
    SparseGraph(int dotCount, bool isDirect);
    ~SparseGraph();

    bool hasEdge(int src, int dst);
    void addEdge(int src, int dst);


private:
    bool mIsDirect = false;
    int mDotCount = 0;
    int mBorderCount = 0;
    std::vector<std::vector<int>> mGraph;
};


#endif //DATASTRUCTURE_SPARSEGRAPH_H
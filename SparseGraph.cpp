//
// Created by yanghui on 2019-05-05.
//

#include "SparseGraph.h"

SparseGraph::SparseGraph(int dotCount, bool isDirect)
{
    mDotCount = dotCount;
    mIsDirect = isDirect;

    for (int i = 0; i < mDotCount; ++i)
    {
        mGraph.push_back(std::vector<int>());
    }
}

SparseGraph::~SparseGraph()
{

}

bool SparseGraph::hasEdge(int src, int dst)
{
    assert(src >= 0 && src < mDotCount);
    assert(dst >= 0 && dst < mDotCount);

    for (int val : mGraph[src])
    {
        if (val == dst)
        {
            return true;
        }
    }

    return false;
}

void SparseGraph::addEdge(int src, int dst)
{
    assert(src >= 0 && src < mDotCount);
    assert(dst >= 0 && dst < mDotCount);

    mGraph[src].push_back(dst);

    if (src != dst && !mIsDirect)
    {
        mGraph[dst].push_back(src);
    }

    mBorderCount++;
}

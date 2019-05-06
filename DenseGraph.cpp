//
// Created by yanghui on 2019-05-05.
//

#include "DenseGraph.h"

DenseGraph::DenseGraph(int dotCount, bool isDirect)
{
    mDotCount = dotCount;
    mIsDirect = isDirect;

    for (int i = 0; i < mDotCount; ++i)
    {
        mGraph.push_back(std::vector<bool>(mDotCount, false));
    }
}

DenseGraph::~DenseGraph()
{

}

bool DenseGraph::hasEdge(int src, int dst)
{
    return mGraph[src][dst];
}

void DenseGraph::addEdge(int src, int dst)
{
    assert(src >= 0 && dst < mDotCount);
    assert(src >= 0 & dst < mDotCount);

    if (hasEdge(src, dst))
    {
        return;
    }

    mGraph[src][dst] = true;
    if (!mIsDirect)
    {
        mGraph[dst][src] = true;
    }

    mBorderCount++;
}

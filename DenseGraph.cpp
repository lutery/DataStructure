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

DenseGraph::ITerator::ITerator(DenseGraph &graph, int dot) : mGraph(graph)
{
    mCurDot = dot;
    mCurCount = 0;
}

DenseGraph::ITerator::~ITerator()
{

}

int DenseGraph::ITerator::begin()
{
    mCurCount = -1;

    return this->next();
}

int DenseGraph::ITerator::next()
{
    for (++mCurCount; mCurCount < mGraph.mDotCount; ++mCurCount)
    {
        if (mGraph.mGraph[mCurDot][mCurCount])
        {
            return mCurCount;
        }
    }

    return -1;
}

bool DenseGraph::ITerator::end()
{
    return mCurCount >= mGraph.mGraph[mCurCount].size();
}

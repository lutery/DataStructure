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

SparseGraph::ITerator::ITerator(SparseGraph &graph, int dot) : mGraph(graph)
{
    mCurDot = dot;
    mCurCount = 0;
}

SparseGraph::ITerator::~ITerator()
{

}

int SparseGraph::ITerator::begin()
{
    mCurCount = 0;

    if (mGraph.mGraph[mCurDot].size() > 0)
    {
        return mGraph.mGraph[mCurDot][mCurCount];
    }

    return -1;
}

int SparseGraph::ITerator::next()
{
    mCurCount++;
    if (mCurCount < mGraph.mGraph[mCurDot].size())
    {
        return mGraph.mGraph[mCurDot][mCurCount];
    }

    return -1;
}

bool SparseGraph::ITerator::end()
{
    return mCurCount >= mGraph.mGraph[mCurDot].size();
}

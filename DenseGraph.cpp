//
// Created by yanghui on 2019-05-05.
//

#include <iostream>
#include "DenseGraph.h"

/**
 * 构造函数
 * @param dotCount 点的总数
 * @param isDirect 是否是有向图
 */
DenseGraph::DenseGraph(int dotCount, bool isDirect)
{
    mDotCount = dotCount;
    mIsDirect = isDirect;

    // 初始化稠密图，全部设置为false
    for (int i = 0; i < mDotCount; ++i)
    {
        mGraph.push_back(std::vector<bool>(mDotCount, false));
    }
}

DenseGraph::~DenseGraph()
{

}

/**
 * 是否有连接
 * @param src 起始点
 * @param dst 目标点
 * @return
 */
bool DenseGraph::hasEdge(int src, int dst)
{
    return mGraph[src][dst];
}

/**
 * 增加边
 * @param src 起始点
 * @param dst 目标点
 */
void DenseGraph::addEdge(int src, int dst)
{
    assert(src >= 0 && dst < mDotCount);
    assert(src >= 0 & dst < mDotCount);

    if (hasEdge(src, dst))
    {
        return;
    }

    // 如果不是有向图，那么反方向也要设置为true
    mGraph[src][dst] = true;
    if (!mIsDirect)
    {
        mGraph[dst][src] = true;
    }

    mBorderCount++;
}

/**
 * 打印图
 */
void DenseGraph::show()
{
    std::cout << "**************DENSE GRAPH**************" << std::endl;
    for (auto& graph : mGraph)
    {
        for (auto item : graph)
        {
            if (item)
            {
                std::cout << " 1 ";
            }
            else
            {
                std::cout << " 0 ";
            }

        }

        std::cout << std::endl;
    }
}

/**
 * 获取点的个数
 * @return
 */
int DenseGraph::V() {
    return mGraph.size();
}

/**
 * 遍历器构造器
 * @param graph
 * @param dot
 */
DenseGraph::ITerator::ITerator(DenseGraph &graph, int dot) : mGraph(graph)
{
    mCurDot = dot;
    mCurCount = 0;
}

DenseGraph::ITerator::~ITerator()
{

}

/**
 * 初始化遍历器
 * @return
 */
int DenseGraph::ITerator::begin()
{
    mCurCount = -1;

    return this->next();
}

/**
 * 遍历下一个节点
 * @return
 */
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

/**
 * 是否遍历到结尾点
 * @return
 */
bool DenseGraph::ITerator::end()
{
    return mCurCount >= mGraph.mGraph[mCurCount].size();
}

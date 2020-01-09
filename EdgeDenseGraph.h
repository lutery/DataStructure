//
// Created by yanghui on 2019-05-05.
//

#ifndef DATASTRUCTURE_DENSEGRAPH_H
#define DATASTRUCTURE_DENSEGRAPH_H

#include <vector>
#include "Edge.h"

/**
 * 稠密图
 */
 template <typename Weight>
class EdgeDenseGraph
{
public:
    EdgeDenseGraph(int dotCount, bool isDirect);
    ~EdgeDenseGraph();

    bool hasEdge(int src, int dst);
    void addEdge(int src, int dst);
    void show();
    int V();

private:
    // 是否是有向图
    bool mIsDirect = false;
    // 点的个数
    int mDotCount = 0;
    //边个数
    int mBorderCount = 0;
    // 图，如果有连接对应的索引x,y设置为true，无连接设置为false
    std::vector<std::vector<Edge<Weight>*>> mGraph;

public:
    /**
     * 稠密图遍历器
     */
    class ITerator
    {
    public:
        ITerator(EdgeDenseGraph& graph, int dot);
        ~ITerator();

        int begin();
        int next();
        bool end();

    private:
        // 当前的边个数
        int mCurCount;
        // 当前遍历的起始点
        int mCurDot;
        // 稠密图引用
        EdgeDenseGraph& mGraph;
    };
};

/**
* 构造函数
* @param dotCount 点的总数
* @param isDirect 是否是有向图
*/
template <typename Weight>
EdgeDenseGraph::EdgeDenseGraph(int dotCount, bool isDirect)
{
    mDotCount = dotCount;
    mIsDirect = isDirect;

    // 初始化稠密图，全部设置为false
    for (int i = 0; i < mDotCount; ++i)
    {
        mGraph.push_back(std::vector<Edge<Weight>*>(mDotCount, nullptr));
    }
}

template <typename Weight>
EdgeDenseGraph::~EdgeDenseGraph()
{

}

/**
 * 是否有连接
 * @param src 起始点
 * @param dst 目标点
 * @return
 */
 template <typename Weight>
bool EdgeDenseGraph::hasEdge(int src, int dst)
{
    return mGraph[src][dst];
}

/**
 * 增加边
 * @param src 起始点
 * @param dst 目标点
 */
void EdgeDenseGraph::addEdge(int src, int dst)
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
void EdgeDenseGraph::show()
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
int EdgeDenseGraph::V() {
    return mGraph.size();
}

/**
 * 遍历器构造器
 * @param graph
 * @param dot
 */
EdgeDenseGraph::ITerator::ITerator(EdgeDenseGraph &graph, int dot) : mGraph(graph)
{
    mCurDot = dot;
    mCurCount = 0;
}

EdgeDenseGraph::ITerator::~ITerator()
{

}

/**
 * 初始化遍历器
 * @return
 */
int EdgeDenseGraph::ITerator::begin()
{
    mCurCount = -1;

    return this->next();
}

/**
 * 遍历下一个节点
 * @return
 */
int EdgeDenseGraph::ITerator::next()
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
bool EdgeDenseGraph::ITerator::end()
{
    return mCurCount >= mGraph.mGraph[mCurCount].size();
}


#endif //DATASTRUCTURE_DENSEGRAPH_H

//
// Created by yanghui on 2019-05-05.
//

#ifndef DATASTRUCTURE_DENSEGRAPH_H
#define DATASTRUCTURE_DENSEGRAPH_H

#include <vector>

/**
 * 稠密图
 */
class DenseGraph
{
public:
    DenseGraph(int dotCount, bool isDirect);
    ~DenseGraph();

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
    std::vector<std::vector<bool>> mGraph;

public:
    /**
     * 稠密图遍历器
     */
    class ITerator
    {
    public:
        ITerator(DenseGraph& graph, int dot);
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
        DenseGraph& mGraph;
    };
};


#endif //DATASTRUCTURE_DENSEGRAPH_H

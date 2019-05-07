//
// Created by yanghui on 2019-05-05.
//

#ifndef DATASTRUCTURE_DENSEGRAPH_H
#define DATASTRUCTURE_DENSEGRAPH_H

#include <vector>

class DenseGraph
{
public:
    DenseGraph(int dotCount, bool isDirect);
    ~DenseGraph();

    bool hasEdge(int src, int dst);
    void addEdge(int src, int dst);


private:
    bool mIsDirect = false;
    int mDotCount = 0;
    int mBorderCount = 0;
    std::vector<std::vector<bool>> mGraph;

public:
    class ITerator
    {
    public:
        ITerator(DenseGraph& graph, int dot);
        ~ITerator();

        int begin();
        int next();
        bool end();

    private:
        int mCurCount;
        int mCurDot;
        DenseGraph& mGraph;
    };
};


#endif //DATASTRUCTURE_DENSEGRAPH_H

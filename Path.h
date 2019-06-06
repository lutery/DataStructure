//
// Created by yanghui on 2019-06-06.
//

#ifndef DATASTRUCTURE_PATH_H
#define DATASTRUCTURE_PATH_H

#include <assert.h>
#include <vector>
#include <stack>
#include <iostream>

template <typename Graph>
class Path
{
private:
    Graph& mGraph;
    int mFromDot;
    bool* mVisited;
    int* mFrom;

    void dfs(int dot)
    {
        mVisited[dot] = true;

        typename Graph::ITerator iTerator(mGraph, dot);

        for (int i = iTerator.begin(); !iTerator.end(); i = iTerator.next())
        {
            if (!mVisited[i])
            {
                mFrom[i] = dot;
                dfs(i);
            }
        }
    }

public:
    Path(Graph& graph, int fromDot):mGraph(graph)
    {
        assert(fromDot >= 0 && fromDot < graph.V());

        mVisited = new bool[graph.V()];
        mFrom = new int[graph.V()];
        for (int i = 0; i < graph.V(); ++i)
        {
            mVisited[i] = false;
            mFrom[i] = -1;
        }

        this->mFromDot = fromDot;

        dfs(this->mFromDot);
    }

    ~Path()
    {
        delete [] mVisited;
        delete [] mFrom;
    }

    bool hasPath(int dstDot)
    {
        assert(dstDot >= 0 && dstDot < mGraph.V());
        return mVisited[dstDot];
    }

    void path(int dstDot, std::vector<int>& dstDots)
    {
        std::stack<int> s;

        int from = dstDot;
        while (from != -1)
        {
            s.push(from);
            from = mFrom[from];
        }

        dstDots.clear();
        while (!s.empty())
        {
            dstDots.push_back(s.top());
            s.pop();
        }
    }

    void showPath(int dstDot)
    {
        std::vector<int> vector;
        path(dstDot, vector);

        for (auto dot : vector)
        {
            if (dstDot == dot)
            {
                std::cout << dot;
            }
            else
            {
                std::cout << dot << " -> " ;
            }
        }

        std::cout << std::endl;
    }
};


#endif //DATASTRUCTURE_PATH_H

//
// Created by yanghui on 2019-07-01.
//

#ifndef DATASTRUCTURE_SHORTPATHGRAPH_H
#define DATASTRUCTURE_SHORTPATHGRAPH_H

#include <assert.h>
#include <queue>
#include <vector>
#include <stack>
#include <iostream>

template <typename Graph>
class ShortPathGraph
{
private:
    Graph& mGraph;
    int mSrcDot;
    bool* mHasVisited;
    int* mFrom;
    int* mOrd;

public:
    ShortPathGraph(Graph& graph, int srcDot):mGraph(graph)
    {
        assert(srcDot >= 0 && srcDot < graph.V());

        mHasVisited = new bool[graph.V()];
        mFrom = new int[graph.V()];
        mOrd = new int[graph.V()];

        for (int i = 0; i < graph.V(); ++i)
        {
            mHasVisited[i] = false;
            mFrom[i] = -1;
            mOrd[i] = -1;
        }

        mSrcDot = srcDot;

        std::queue<int> q;

        q.push(srcDot);
        mHasVisited[srcDot] = true;
        mOrd[srcDot] = 0;

        while (!q.empty())
        {
            int cur = q.front();
            q.pop();

            typename Graph::ITerator adj(mGraph, cur);

            for (int i = adj.begin(); !adj.end(); i = adj.next())
            {
                if (!mHasVisited[i])
                {
                    q.push(i);
                    mHasVisited[i] = true;

                    mFrom[i] = cur;
                    mOrd[i] += 1;
                }
            }
        }
    }

    ~ShortPathGraph()
    {
        delete[] mHasVisited;
        delete[] mFrom;
        delete[] mOrd;
    }

    bool hasPath(int w)
    {
        assert(w >= 0 && w < mGraph.V());
        return mHasVisited[w];
    }

    void path(int w, std::vector<int>& vec)
    {
        assert(w >= 0 && w < mGraph.V());

        std::stack<int> s;

        int p = w;

        while (p != -1)
        {
            s.push(p);
            p = mFrom[p];
        }

        vec.clear();
        while (!s.empty())
        {
            vec.push_back(s.top());
            s.pop();
        }
    }

    void showPath(int w)
    {
        assert(w >= 0 && w < mGraph.V());

        std::vector<int> vec;
        path(w, vec);
        for (int i = 0; i < vec.size(); ++i)
        {
            std::cout << vec[i];
            if (i == vec.size() - 1)
            {
                std::cout << std::endl;
            }
            else
            {
                std::cout << " -> ";
            }
        }
    }

    int length(int w)
    {
        assert(w >= 0 && w < mGraph.V());
        return mOrd[w];
    }
};


#endif //DATASTRUCTURE_SHORTPATHGRAPH_H

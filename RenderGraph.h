//
// Created by yanghui on 2019-05-09.
//

#ifndef DATASTRUCTURE_RENDERGRAPH_H
#define DATASTRUCTURE_RENDERGRAPH_H

#include <string>
#include <fstream>
#include <sstream>

/**
 * 遍历联通分量，也就是内部有多少联通区域
 * @tparam Graph
 */
template <typename Graph>
class Component
{
private:
    Graph& G;
    bool* visited;
    int dotCount = 0;

    void dfs(int curDot)
    {
        visited[curDot] = true;

        typename Graph::ITerator iTerator(G, curDot);

        for (int i = iTerator.begin(); !iTerator.end(); i = iTerator.next())
        {
            if (!visited[i])
            {
                dfs(i);
            }
        }
    }

public:
    auto getDotCount() -> int  {
        return this->dotCount;
    }

    Component(Graph& graph) : G(graph)
    {
        visited = new bool[G.V()];

        for (int i = 0; i < G.V(); ++i)
        {
            visited[i] = false;
        }

        for (int i = 0; i < G.V(); ++i)
        {
            if (!visited[i])
            {
                dfs(i);
                dotCount++;
            }
        }
    }
};

template <typename Graph>
class RenderGraph
{
public:
    static void readGraph(Graph& graph, const std::string& filename)
    {
        std::ifstream file(filename);
        std::string line;

        int V, E;

        assert(file.is_open());

        assert(std::getline(file, line));
        std::stringstream ss(line);
        ss >> V >> E;

        assert(V == graph.V());

        for (int i = 0; i < E; ++i)
        {
            assert(getline(file, line));

            std::stringstream ss(line);

            int a, b;
            ss >> a >> b;

            graph.addEdge(a, b);
        }
    }
};

#endif //DATASTRUCTURE_RENDERGRAPH_H

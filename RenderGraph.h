//
// Created by yanghui on 2019-05-09.
//

#ifndef DATASTRUCTURE_RENDERGRAPH_H
#define DATASTRUCTURE_RENDERGRAPH_H

#include <string>
#include <fstream>
#include <sstream>

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

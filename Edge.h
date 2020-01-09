//
// Created by yanghui on 2019-07-16.
//

#ifndef DATASTRUCTURE_EDGE_H
#define DATASTRUCTURE_EDGE_H

#include <ostream>

template <typename Weight>
class Edge
{
private:
    int mFrom, mTo;
    Weight mWeight;

public:
    Edge(int from, int to, Weight weight)
    {
        this->mFrom = from;
        this->mTo = to;
        this->mWeight = weight;
    }

    Edge(){}

    ~Edge(){}

    auto V() -> int
    {
        return mFrom;
    }

    auto W() -> int
    {
        return mTo;
    }

    auto Wt() -> Weight
    {
        return mWeight;
    }

    auto other(int x) -> int
    {
        assert(x == mFrom || x == mTo);

        return x == mFrom ? mTo : mFrom;
    }

    friend std::ostream& operator<<(std::ostream& os, const Edge& e)
    {
        os << e.mFrom << "-" << e.To << ": " << e.mWeight;

        return os;
    }

    bool operator<(Edge<Weight>& other)
    {
        return mWeight < other.Wt();
    }

    bool operator<=(Edge<Weight>& other)
    {
        return mWeight <= other.Wt();
    }

    bool operator>(Edge<Weight>& other)
    {
        return mWeight > other.Wt();
    }

    bool operator>=(Edge<Weight>& other)
    {
        return mWeight >= other.Wt();
    }

    bool operator==(Edge<Weight>& other)
    {
        return mWeight == other.Wt();
    }
};


#endif //DATASTRUCTURE_EDGE_H

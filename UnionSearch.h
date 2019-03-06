//
// Created by yanghui on 2019/3/6.
//

#ifndef DATASTRUCTURE_UNIONSEARCH_H
#define DATASTRUCTURE_UNIONSEARCH_H

#include <iostream>

template <class T>
class UnionSearch
{
private:
    T* mElement = nullptr;
    int mCount = 0;

public:
    UnionSearch(int count):mCount(count), mElement(new T[mCount])
    {

    }

    int count()
    {
        return this->mCount;
    }

    T searchGroup(int index)
    {
        return mElement[index];
    }

    void setGroup(int index, int group)
    {
        mElement[index] = group;
    }

    bool isConnect(int pIndex, int qIndex)
    {
        return searchGroup(pIndex) == searchGroup(qIndex);
    }

    void unionGroup(int p, int q)
    {
        T pGroup = searchGroup(p);
        T qGroup = searchGroup(q);

        if (pGroup == qGroup)
        {
            return;
        }

        for (int i = 0; i < mCount; ++i)
        {
            if (searchGroup(i) == pGroup)
            {
                setGroup(i, qGroup);
            }
        }
    }
};

class UnionSearchTestHelper
{
public:

};


#endif //DATASTRUCTURE_UNIONSEARCH_H

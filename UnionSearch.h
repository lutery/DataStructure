//
// Created by yanghui on 2019/3/6.
//

#ifndef DATASTRUCTURE_UNIONSEARCH_H
#define DATASTRUCTURE_UNIONSEARCH_H

#include <iostream>

/**
 * 并查集，主要实现的是分组网络，可以用于查看用户的关联关系，网络互通关系等等
 * @tparam T
 */
template <class T>
class UnionSearch
{
private:
    // 存储每个元素（索引）其所在的分组（值）
    T* mElement = nullptr;
    int mCount = 0;

public:
    UnionSearch(int count):mCount(count), mElement(new T[count])
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

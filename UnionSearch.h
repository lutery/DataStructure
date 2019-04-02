//
// Created by yanghui on 2019/3/6.
//

#ifndef DATASTRUCTURE_UNIONSEARCH_H
#define DATASTRUCTURE_UNIONSEARCH_H

#include <iostream>

template <class T>
class IUnion
{
protected:
    T* mElement = nullptr;
    int mCount = 0;

public:
    IUnion(int count) : mCount(count), mElement(new T[count]){}
    virtual ~IUnion()
    {
        delete[] mElement;
    }

    int count()
    {
        return mCount;
    }

    virtual T searchGroup(int index) = 0;
    virtual void setGroup(int index, int group) = 0;
    virtual bool isConnect(int pIndex, int qIndex) = 0;
    virtual void unionGroup(int pIndex, int qIndex) = 0;
};

template <class T>
class QuickUnion : IUnion<T> {
private:
    T *mElement = nullptr;
    int mCount = 0;

public:
    QuickUnion(int count) : IUnion<T>(count)
    {

    }

    virtual ~QuickUnion()
    {

    }

    int count()
    {
        return this->mCount;
    }

    T searchGroup(int index) override
    {
        return mElement[index];
    }

    void setGroup(int index, int group) override
    {
        mElement[index] = group;
    }

    bool isConnect(int pIndex, int qIndex) override
    {
        T pTop, qTop;

        while (mElement[pIndex] != pIndex)
        {
            pIndex = mElement[pIndex];
        }

        pTop = mElement[pIndex];

        while (mElement[qIndex] != qIndex)
        {
            qIndex = mElement[qIndex];
        }

        qTop = mElement[qIndex];

        return pTop == qTop;
    }

    void unionGroup(int pIndex, int qIndex) override
    {
//        int pCount = 0;
//        int qCount = 0;

        while (mElement[pIndex] != pIndex)
        {
//            ++pCount;
            pIndex = mElement[pIndex];
        }

        while (mElement[qIndex] != qIndex)
        {
//            ++qCount;
            qIndex = mElement[qIndex];
        }

        mElement[pIndex] = qIndex;
    }
};

/**
 * 并查集，主要实现的是分组网络，可以用于查看用户的关联关系，网络互通关系等等
 * @tparam T
 */
template <class T>
class UnionSearch :  {
private:
    // 存储每个元素（索引）其所在的分组（值）
    T *mElement = nullptr;
    int mCount = 0;

public:
    UnionSearch(int count) : mCount(count), mElement(new T[count]) {

    }

    ~UnionSearch()
    {
        delete[] mElement;
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


#endif //DATASTRUCTURE_UNIONSEARCH_H

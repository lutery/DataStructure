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
    IUnion(int count) : mCount(count), mElement(new T[count])
    {
        for (int i = 0;  i < count; ++i)
        {
            mElement[i] = i;
        }
    }

    virtual ~IUnion()
    {
        delete[] mElement;
    }

    int count()
    {
        return mCount;
    }

    virtual T searchGroup(int index) = 0;
//    virtual void setGroup(int index, int group) = 0;
    virtual bool isConnect(int pIndex, int qIndex) = 0;
    virtual void unionGroup(int pIndex, int qIndex) = 0;
};

template <class T>
class QuickUnion : public IUnion<T> {
private:
//    T *mElement = nullptr;
//    int mCount = 0;

public:
    QuickUnion(int count) : IUnion<T>(count)
    {

    }

    virtual ~QuickUnion()
    {

    }

    T searchGroup(int index) override
    {
        assert(index >= 0 && index < this->mCount);
        while (index != this->mElement[index])
        {
            index = this->mElement[index];
        }

        return index;
    }

//    void setGroup(int index, int group) override
//    {
//        this->mElement[index] = group;
//    }

    bool isConnect(int pIndex, int qIndex) override
    {
//        T pTop, qTop;
//
//        while (this->mElement[pIndex] != pIndex)
//        {
//            pIndex = this->mElement[pIndex];
//        }
//
//        pTop = this->mElement[pIndex];
//
//        while (this->mElement[qIndex] != qIndex)
//        {
//            qIndex = this->mElement[qIndex];
//        }
//
//        qTop = this->mElement[qIndex];
//
//        return pTop == qTop;

        return this->searchGroup(pIndex) == this->searchGroup(qIndex);
    }

    void unionGroup(int pIndex, int qIndex) override
    {
//        while (this->mElement[pIndex] != pIndex)
//        {
//            pIndex = this->mElement[pIndex];
//        }
//
//        while (this->mElement[qIndex] != qIndex)
//        {
//            qIndex = this->mElement[qIndex];
//        }
//
//        this->mElement[pIndex] = qIndex;

        int pRoot = this->searchGroup(pIndex);
        int qRoot = this->searchGroup(qIndex);

        if (pRoot == qRoot)
        {
            return;
        }

        this->mElement[pRoot] = qRoot;
    }
};

/**
 * 并查集，主要实现的是分组网络，可以用于查看用户的关联关系，网络互通关系等等
 * @tparam T
 */
template <class T>
class UnionSearch : public IUnion<T>{
private:
    // 存储每个元素（索引）其所在的分组（值）
//    T *mElement = nullptr;
//    int mCount = 0;

public:
    UnionSearch(int count) : IUnion<T>(count){

    }

    virtual ~UnionSearch()
    {
    }

    T searchGroup(int index) override
    {
        return this->mElement[index];
    }

    void setGroup(int index, int group)
    {
        this->mElement[index] = group;
    }

    bool isConnect(int pIndex, int qIndex) override
    {
        return searchGroup(pIndex) == searchGroup(qIndex);
    }

    void unionGroup(int p, int q) override
    {
        T pGroup = searchGroup(p);
        T qGroup = searchGroup(q);

        if (pGroup == qGroup)
        {
            return;
        }

        for (int i = 0; i < this->mCount; ++i)
        {
            if (searchGroup(i) == pGroup)
            {
                setGroup(i, qGroup);
            }
        }
    }
};


#endif //DATASTRUCTURE_UNIONSEARCH_H

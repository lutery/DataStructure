//
// Created by yanghui on 2019/3/6.
//

#ifndef DATASTRUCTURE_UNIONSEARCH_H
#define DATASTRUCTURE_UNIONSEARCH_H

#include <iostream>

/**
 * 并查集接口
 * @tparam T
 */
template <class T>
class IUnion
{
protected:
    // 存储的元素数组，其保存的内容是索引i是哪个分组
    T* mElement = nullptr;
    // 元素的个数
    int mCount = 0;

public:
    IUnion(int count) : mCount(count), mElement(new T[count])
    {
        // 初始化每个元素指向自身
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

    // 索引i所对应的组
    virtual T searchGroup(int index) = 0;
//    virtual void setGroup(int index, int group) = 0;
    //判断是否连接
    virtual bool isConnect(int pIndex, int qIndex) = 0;
    //连接两个分组
    virtual void unionGroup(int pIndex, int qIndex) = 0;
};

/**
 * 路径搜索的并查集，路径优化下，每个节点都会指向其所在分组的父节点，由于路径优化，每个节点都会指向该条路径下的根节点
 * @tparam T
 */
template <class T>
class PathUnion : public IUnion<T> {
private:
    // 保存每个分组的子节点个数为1
    int* mRank = nullptr;

public:
    PathUnion(int count) : IUnion<T>(count), mRank(new int[count])
    {
        // 初始化每一个分组的个数为1
        for (int i = 0; i < this->mCount; ++i)
        {
            mRank[i] = 1;
        }
    }

    virtual ~PathUnion()
    {
        if (mRank != nullptr) {
            delete[] mRank;
        }
    }

    /**
     * 获取指定节点的分组号
     * @param index
     * @return
     */
    T searchGroup(int index) override
    {
        // 由于每个元素其存储的是该分组所在位置的上一级元素索引
        // 其根节点所存储的才是该分组的组号
        // 所以这里需要不断的向上遍历
        assert(index >= 0 && index < this->mCount);
//        while (index != this->mElement[index])
//        {
//            this->mElement[index] = this->mElement[this->mElement[index]];
//            index = this->mElement[index];
//        }
//
//        return index;

        // 因为是路径优化，所以在获取分组号的时候，会不断的更新每个节点的父节点索引，使每个分组的深度不会太深
        if (index != this->mElement[index])
        {
            this->mElement[index] = searchGroup(this->mElement[index]);
        }

        return this->mElement[index];
    }

//    void setGroup(int index, int group) override
//    {
//        this->mElement[index] = group;
//    }

    /**
     * 判断两个节点之间是否是出于同一分组
     * @param pIndex
     * @param qIndex
     * @return
     */
    bool isConnect(int pIndex, int qIndex) override
    {
        return this->searchGroup(pIndex) == this->searchGroup(qIndex);
    }

    /**
     * 设置两个节点为同一个分组，路径优化下，层数分组内节点数少的分组会获取另一个节点
     * @param pIndex
     * @param qIndex
     */
    void unionGroup(int pIndex, int qIndex) override
    {
        /**
         * 获取两个节点的所在的分组
         */
        int pRoot = this->searchGroup(pIndex);
        int qRoot = this->searchGroup(qIndex);

        if (pRoot == qRoot)
        {
            return;
        }

        /**
         * 如果pRoot分组的节点数小于qRoot分组，那么pRoot分组根节点指向qRoot分组的根节点
         * 并更新qRoot分组的个数
         * 反之亦然
         */
        if (mRank[pRoot] < mRank[qRoot])
        {
            this->mElement[pRoot] = qRoot;
        }
        else if (mRank[pRoot] > mRank[qRoot])
        {
            this->mElement[qRoot] = pRoot;
        }
        else
        {
            this->mElement[pRoot] = qRoot;
            mRank[qRoot]++;
        }
    }
};

/**
 * Rank优化并查集
 * @tparam T
 */
template <class T>
class RankUnion : public IUnion<T> {
private:
//    T *mElement = nullptr;
//    int mCount = 0;
    int* mRank = nullptr;

public:
    RankUnion(int count) : IUnion<T>(count), mRank(new int[count])
    {
        // 初始化每一个分组的个数为1
        for (int i = 0; i < this->mCount; ++i)
        {
            mRank[i] = 1;
        }
    }

    virtual ~RankUnion()
    {
        if (mRank != nullptr) {
            delete[] mRank;
        }
    }

    T searchGroup(int index) override
    {
        // 由于每个元素其存储的是该分组所在位置的上一级元素索引
        // 其根节点所存储的才是该分组的组号
        // 所以这里需要不断的向上遍历
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
        return this->searchGroup(pIndex) == this->searchGroup(qIndex);
    }

    void unionGroup(int pIndex, int qIndex) override
    {
        /**
         * 获取两个节点的所在的分组
         */
        int pRoot = this->searchGroup(pIndex);
        int qRoot = this->searchGroup(qIndex);

        if (pRoot == qRoot)
        {
            return;
        }

        /**
         * 如果pRoot分组的节点数小于qRoot分组，那么pRoot分组根节点指向qRoot分组的根节点
         * 并更新qRoot分组的个数
         * 反之亦然
         */
        if (mRank[pRoot] < mRank[qRoot])
        {
            this->mElement[pRoot] = qRoot;
        }
        else if (mRank[pRoot] > mRank[qRoot])
        {
            this->mElement[qRoot] = pRoot;
        }
        else
        {
            this->mElement[pRoot] = qRoot;
            mRank[qRoot]++;
        }
    }
};

/**
 * 快速排序并查集，与普通并查集相比，多了一个mSize成员，其存储的是每一个索引所在的分组
 * 其分组的大小
 * @tparam T
 */
template <class T>
class QuickUnion : public IUnion<T> {
private:
//    T *mElement = nullptr;
//    int mCount = 0;
    int* mSize = nullptr;

public:
    QuickUnion(int count) : IUnion<T>(count), mSize(new int[count])
    {
        // 初始化每一个分组的个数为1
        for (int i = 0; i < this->mCount; ++i)
        {
            mSize[i] = 1;
        }
    }

    virtual ~QuickUnion()
    {
        if (mSize != nullptr) {
            delete[] mSize;
        }
    }

    T searchGroup(int index) override
    {
        // 由于每个元素其存储的是该分组所在位置的上一级元素索引
        // 其根节点所存储的才是该分组的组号
        // 所以这里需要不断的向上遍历
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
        return this->searchGroup(pIndex) == this->searchGroup(qIndex);
    }

    void unionGroup(int pIndex, int qIndex) override
    {
        /**
         * 获取两个节点的所在的分组
         */
        int pRoot = this->searchGroup(pIndex);
        int qRoot = this->searchGroup(qIndex);

        if (pRoot == qRoot)
        {
            return;
        }

        /**
         * 如果pRoot分组的节点数小于qRoot分组，那么pRoot分组根节点指向qRoot分组的根节点
         * 并更新qRoot分组的个数
         * 反之亦然
         */
        if (mSize[pRoot] < mSize[qRoot])
        {
            this->mElement[pRoot] = qRoot;
            mSize[qRoot] += mSize[pRoot];
        }
        else
        {
            this->mElement[qRoot] = pRoot;
            mSize[pRoot] += mSize[qRoot];
        }
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
        /**
         * 原理：每个元素存储其对应的分组信息，判断获取设置都可以通过缩影快速的查询设置
         */
        T pGroup = searchGroup(p);
        T qGroup = searchGroup(q);

        if (pGroup == qGroup)
        {
            return;
        }

        // 更新分组信息，另一个分组的分组号会全部的更新
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

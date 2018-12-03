//
// Created by yanghui on 2018/11/21.
//

#include "ISearch.h"

#ifndef DATASTRUCTURE_BINARYSEARCH_H
#define DATASTRUCTURE_BINARYSEARCH_H

/**
 * 二分查询
 */
class BinarySearch
{
public:
    template <typename Item>
    static int normal(Item arr[], int n, Item target);

private:
};

/**
 * 正常的二分查询法
 * @tparam Item 数据类型
 * @param arr 数据缓存
 * @param n 数据长度
 * @param target 要查询的目标
 * @return 返回查找到的索引值
 */
template<typename Item>
int BinarySearch::normal(Item *arr, int n, Item target)
{
    int l = 0;
    int r = n - 1;

    while (l <= r)
    {
        int mid = l + (r - l) / 2;

        if (arr[mid] == target)
        {
            return mid;
        }

        if (arr[mid] < target)
        {
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }

    return -1;
}

/**
 * 二叉树查询
 * @tparam Key 键的数据类型
 * @tparam Value 值的数据类型
 */
template <typename Key, typename Value>
class BST : public ISearch<Key, Value>
{
private:
    // 二叉树节点
    struct Node
    {
        Key key;
        Value value;
        Node* left;
        Node* right;

        Node(Key key, Value value)
        {
            this->key = key;
            this->value = value;
            this->left = this->right = nullptr;
        }
    };

    Node* root;
    int count;

public:
    BST()
    {
        root = nullptr;
        count = 0;
    }

    ~BST()
    {

    }

    int size()
    {
        return count;
    }

    bool isEmpty()
    {
        return count == 0;
    }

    /**
     * 插入节点
     * @param key
     * @param value
     */
    void insert(Key key, Value value) override
    {
        Node* node = this->insert(this->root, key, value);

        if (this->root == nullptr)
        {
            this->root = node;
        }
    }

    /**
     * 搜索某个值
     * @param key
     * @return 如果没有找到返回-1，找到的话返回找到的值
     */
    Value search(Key key) override
    {
        auto node = this->search(this->root, key);

        if (node == nullptr)
        {
            return -1;
        }
        return node->value;
    }

    /**
     * 判断是否包含某个值
     * @param key 键
     * @return true表示包含，false表示没有
     */
    bool contain(Key key)
    {
        return this->contain(this->root, key);
    }

private:
    /**
     * 插入节点
     * @param curNode 当前遍历到的节点
     * @param key 键
     * @param value 值
     * @return 返回遍历到的节点
     */
    Node* insert(Node* curNode, Key key, Value value)
    {
        // 如果当前的节点唯空，表示整个二叉树没有存储此键值，创建一个新的节点返回
        if (curNode == nullptr)
        {
            ++count;
            return new Node(key, value);
        }

        // 如果当前的节点等于key，表示找到node，进行value更新
        if (curNode->key == key)
        {
            curNode->value = value;
        }
        // 如果当前节点key小于key，那么在左孩子里面找
        else if (curNode->key < key)
        {
            curNode->left = this->insert(curNode->left, key, value);
        }
        // 剩余的情况在右孩子里面找
        else
        {
            curNode->right = this->insert(curNode->right, key, value);
        }

        //将自身返回
        return curNode;
    }

    /**
     * 寻找某个节点
     * @param curNode
     * @param key
     * @return 如果找到了则返回该节点的指针，没有找到则返回nullptr
     */
    Node* search(Node* curNode, Key key)
    {
        if (curNode == nullptr)
        {
            return nullptr;
        }

        if (curNode->key == key)
        {
            return curNode;
        }
        else if (curNode->key < key)
        {
            return this->search(curNode->left, key);
        }
        else
        {
            return this->search(curNode->right, key);
        }
    }

    /**
     * 判断是否包含某个key
     * @param node
     * @param key
     * @return
     */
    bool contain(Node* node, Key key)
    {
        // 如果不包含返回false，如果包含则返回true
        if (node == nullptr)
        {
            return false;
        }

        // 判断当前节点是否等于该key，如果不等于则根据key的大小对比，进一步遍历其做孩子还是右孩子
        if (node->key == key)
        {
            return true;
        }
        else if (node->key < key)
        {
            return this->contain(node->left, key);
        }
        else
        {
            return this->contain(node->right, key);
        }
    }
};


#endif //DATASTRUCTURE_BINARYSEARCH_H

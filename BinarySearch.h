//
// Created by yanghui on 2018/11/21.
//

#include "ISearch.h"

#ifndef DATASTRUCTURE_BINARYSEARCH_H
#define DATASTRUCTURE_BINARYSEARCH_H

class BinarySearch
{
public:
    template <typename Item>
    static int normal(Item arr[], int n, Item target);

private:
};

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

template <typename Key, typename Value>
class BST : public ISearch<Key, Value>
{
private:
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

    void insert(Key key, Value value) override
    {
        Node* node = this->insert(this->root, key, value);

        if (this->root == nullptr)
        {
            this->root = node;
        }
    }

    Value search(Key key) override
    {
        auto node = this->search(this->root, key);

        if (node == nullptr)
        {
            return -1;
        }
        return node->value;
    }

    bool contain(Key key)
    {
        return this->contain(this->root, key);
    }

private:
    Node* insert(Node* curNode, Key key, Value value)
    {
        if (curNode == nullptr)
        {
            ++count;
            return new Node(key, value);
        }

        if (curNode->key == key)
        {
            curNode->value = value;
        }
        else if (curNode->key < key)
        {
            curNode->left = this->insert(curNode->left, key, value);
        }
        else
        {
            curNode->right = this->insert(curNode->right, key, value);
        }

        return curNode;
    }

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

    bool contain(Node* node, Key key)
    {
        if (node == nullptr)
        {
            return false;
        }

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

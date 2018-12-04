//
// Created by yanghui on 2018/11/28.
//

#ifndef DATASTRUCTURE_ISEARCH_H
#define DATASTRUCTURE_ISEARCH_H

template <typename Key, typename Value>
class ISearch
{
public:
    virtual void insert(Key key, Value value) = 0;
    virtual Value search(Key key) = 0;
    virtual void traverse() = 0;
};

#endif //DATASTRUCTURE_ISEARCH_H

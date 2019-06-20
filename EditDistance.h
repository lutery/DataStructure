//
// Created by yanghui on 2019-06-20.
//

#ifndef DATASTRUCTURE_EDITDISTANCE_H
#define DATASTRUCTURE_EDITDISTANCE_H

// https://mp.weixin.qq.com/s/FGFkg3VwVnx9U0_SbwIwSg
#include <string>
#include <vector>

class EditDistance
{
public:
    static int editDistDP(std::string s1, std::string s2);

private:
    template <typename... Args>
    static int min(int val, Args... args);
    static int min(int val);
};


#endif //DATASTRUCTURE_EDITDISTANCE_H

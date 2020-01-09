//
// Created by yanghui on 2020-01-09.
//

#ifndef DATASTRUCTURE_BFCOMPARE_H
#define DATASTRUCTURE_BFCOMPARE_H

#include <string>

// https://mp.weixin.qq.com/s/DnjLeZbdhSbSLj6phPXwhQ
class BFCompare
{
public:
    static int index(std::string S, std::string T, int pos)
    {
        int i = pos; // i 表示主串 S 中当前位置下标
        int j = 1;   // j 表示子串 T 中当前位置下标

        while (i <= S[0] && j <= T[0]) // i 或 j 其中一个到达尾部则终止搜索
        {
            if (S[i] == T[j])          // 若相等则继续进行下一个元素匹配
            {
                i++;
                j++;
            }
            else
            {
                i = i - j + 2; // 若匹配失败则 j 回溯到第一个元素重新匹配
                j = 1;         // 将 i 重新回溯到上次匹配首位的下一个元素
            }
        }

        if (j > T[0])
        {
            return i - T[0];
        }
        else
        {
            return 0;
        }
    }
};


#endif //DATASTRUCTURE_BFCOMPARE_H

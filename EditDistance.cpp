//
// Created by yanghui on 2019-06-20.
//

#include "EditDistance.h"

int EditDistance::editDistDP(std::string s1, std::string s2)
{
    int lengthS1 = s1.length();
    int lengthS2 = s2.length();

    std::vector<std::vector<int>> dp(lengthS1 + 1, std::vector<int>(lengthS2 + 1, 0));
//    for (int i = 0; i < lengthS1 + 1; ++i)
//    {
//        for (int j = 0; j < lengthS2 + 1; ++j)
//        {
//            dp[i][j] = 0;
//        }
//    }

    for (int i = 0; i <= lengthS1; ++i)
    {
        for (int j = 0; j <= lengthS2; ++j)
        {
            if (i == 0)
            {
                dp[i][j] = j;
            }
            else if (j == 0)
            {
                dp[i][j] = i;
            }
            else if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = 1 + min(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]);
            }
        }
    }

    return dp[lengthS1][lengthS2];
}

template<typename... Args>
int EditDistance::min(int val, Args... args)
{
    return (val > min(args...)) ? min(args...) : val;
}

int EditDistance::min(int val)
{
    return val;
}

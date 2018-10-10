//
// Created by yanghui on 2018/8/2.
//

#include "ToolUtil.h"

namespace ToolUtil
{
    std::chrono::time_point<std::chrono::steady_clock>& preTime(){
        static std::chrono::time_point<std::chrono::steady_clock> pretime = std::chrono::steady_clock::now();
        return pretime;
    }

    void setPreTime(std::chrono::time_point<std::chrono::steady_clock> time_point){
        preTime() = time_point;
    }

    std::chrono::time_point<std::chrono::steady_clock>& nowTime(){
        static std::chrono::time_point<std::chrono::steady_clock> nowtime = std::chrono::steady_clock::now();
        return nowtime;
    }

    void setNowTime(std::chrono::time_point<std::chrono::steady_clock> time_point){
        nowTime() = time_point;
    }

    void start(){
        ToolUtil::setNowTime(std::chrono::steady_clock::now());
    }

    void tick(){
        ToolUtil::setPreTime(ToolUtil::nowTime());
        ToolUtil::setNowTime(std::chrono::steady_clock::now());
    }
}
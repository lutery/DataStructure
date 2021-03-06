//
// Created by yanghui on 2018/8/2.
//

#ifndef DATASTRUCTURE_TOOLUTIL_H
#define DATASTRUCTURE_TOOLUTIL_H

#include <chrono>
#include <tuple>
#include <string>

namespace ToolUtil
{
    std::chrono::time_point<std::chrono::steady_clock>& preTime();

    void setPreTime(std::chrono::time_point<std::chrono::steady_clock> time_point);

    std::chrono::time_point<std::chrono::steady_clock>& nowTime();

    void setNowTime(std::chrono::time_point<std::chrono::steady_clock> time_point);
    void start();

    void tick();

    template<class TimeUnit>
    int clock(){
        ToolUtil::setPreTime(ToolUtil::nowTime());
        ToolUtil::setNowTime(std::chrono::steady_clock::now());

        TimeUnit diff = std::chrono::duration_cast<TimeUnit>(ToolUtil::nowTime() - ToolUtil::preTime());

        return diff.count();
    }

    template<class TimeUnit, class Fun, class... Args>
    decltype(auto) funClock(Fun&& f, Args&&... args)
    noexcept(noexcept(std::forward<Fun>(f)(std::forward<Args>(args)...)))
    {
        auto start = std::chrono::steady_clock::now();
        auto rtl = std::forward<Fun>(f)(std::forward<Args>(args)...);
        TimeUnit diff = std::chrono::duration_cast<TimeUnit>(std::chrono::steady_clock::now() - start);
        return std::make_tuple(diff.count(), rtl);
    }

    template<class TimeUnit, class Fun, class... Args>
    decltype(auto) funNClock(Fun&& f, Args&&... args)
    noexcept(noexcept(std::forward<Fun>(f)(std::forward<Args>(args)...)))
    {
        auto start = std::chrono::steady_clock::now();
        std::forward<Fun>(f)(std::forward<Args>(args)...);
        TimeUnit diff = std::chrono::duration_cast<TimeUnit>(std::chrono::steady_clock::now() - start);
        return diff.count();
    }

    template<class TimeUnit, class Fun, class SELF, class... Args>
    decltype(auto) cfunClock(Fun&& f, SELF* self, Args&&... args)
    noexcept(noexcept((self->*(std::forward<Fun>(f)))(std::forward<Args>(args)...)))
    {
        auto start = std::chrono::steady_clock::now();
        auto rtl = (self->*(std::forward<Fun>(f)))(std::forward<Args>(args)...);
        TimeUnit diff = std::chrono::duration_cast<TimeUnit>(std::chrono::steady_clock::now() - start);
        return std::make_tuple(diff.count(), rtl);
    }

    template<class TimeUnit, class Fun, class SELF, class... Args>
    decltype(auto) cfunNClock(Fun&& f, SELF* self, Args&&... args)
    noexcept(noexcept((self->*(std::forward<Fun>(f)))(std::forward<Args>(args)...)))
    {
        auto start = std::chrono::steady_clock::now();
        (self->*(std::forward<Fun>(f)))(std::forward<Args>(args)...);
        TimeUnit diff = std::chrono::duration_cast<TimeUnit>(std::chrono::steady_clock::now() - start);
        return diff.count();
    }
}

#endif //DATASTRUCTURE_TOOLUTIL_H

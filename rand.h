
#ifndef UNTITLED_RAND_H
#define UNTITLED_RAND_H

#include <random>
#include "sfinae.h"

class r
{
    static std::default_random_engine& engine()
    {
        static std::default_random_engine e(std::random_device{}());
        return e;
    }

public:
    template<typename T, typename std::enable_if_t<std::is_integral_v<T>, int> = 0>
    static T get()
    {
        std::uniform_int_distribution<T> distribution;
        return distribution(engine());
    }

    template<typename T, typename std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
    static T get()
    {
        std::uniform_real_distribution<T> distribution;
        return distribution(engine());
    }

    template<typename T, typename std::enable_if_t<is_bool_v<T>, int> = 0>
    static T get()
    {
        std::bernoulli_distribution distribution;
        return distribution(engine());
    }
};

template<typename T>
T random()
{
    return r::get<T>();
}

#endif //UNTITLED_RAND_H

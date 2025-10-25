#ifndef __DATA_SET_H__
#define __DATA_SET_H__

#include <list>
#include <cstdlib>
#include <iostream>
#include <chrono>

class data_set
{
public:
    data_set()
    {
    }

    double get_val(const unsigned int seed, const double lower, const double upper, const long step)
    {
        std::srand(seed);
        return lower + (upper - lower) * (random() % step) / step;
    }

    std::list<double> get_list(const unsigned int size, const double lower, const double upper, const long step)
    {
        std::list<double> out;
        auto start = std::chrono::high_resolution_clock::now();

        for (unsigned int index = 0; index < size; index++)
        {
            auto finish = std::chrono::high_resolution_clock::now();
            out.push_back(get_val(std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count(), lower, upper, step));
        }
        return out;
    }
};

#endif
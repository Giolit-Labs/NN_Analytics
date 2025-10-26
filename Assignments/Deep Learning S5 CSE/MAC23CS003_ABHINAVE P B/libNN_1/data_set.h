#ifndef __DATA_SET_H__
#define __DATA_SET_H__

#include <list>
#include <cstdlib>
#include <iostream>
#include <random>   // added for random number generation

class data_set
{
public:

    data_set() = default;  // Correct default constructor

    // Get a random value between lower_bound and upper_bound
    double get_val(double lower_bound, double upper_bound)
    {    	
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dist(lower_bound, upper_bound);
        return dist(gen);
    }

    // Get a list of random values
    std::list<double> get_list(unsigned int size, double lower_bound, double upper_bound)
    {
        std::list<double> values;
        for (unsigned int i = 0; i < size; ++i)
        {
            values.push_back(get_val(lower_bound, upper_bound));
        }
        return values;
    }
};

#endif

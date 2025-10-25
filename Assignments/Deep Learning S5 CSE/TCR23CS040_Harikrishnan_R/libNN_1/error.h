#ifndef __ERROR_H__
#define __ERROR_H__

#include <list>
#include <iostream>
#include <cassert>

class error
{
public:
    std::list<double> err;

    error()
    {
    }

    error(std::list<double> &_err) : err(_err)
    {
    }

    void set_error(std::list<double> &error)
    {
        assert(err.size() == error.size());

        auto it_err = err.begin();
        auto it_error = error.begin();

        while (it_err != err.end())
        {
            *it_err = *it_error;
            ++it_err;
            ++it_error;
        }
    }

    void print()
    {
        std::cout << "Error: [";
        for (auto field : err)
        {
            printf("%f ", field);
        }
        std::cout << "]" << std::endl;
    }
};

#endif
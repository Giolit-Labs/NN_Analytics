#ifndef __ERROR_H__
#define __ERROR_H__

#include <list>
#include <iostream>
#include <assert.h>

class error
{
public:
    std::list<double> err;

    error() {}

    error(std::list<double>& _err) : err(_err) {}

    void set_error(std::list<double>& error_list)
    {
        assert(err.size() == error_list.size());

        auto it_err = err.begin();
        auto it_error = error_list.begin();

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

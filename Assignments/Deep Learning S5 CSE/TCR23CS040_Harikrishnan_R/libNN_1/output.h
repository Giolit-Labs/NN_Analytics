#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include <iostream>
#include <list>

class output
{
public:
    std::list<double *> out;

    output()
    {
    }

    output(std::list<double *> &_out) : out(_out)
    {
    }

    std::list<double> get_out_put()
    {
        std::list<double> result;

        for (auto it = out.begin(); it != out.end(); ++it)
        {
            result.push_back(**it);
        }

        return result;
    }

    void print()
    {
        std::cout << "Output: [";
        for (auto field : out)
        {
            printf("%f ", *field);
        }
        std::cout << "]" << std::endl;
    }
};

#endif
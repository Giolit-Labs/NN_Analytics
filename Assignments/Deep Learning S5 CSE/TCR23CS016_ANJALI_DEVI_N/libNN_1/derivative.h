#ifndef __DERIVATIVE_H__
#define __DERIVATIVE_H__

#include <cmath>
#include "global_enum.h"

class derivative 
{
public:

    derivative() {}

    double loss(ACT_FUN id, double x) 
    {
        switch (id)
        {
            case ACT_FUN::sigmoid:
                return sigmoid(x);

            case ACT_FUN::relu:
                return relu(x);

            case ACT_FUN::tanh_act:
                return tanh_fn(x);

            case ACT_FUN::leaky_relu:
                return leaky_relu(x);

            default:
                return x;
        }		
    }

    double sigmoid(double x)
    {
        double s = 1.0 / (1.0 + std::exp(-x));
        return s * (1.0 - s);
    }

    double relu(double x)
    {
        return (x > 0.0) ? 1.0 : 0.0;
    }

    double leaky_relu(double x)
    {
        return (x > 0.0) ? 1.0 : 0.01;
    }

    double tanh_fn(double x)
    {
        double t = std::tanh(x);
        return 1.0 - (t * t);
    }
};

#endif

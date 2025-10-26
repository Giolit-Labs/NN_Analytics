#ifndef __ACTIVATION_H__
#define __ACTIVATION_H__

#include "global_enum.h"
#include <cmath>   // for std::tanh, std::exp

class activation 
{
public:
    activation() {}

    double function (ACT_FUN id, double x) 
{
    switch (id)
    {
        case ACT_FUN::sigmoid:
            return sigmoid(x);
        case ACT_FUN::relu:
            return relu(x);
        case ACT_FUN::tanh_act:   // renamed
            return tanh(x);       // standard math function
        case ACT_FUN::leaky_relu:
            return leaky_relu(x);
        default:
            return x;
    }        
}


    double sigmoid(double x)
    {
        return 1.0 / (1.0 + std::exp(-x));
    }

    double relu(double x)
    {
        return (x > 0.0) ? x : 0.0;
    }

    double leaky_relu(double x)
    {
        return (x > 0.0) ? x : 0.01 * x;  // typical small slope for negative x
    }

    double tanh_activation(double x)  // renamed from tanh to avoid conflict
    {
        return std::tanh(x);
    }
};

#endif

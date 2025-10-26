#ifndef __ACTIVATION_H__
#define __ACTIVATION_H__

#include "global_enum.h"
#include <cmath>
#include <iostream>

class activation 
{
	public:
	
		activation ()
		{
		
		}
	
		double function (ACT_FUN id, double x,double alpha = 0.01) 
		{
			switch (id)
			{
				case ACT_FUN::sigmoid:
				
					return  sigmoid(x);
				
				case ACT_FUN::relu:
				
					return  relu(x);
				
				case ACT_FUN::tanh_act:
				
					return  tanh_act(x);
				
				case ACT_FUN::leaky_relu:
				
					return  leaky_relu(x,alpha);
					
				default:
				
					return x;
			}		
		}
	
		double sigmoid (double x)
		{
			return 1.0 / (1.0 + std::exp(-x));
		}

		double relu(double x)
		{
			return std::max(0.0, x);
		}

		double leaky_relu(double x, double alpha = 0.01)
		{
			return x > 0 ? x : alpha * x;
		}
		
		double tanh_act(double x)
    	{
        	return std::tanh(x);
    	}
};

#endif


#ifndef __ACTIVATION_H__
#define __ACTIVATION_H__

#include "global_enum.h"
#include <cmath>

class activation 
{
	public:
	
		activation ()
		{
		
		}
	
		double function (ACT_FUN id, double x) 
		{
			switch (id)
			{
				case ACT_FUN::SIGMOID:
				
					return  sigmoid (x);
				
				case ACT_FUN::RELU:
				
					return  relu (x);
				
				case ACT_FUN::TANH:
				
					return  tanh_func (x);
				
				case ACT_FUN::LEAKY_RELU:
				
					return  leaky_relu (x);
					
				default:
				
					return x;
			}		
		}
	
		double sigmoid (double x)
		{
			return 1.0 / (1.0 + exp(-x));
		}

		double relu (double x)
		{
			if (x > 0.0) 
			{
				return x;
			}
		
			return 0.0;
		}

		double leaky_relu (double x)
		{
			if (x > 0.0) 
			{
				return x;
			}
		
			return 0.01 * x; // Small positive slope for negative values
		}
		
		double tanh_func (double x)
		{
			return std::tanh(x);
		}
};

#endif
#ifndef __DERIVATIVE_H__
#define __DERIVATIVE_H__

#include "global_enum.h"
#include <cmath>

class derivative 
{
	public:
	
		derivative ()
		{
		
		}
	
		double loss (ACT_FUN id, double x) 
		{
			switch (id)
			{
				case ACT_FUN::sigmoid:
					return sigmoid (x);
				
				case ACT_FUN::tanh_func:
					return tanh_func (x);
				
				case ACT_FUN::relu:
					return relu (x);
				
				case ACT_FUN::leaky_relu:
					return leaky_relu (x);
					
				case ACT_FUN::linear:
					return linear(x);
					
				default:
					return x;
			}		
		}
	
		double sigmoid (double x)
		{
			return (x * (1-x));
		}

		double relu (double x)
		{
			if (x > 0.0) 
			{
				return 1.0;
			}
			return 0;
		}

		double leaky_relu (double x)
		{
			if (x > 0.0) 
			{
				return 1.0;
			}
			return 0.01;
		}
		
		double tanh_func (double x)
		{
			return 1.0 - std::tanh(x) * std::tanh(x);
		}
		
		double linear (double x)
		{
			return 1.0;  // Derivative of linear function is 1
		}
};

#endif
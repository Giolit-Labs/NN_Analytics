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
				case ACT_FUN::SIGMOID:
				
					return  sigmoid (x);
				
				case ACT_FUN::RELU:
				
					return  relu (x);
				
				case ACT_FUN::TANH:
				
					return  tanh_deriv (x);
				
				case ACT_FUN::LEAKY_RELU:
				
					return  leaky_relu (x);
					
				default:
				
					return 1.0; // Default to 1.0 for linear activation
			}		
		}
	
		double sigmoid (double x)
		{
			// Derivative of sigmoid: f'(x) = f(x) * (1 - f(x))
			// But since x is already the output of sigmoid, we use:
			return (x * (1 - x));
		}

		double relu (double x)
		{
			if (x > 0.0) 
			{
				return 1.0;
			}
		
			return 0.0;
		}

		double leaky_relu (double x)
		{
			if (x > 0.0) 
			{
				return 1.0;
			}
		
			return 0.01; // Derivative of leaky ReLU: 1 for x>0, 0.01 for x<=0
		}
		
		double tanh_deriv (double x)
		{
			// Derivative of tanh: f'(x) = 1 - f(x)^2
			// But since x is already the output of tanh, we use:
			return (1 - x * x);
		}
};

#endif
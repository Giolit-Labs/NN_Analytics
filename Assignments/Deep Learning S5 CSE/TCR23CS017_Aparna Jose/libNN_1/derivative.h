#ifndef __DERIVATIVE_H__
#define __DERIVATIVE_H__

#include "global_enum.h"

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
				
					return  sigmoid (x);
				
				case ACT_FUN::relu:
				
					return  relu (x);
				
				case ACT_FUN::tanh:
				
					return  tanh (x);
				
				case ACT_FUN::leaky_relu:
				
					return  leaky_relu (x);
					
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
		
			return (0.01 * x);
		}
		
		double tanh (double x)
		{
			return x;
		}
};

#endif


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
				
					return  sigmoid (x);
				
				case ACT_FUN::relu:
				
					return  relu (x);
				
				case ACT_FUN::tanh_act:
				
					return  tanh_act (x);
				
				case ACT_FUN::leaky_relu:
				
					return  leaky_relu (x);
					
				default:
				
					return 1.0;
			}		
		}
	
		double sigmoid (double x)
		{
			return x * (1.0-x);
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
			return 0.01;
		}
		
		double tanh_act (double x)
		{
			double t = std::tanh(x);
			return 1.0-t*t;
		}
};

#endif


#ifndef __ACTIVATION_H__
#define __ACTIVATION_H__

#include "global_enum.h"

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
			return x;
		}

		double relu (double x)
		{
			if (x > 0.0) 
			{
				return x;
			}
		
			return 0;
		}

		double leaky_relu (double x)
		{
			if(x>0.0)
				return x;
			return (0.01*x);
		}
		
		double tanh (double x)
		{
			return x;
		}
};

#endif


#ifndef __DATA_SET_H__
#define __DATA_SET_H__

#include <list> 
#include <cstdlib> 
#include <iostream>

class data_set
{
	public:

		data_set () 
		{			
		
		}
	
		double get_val (const unsigned int seed, const double lower_bound, const double upper_bound, const long max_rand) 
		{    	
		    	std::srand (seed);

		   	return lower_bound + (upper_bound - lower_bound) * (rand() % max_rand) / max_rand;
		}


		std::list<double> get_list (const unsigned int size, const double lower_bound, const double upper_bound, const long max_rand) 
		{
		    	std::list<double> _list;
		    	
		    	auto start = std::chrono::high_resolution_clock::now();
		    	
		    	for (unsigned int index = 0; index < size; index++)
		    	{
		    		auto finish = std::chrono::high_resolution_clock::now();
		    	
		    		_list.push_back (get_val (std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count(), lower_bound, upper_bound, max_rand));	
		    	}
		    	
		    	return _list;
		}
};

#endif

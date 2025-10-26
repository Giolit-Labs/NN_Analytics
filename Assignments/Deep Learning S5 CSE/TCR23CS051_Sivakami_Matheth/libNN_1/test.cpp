#include <iostream>
#include <chrono>
#include <list> 

using namespace std;

double get_val (const unsigned int seed, const double lower_bound, const double upper_bound, const long max_rand) 
{    	
    	std::srand (seed);

   	return lower_bound + (upper_bound - lower_bound) * (random() % max_rand) / max_rand;
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



int main()
{ 
 	std::list<double> ip_list = get_list (3, -1000, 1000, 1000000);
 
 	std::list<double> op_list = get_list (3, -1000, 1000, 1000000);
 
 	for (auto item: ip_list)
 	{
 		std::cout << item << std::endl;
 	}
  
 	for (auto item: op_list)
 	{
 		std::cout << item << std::endl;
 	}
 
    	return 0;
}


/*
#include <list> 
#include <iostream>

	int main ()
	{
	
		std::list<double> in = {1, 2, 3, 4};

		std::list<double*> out;
		
		out.push_back (&(in[0]));

		out.push_back (&(in[1]));
		
		out.push_back (&(in[2]));
		
		out.push_back (&(in[3]));
						
		for (auto field : out)
		{
			std::cout << (*field) <<std::endl;
		}

		in[0] = 10;
		
		in[1] = 11;
		
		in[2] = 12;
		
		in[3] = 13;

		for (auto field : out)
		{
			std::cout << (*field) <<std::endl;
		}
		return 0;
	}	
*/

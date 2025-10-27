#ifndef __INPUT_H__
#define __INPUT_H__


#include <list> 
//my change
#include <iostream>
#include <cassert>

class input
{
	public:
		std::list<double> in;
		
		std::list<std::pair<bool, double>> w_out;
		
		input ()
		{
		
		}
	
		input (std::list<double>& _in) : in (_in)
		{
		
		}
		
		void print () 
		{
			std::cout << "Input: [";
		
			for (auto field : in) 
			{
				printf ("%f ", field);
			}
		
			std::cout << "]" <<std::endl;
		}
		
		// void set_input (std::list<double>& input)
		// {
		// 	assert (in.size () == input.size ());
			
		// 	auto it_in = in.begin ();
			
		// 	auto it_input = input.begin ();
			
		// 	while (it_in != in.end ())
		// 	{
		// 		*it_in = *it_input;
				
		// 		++it_in;
				
		// 		++it_input;
		// 	}
		// }
		void set_input(std::list<double>& new_input)
    {
        // Clear previous input and copy new values
        in.clear();
        in.insert(in.begin(), new_input.begin(), new_input.end());
    }
};

#endif

#ifndef __NEURON_H__
#define __NEURON_H__

#include <string>
#include <list> 
#include <assert.h> 
#include <cmath>
#include "resonant_activation.h"
#include "output.h"
#include "input.h"
#include "error.h"
#include "label.h"
#include "structures.h"

class neuron 
{
	public:	
		double learning_rate;
		bool in_forward;
		bool in_backward;
		
		neuron () : learning_rate(0.01), in_forward(false), in_backward(false)
		{
		}
		
		void forward (std::list<node>::iterator n_id) 
		{
			assert (n_id->w_in.size () == n_id->in.size ());
		
			double result = 0;
			auto it_in = n_id->in.begin (); 
			auto it_w_in = n_id->w_in.begin (); 

			while (it_in != n_id->in.end ()) 
			{
				result +=  (**it_in) * (**it_w_in);
				++it_in;
				++it_w_in;
			}

			double activation_input = result + n_id->b;
			
			// 🌟 ACTIVATION FUNCTIONS
			if (n_id->f == sigmoid) {
				n_id->out = 1.0 / (1.0 + std::exp(-activation_input));
			}
			else if (n_id->f == tanh_func) {
				n_id->out = std::tanh(activation_input);
			}
			else if (n_id->f == relu) {
				n_id->out = (activation_input > 0) ? activation_input : 0;
			}
			else if (n_id->f == leaky_relu) {
				n_id->out = (activation_input > 0) ? activation_input : 0.01 * activation_input;
			}
			else if (n_id->f == resonant_func) {  // 🌟 CHANGED to resonant_func
				n_id->out = resonant(activation_input);
			}
			else {
				n_id->out = activation_input;
			}
		}
			
		void backward (std::list<node>::iterator n_id)
		{
			assert (n_id->w_out.size () == n_id->error.size ());
			
			double acc_err = 0;
			auto e_id = n_id->error.begin ();
			auto l_id = n_id->label.begin ();
			auto w_id = n_id->w_out.begin ();
			
			while (e_id != n_id->error.end () && l_id != n_id->label.end () && w_id != n_id->w_out.end ())
			{
				if (**e_id != 0.0)
				{	
					if ((**l_id != 0.0) && ((n_id->out * w_id->second) / **l_id) > 0.0)
					{	
						**e_id = **e_id * ((n_id->out * w_id->second) / **l_id);				
					} else {
						**e_id = **e_id * ( 0.0 - ((n_id->out * w_id->second) / **l_id));	
					}
					
					if ((w_id->first) && (n_id->out != 0))
					{
						w_id->second += (**e_id * learning_rate / n_id->out);
						if (w_id->second != 0) 
						{										
							acc_err += (**e_id / w_id->second);
						}
					} else {
						acc_err += **e_id;	
					}
				}
				++e_id;
				++l_id;
				++w_id;
			}
			
			if (n_id->w_out.size () > 0)
			{
				acc_err = acc_err / n_id->w_out.size ();				
			}

			// 🌟 DERIVATIVE CALCULATIONS
			double derivative_val = 0;
			if (n_id->f == sigmoid) {
				derivative_val = n_id->out * (1 - n_id->out);
			}
			else if (n_id->f == tanh_func) {
				derivative_val = 1 - (n_id->out * n_id->out);
			}
			else if (n_id->f == relu) {
				derivative_val = (n_id->out > 0) ? 1 : 0;
			}
			else if (n_id->f == leaky_relu) {
				derivative_val = (n_id->out > 0) ? 1 : 0.01;
			}
			else if (n_id->f == resonant_func) {  // 🌟 CHANGED to resonant_func
				derivative_val = resonant_derivative(n_id->out);
			}
			else {
				derivative_val = 1.0;
			}
			
			n_id->b += (learning_rate * acc_err * derivative_val);
			n_id->delta = acc_err * derivative_val;
		}
};

#endif
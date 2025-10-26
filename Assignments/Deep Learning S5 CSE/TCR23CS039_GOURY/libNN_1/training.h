#ifndef __TRAINING_H__
#define __TRAINING_H__

#include "data_set.h"
#include "network.h"

class training
{
	public:
		training ()
		{
		
		}
	
		bool is_close (std::list<double> out_put, std::list<double> label, double delta)
		{
			assert (out_put.size () == label.size ());
			
			auto it_label = label.begin ();
			
			auto it_out_put = out_put.begin ();
			
			while (it_out_put != out_put.end ())
			{
				if ((*it_out_put - *it_label > delta) || (*it_label - *it_out_put > delta))   
				{
					return false;
				}
				
				it_label++;
				
				it_out_put++;
			}
			
			return true;
		}

		std::list<double> difference (std::list<double> out_put, std::list<double>& label)
		{
			assert (out_put.size () == label.size ());
			
			std::list<double> result;
			
			auto it_label = label.begin ();
			
			auto it_out_put = out_put.begin ();
			
			while (it_out_put != out_put.end ())
			{
				result.push_back (*it_label - *it_out_put);
			
				it_label++;
				
				it_out_put++;
			}
			
			return result;
		}	

		bool train (network& model, unsigned int epoch, std::list<double>& input, std::list<double>& label, double delta)
		{
			model.set_input (input);
			
			model.set_label (label);
				
			model.input::print ();
	
			for (unsigned int step = 0; step < epoch; ++step)
			{	
				model.predict ();
				
				model.output::print ();
				
				std::list<double> error = difference (model.get_out_put (), label);
				
				model.set_error (error);
				
				model.error::print ();
				
				model.train ();
				
				//model.print_weight ();
			}
			
			return is_close (model.get_out_put (), label, delta);
		}
		
		bool train (network& model, std::list<double>& input, std::list<double>& label, double delta)
		{
			model.set_input (input);
			
			model.set_label (label);
				
			//model.input::print ();
			
			unsigned int step = 0;
			model.set_learning_rate(0.01);

			while (!is_close (model.get_out_put (), label, delta))
			{	
				if (step == 10000) break;
				{
					//model.input::print ();
				
					//model.label::print ();

					//model.output::print();
					
					//model.error::print ();
					
					//model.print_weight ();
				
					return false;
				}
			
				model.predict ();
				
				//model.output::print ();
				
				std::list<double> error = difference (model.get_out_put (), label);
				
				model.set_error (error);
				
				//model.error::print ();
				
				model.train ();
				
				//model.print_weight ();
				
				++step;
			}
			
			//model.input::print ();
				
			//model.label::print ();

			//model.output::print();

			//model.error::print ();
	
			//model.print_weight ();
			
			return true;
		}
};

#endif

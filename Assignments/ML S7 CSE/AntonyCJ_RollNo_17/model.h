#ifndef __MODEL_H__
#define __MODEL_H__




#include "network.h"
#include <cmath>

class model
{
	public:
		network _nn = network ();
	
		model ()
		{
		
		}
		
		void set ()
		{
			std::list<std::list<std::pair<ACT_FUN, double>>> node_list;
			
			// This defines a 3-layer network for sin(x) prediction:
			// Layer 0: 1 neuron (Input Layer)
			// Layer 1: 8 neurons (Hidden Layer)
			// Layer 2: 1 neuron (Output Layer)
			node_list = {
				// Layer 0: 1 input neuron (SIGMOID for stable input)
				{{ACT_FUN::SIGMOID, 1.0}},
				
				// Layer 1: 8 hidden neurons (TANH for periodic functions)
				{{ACT_FUN::TANH, 1.0}, {ACT_FUN::TANH, 1.0}, {ACT_FUN::TANH, 1.0}, 
				 {ACT_FUN::TANH, 1.0}, {ACT_FUN::TANH, 1.0}, {ACT_FUN::TANH, 1.0},
				 {ACT_FUN::TANH, 1.0}, {ACT_FUN::TANH, 1.0}},
				
				// Layer 2: 1 output neuron (TANH for bounded output between -1 and 1)
				{{ACT_FUN::TANH, 1.0}}
			};
			
			_nn.initialize (node_list);		
			
			// Much smaller learning rate to prevent NaN
			_nn.set_learning_rate (0.0000001); 

			// Connect 1 input to the 1 neuron of the first layer (Layer 0)
			ip_to_nn i1 = {0, 0, 0, 0.1, false}; // Smaller initial weight
			_nn.add (i1);

			// Connect Layer 0 (1 neuron) to Layer 1 (8 neurons) - smaller weights
			nn_to_nn n0n10 = {0, 0, 0, 1, 0, 0, 0.1, true};
			nn_to_nn n0n11 = {0, 0, 0, 1, 1, 0, 0.1, true};
			nn_to_nn n0n12 = {0, 0, 0, 1, 2, 0, 0.1, true};
			nn_to_nn n0n13 = {0, 0, 0, 1, 3, 0, 0.1, true};
			nn_to_nn n0n14 = {0, 0, 0, 1, 4, 0, 0.1, true};
			nn_to_nn n0n15 = {0, 0, 0, 1, 5, 0, 0.1, true};
			nn_to_nn n0n16 = {0, 0, 0, 1, 6, 0, 0.1, true};
			nn_to_nn n0n17 = {0, 0, 0, 1, 7, 0, 0.1, true};
			
			_nn.add (n0n10);
			_nn.add (n0n11);
			_nn.add (n0n12);
			_nn.add (n0n13);
			_nn.add (n0n14);
			_nn.add (n0n15);
			_nn.add (n0n16);
			_nn.add (n0n17);
			
			// Connect Layer 1 (8 neurons) to Layer 2 (1 neuron) - smaller weights
			nn_to_nn n1n20 = {1, 0, 0, 2, 0, 0, 0.1, true};
			nn_to_nn n1n21 = {1, 1, 0, 2, 0, 0, 0.1, true};
			nn_to_nn n1n22 = {1, 2, 0, 2, 0, 0, 0.1, true};
			nn_to_nn n1n23 = {1, 3, 0, 2, 0, 0, 0.1, true};
			nn_to_nn n1n24 = {1, 4, 0, 2, 0, 0, 0.1, true};
			nn_to_nn n1n25 = {1, 5, 0, 2, 0, 0, 0.1, true};
			nn_to_nn n1n26 = {1, 6, 0, 2, 0, 0, 0.1, true};
			nn_to_nn n1n27 = {1, 7, 0, 2, 0, 0, 0.1, true};
			
			_nn.add (n1n20);
			_nn.add (n1n21);
			_nn.add (n1n22);
			_nn.add (n1n23);
			_nn.add (n1n24);
			_nn.add (n1n25);
			_nn.add (n1n26);
			_nn.add (n1n27);

			// Connect the 1 neuron of the output layer (Layer 2) to the overall output
			nn_to_op o1 = {2, 0, 0, 0.1, false}; // Smaller weight
			_nn.add (o1);
		}
		
		// Helper function to normalize input x to [0, 1] range for 0 to 2π
		double normalize_input(double x) {
			return x / (2 * M_PI);
		}
};

#endif
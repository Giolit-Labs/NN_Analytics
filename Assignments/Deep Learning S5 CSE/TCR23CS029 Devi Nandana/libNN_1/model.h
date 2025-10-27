#ifndef _MODEL_H_
#define _MODEL_H_

#include "network.h"

                                              class model
{
public:
    network _nn = network();

    model()
    {
    }

    // void set()
    // {
    //     std::list<std::list<std::pair<ACT_FUN, double>>> node_list;

    //     // This defines a 3-layer network:
    //     // Layer 0: 3 neurons (Input Layer)
    //     // Layer 1: 3 neurons (Hidden Layer)
    //     // Layer 2: 3 neurons (Output Layer)
    //     node_list = {
    //         {{ACT_FUN::leaky_relu, 4.0}, {ACT_FUN::leaky_relu, 4.0}, {ACT_FUN::leaky_relu, 4.0}},

    //         {{ACT_FUN::leaky_relu, 5.0}, {ACT_FUN::leaky_relu, 2.0}, {ACT_FUN::leaky_relu, 4.0}},

    //         {{ACT_FUN::leaky_relu, 3.0}, {ACT_FUN::leaky_relu, 3.0}, {ACT_FUN::leaky_relu, 3.0}}};

    //     _nn.initialize(node_list);

    //     // A higher learning rate for a linear problem
    //     _nn.set_learning_rate(0.000001);

    //     // Connects 3 inputs to the 3 neurons of the first layer (Layer 0)
    //     ip_to_nn i1 = {0, 0, 0, 1.0, false};
    //     ip_to_nn i2 = {0, 1, 0, -1.0, false};
    //     ip_to_nn i3 = {0, 2, 0, -1.0, false};

    //     _nn.add(i1);
    //     _nn.add(i2);
    //     _nn.add(i3);

    //     // Connects all neurons in Layer 0 to all neurons in Layer 1 (Fully Connected)
    //     nn_to_nn n0n10 = {0, 0, 0, 1, 0, 0, 1.0, true};
    //     nn_to_nn n0n11 = {0, 0, 0, 1, 1, 0, 1.0, true};
    //     nn_to_nn n0n12 = {0, 0, 0, 1, 2, 0, 1.0, true};

    //     nn_to_nn n0n20 = {0, 1, 0, 1, 0, 0, 1.0, true};
    //     nn_to_nn n0n21 = {0, 1, 0, 1, 1, 0, 1.0, true};
    //     nn_to_nn n0n22 = {0, 1, 0, 1, 2, 0, 1.0, true};

    //     nn_to_nn n0n30 = {0, 2, 0, 1, 0, 0, 1.0, true};
    //     nn_to_nn n0n31 = {0, 2, 0, 1, 1, 0, 1.0, true};
    //     nn_to_nn n0n32 = {0, 2, 0, 1, 2, 0, 1.0, true};

    //     _nn.add(n0n10);
    //     _nn.add(n0n11);
    //     _nn.add(n0n12);
    //     _nn.add(n0n20);
    //     _nn.add(n0n21);
    //     _nn.add(n0n22);
    //     _nn.add(n0n30);
    //     _nn.add(n0n31);
    //     _nn.add(n0n32);

    //     // Connects all neurons in Layer 1 to all neurons in Layer 2 (Fully Connected)
    //     nn_to_nn n1n20 = {1, 0, 0, 2, 0, 0, 1.0, true};
    //     nn_to_nn n1n21 = {1, 0, 0, 2, 1, 0, 1.0, true};
    //     nn_to_nn n1n22 = {1, 0, 0, 2, 2, 0, 1.0, true};

    //     nn_to_nn n1n23 = {1, 1, 0, 2, 0, 0, 1.0, true};
    //     nn_to_nn n1n24 = {1, 1, 0, 2, 1, 0, 1.0, true};
    //     nn_to_nn n1n25 = {1, 1, 0, 2, 2, 0, 1.0, true};

    //     nn_to_nn n1n26 = {1, 2, 0, 2, 0, 0, 1.0, true};
    //     nn_to_nn n1n27 = {1, 2, 0, 2, 1, 0, 1.0, true};
    //     nn_to_nn n1n28 = {1, 2, 0, 2, 2, 0, 1.0, true};

    //     _nn.add(n1n20);
    //     _nn.add(n1n21);
    //     _nn.add(n1n22);
    //     _nn.add(n1n23);
    //     _nn.add(n1n24);
    //     _nn.add(n1n25);
    //     _nn.add(n1n26);
    //     _nn.add(n1n27);
    //     _nn.add(n1n28);

    //     // Connects the 3 neurons of the output layer (Layer 2) to the overall output
    //     nn_to_op o1 = {2, 0, 0, 1.0, false};
    //     nn_to_op o2 = {2, 1, 0, 1.0, false};
    //     nn_to_op o3 = {2, 2, 0, 1.0, false};

    //     _nn.add(o1);
    //     _nn.add(o2);
    //     _nn.add(o3);
    // }
    void set()
{
    std::list<std::list<std::pair<ACT_FUN, double>>> node_list;

    // Simpler and efficient network for AP prediction
    // 3 input neurons → 1 hidden layer (4 neurons) → 3 output neurons
    node_list = {
        {{ACT_FUN::relu, 4.0}, {ACT_FUN::relu, 4.0}, {ACT_FUN::relu, 4.0}},   // Input layer
        {{ACT_FUN::relu, 5.0}, {ACT_FUN::relu, 5.0}, {ACT_FUN::relu, 5.0}, {ACT_FUN::relu, 5.0}},  // Hidden layer
        {{ACT_FUN::relu, 3.0}, {ACT_FUN::relu, 3.0}, {ACT_FUN::relu, 3.0}}  // Output layer
    };

    _nn.initialize(node_list);

    
    _nn.set_learning_rate(0.00001);

    // Connections (3 inputs → 4 hidden → 3 output)
    // Input to hidden

    for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                nn_to_nn c = {0, static_cast<unsigned>(i), 0, 1, static_cast<unsigned>(j), 0, 1.0, true};
                _nn.add(c);
            }
        }

    // Hidden to output

    for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                nn_to_nn c = {1, static_cast<unsigned>(i), 0, 2, static_cast<unsigned>(j), 0, 1.0, true};
                _nn.add(c);
            }
        }

    // Outputs

    for (int i = 0; i < 3; i++)
        {
            nn_to_op o = {2, static_cast<unsigned>(i), 0, 1.0, false};
            _nn.add(o);
        }
}

};

#endif
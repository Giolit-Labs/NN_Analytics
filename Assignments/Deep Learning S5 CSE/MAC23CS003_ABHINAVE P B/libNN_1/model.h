#ifndef _MODEL_H_
#define _MODEL_H_

#include "network.h"
#include <random>  // make sure to include this

class model
{
public:
    network _nn = network();  // Neural network instance

    model() {}
 void set()
{
    // Define layers and neurons (5 layers: input, hidden1, hidden2, hidden3, output)
    std::list<std::list<std::pair<ACT_FUN, double>>> node_list = {
        {{ACT_FUN::leaky_relu, 0.0}, {ACT_FUN::leaky_relu, 0.0}, {ACT_FUN::leaky_relu, 0.0}},             // Input Layer (3 neurons)
        {{ACT_FUN::relu, 0.0}, {ACT_FUN::leaky_relu, 0.0}, {ACT_FUN::tanh_act, 0.0}, {ACT_FUN::relu, 0.0}}, // Hidden Layer 1 (4 neurons)
        {{ACT_FUN::relu, 0.0}, {ACT_FUN::tanh_act, 0.0}, {ACT_FUN::leaky_relu, 0.0}},                     // Hidden Layer 2 (3 neurons)
        {{ACT_FUN::tanh_act, 0.0}, {ACT_FUN::leaky_relu, 0.0}},                                           // Hidden Layer 3 (2 neurons)
        {{ACT_FUN::leaky_relu, 0.0}, {ACT_FUN::relu, 0.0}, {ACT_FUN::tanh_act, 0.0}}                      // Output Layer (3 neurons)
    };

    _nn.initialize(node_list);
    _nn.set_learning_rate(0.00001); // keep small learning rate

    // Small weight values for Input → Hidden1
    ip_to_nn ip1{0, 0, 0, 0.05, false}; _nn.add(ip1);
    ip_to_nn ip2{0, 1, 0, -0.05, false}; _nn.add(ip2);
    ip_to_nn ip3{0, 2, 0, 0.05, false}; _nn.add(ip3);

    // Hidden1 → Hidden2
    nn_to_nn nn1{1, 0, 0, 2, 0, 0, 0.05, true}; _nn.add(nn1);
    nn_to_nn nn2{1, 1, 0, 2, 1, 0, 0.05, true}; _nn.add(nn2);
    nn_to_nn nn3{1, 2, 0, 2, 2, 0, -0.05, true}; _nn.add(nn3);
    nn_to_nn nn4{1, 3, 0, 2, 1, 0, 0.05, true}; _nn.add(nn4);

    // Hidden2 → Hidden3
    nn_to_nn nn5{2, 0, 0, 3, 0, 0, 0.05, true}; _nn.add(nn5);
    nn_to_nn nn6{2, 0, 0, 3, 1, 0, -0.05, true}; _nn.add(nn6);
    nn_to_nn nn7{2, 1, 0, 3, 0, 0, 0.05, true}; _nn.add(nn7);
    nn_to_nn nn8{2, 1, 0, 3, 1, 0, 0.05, true}; _nn.add(nn8);
    nn_to_nn nn9{2, 2, 0, 3, 0, 0, 0.05, true}; _nn.add(nn9);
    nn_to_nn nn10{2, 2, 0, 3, 1, 0, -0.05, true}; _nn.add(nn10);

    // Hidden3 → Output
    nn_to_nn nn11{3, 0, 0, 4, 0, 0, 0.05, true}; _nn.add(nn11);
    nn_to_nn nn12{3, 0, 0, 4, 1, 0, 0.05, true}; _nn.add(nn12);
    nn_to_nn nn13{3, 0, 0, 4, 2, 0, -0.05, true}; _nn.add(nn13);
    nn_to_nn nn14{3, 1, 0, 4, 0, 0, 0.05, true}; _nn.add(nn14);
    nn_to_nn nn15{3, 1, 0, 4, 1, 0, -0.05, true}; _nn.add(nn15);
    nn_to_nn nn16{3, 1, 0, 4, 2, 0, 0.05, true}; _nn.add(nn16);

    // Output → final outputs
    nn_to_op op1{4, 0, 0, 0.05, false}; _nn.add(op1);
    nn_to_op op2{4, 1, 0, 0.05, false}; _nn.add(op2);
    nn_to_op op3{4, 2, 0, 0.05, false}; _nn.add(op3);
}
};

#endif


#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

#include "global_enum.h"

struct node
{
    double b;

    ACT_FUN f;

    unsigned int l_index;

    unsigned int p_index;

    std::list<double *> w_in;

    std::list<double *> in;

    double out;

    double pre_activation;

    std::list<double *> error;

    std::list<double *> label;

    double delta;

    std::list<std::pair<bool, double>> w_out;
};

struct nn_to_nn
{
    unsigned int from_layer;

    unsigned int from_node;

    unsigned int from_index;

    unsigned int to_layer;

    unsigned int to_node;

    unsigned int to_index;

    double weight;

    bool trainable;
};

struct ip_to_nn
{
    unsigned int to_layer;

    unsigned int to_node;

    unsigned int to_index;

    double weight;

    bool trainable;
};

struct nn_to_op
{
    unsigned int from_layer;

    unsigned int from_node;

    unsigned int from_index;

    double weight;

    bool trainable;
};

#endif
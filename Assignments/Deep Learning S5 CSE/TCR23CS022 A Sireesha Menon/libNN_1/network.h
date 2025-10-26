#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <list>
#include <iostream>
#include <cassert>
#include <utility> // for std::pair

#include "neuron.h"
#include "structures.h" // for node, nn_to_nn, ip_to_nn, nn_to_op

class network : public neuron, public input, public output, public error, public label
{
public:
    std::list<std::list<node>> nodes;

    network() {}

    void initialize(std::list<std::list<std::pair<ACT_FUN, double>>> node_list)
    {
        unsigned int l_index = 0;

        for (auto &layer_nodes : node_list)
        {
            std::list<node> temp_layer;
            unsigned int p_index = 0;

            for (auto &n : layer_nodes)
            {
                node temp_node;
                temp_node.f = n.first;
                temp_node.b = n.second;
                temp_node.l_index = l_index;
                temp_node.p_index = p_index++;
                temp_layer.push_back(temp_node);
            }

            nodes.push_back(temp_layer);
            l_index++;
        }
    }

    void set_learning_rate(double _rate)
    {
        learning_rate = _rate;
    }

    void add(nn_to_nn &nn)
    {
        assert(nn.to_layer < nodes.size());
        assert(nn.from_layer < nodes.size());

        auto it_from_layer = nodes.begin();
        std::advance(it_from_layer, nn.from_layer);
        assert(nn.from_node < it_from_layer->size());
        auto it_from_node = it_from_layer->begin();
        std::advance(it_from_node, nn.from_node);

        auto it_to_layer = nodes.begin();
        std::advance(it_to_layer, nn.to_layer);
        assert(nn.to_node < it_to_layer->size());
        auto it_to_node = it_to_layer->begin();
        std::advance(it_to_node, nn.to_node);

        // Fix: add template arguments to std::pair
        it_from_node->w_out.push_back(std::pair<bool, double>(nn.trainable, nn.weight));

        nn.from_index = it_from_node->w_out.size() - 1;
        it_to_node->w_in.push_back(&(it_from_node->w_out.back().second));
        nn.to_index = it_to_node->w_in.size() - 1;
        it_to_node->in.push_back(&(it_from_node->out));
        it_from_node->error.push_back(&(it_to_node->delta));
        it_from_node->label.push_back(&(it_to_node->out));

        assert(it_from_node->label.size() == it_from_node->error.size());
        assert(it_from_node->w_out.size() == it_from_node->error.size());
        assert(it_to_node->w_in.size() == it_to_node->in.size());
    }

    void add(ip_to_nn &ip)
    {
        assert(ip.to_layer < nodes.size());
        auto it_layer = nodes.begin();
        std::advance(it_layer, ip.to_layer);
        assert(ip.to_node < it_layer->size());
        auto it_node = it_layer->begin();
        std::advance(it_node, ip.to_node);

        double val = 1.0;
        in.push_back(val);
        it_node->in.push_back(&(in.back()));

        // Fix: add template arguments to std::pair
        w_out.push_back(std::pair<bool, double>(ip.trainable, ip.weight));
        it_node->w_in.push_back(&(w_out.back().second));

        ip.to_index = it_node->w_in.size() - 1;
        assert(it_node->w_in.size() == it_node->in.size());
    }

    void add(nn_to_op &op)
    {
        assert(op.from_layer < nodes.size());
        auto it_layer = nodes.begin();
        std::advance(it_layer, op.from_layer);
        assert(op.from_node < it_layer->size());
        auto it_node = it_layer->begin();
        std::advance(it_node, op.from_node);

        out.push_back(&(it_node->out));

        // Fix: add template arguments to std::pair
        it_node->w_out.push_back(std::pair<bool, double>(op.trainable, op.weight));

        double val = 1.0;
        err.push_back(val);
        lbl.push_back(val);

        it_node->error.push_back(&(err.back()));
        it_node->label.push_back(&(lbl.back()));

        op.from_index = it_node->error.size() - 1;
        assert(it_node->error.size() == it_node->w_out.size());
        assert(it_node->error.size() == it_node->label.size());
    }

    // Corrected predict() using node reference
    void predict()
    {
        for (auto &layer : nodes)
        {
            for (auto &n : layer)
            {
                in_forward = true;
                forward(n); // pass node reference
                in_forward = false;
            }
        }
    }

    // Corrected train() using node reference
    void train()
    {
        for (auto l_it = nodes.end(); l_it != nodes.begin();)
        {
            --l_it;
            for (auto &n : *l_it)
            {
                in_backward = true;
                backward(n); // pass node reference
                in_backward = false;
            }
        }
    }

    void print_weight() const
    {
        for (auto &layer : nodes)
        {
            for (auto &n : layer)
            {
                printf("L-ID: %d\t,N-ID:%d\t Bias: [ %f ]\t Delta: [ %f ]", n.l_index, n.p_index, n.b, n.delta);
                printf("]\nIn wights: [");
                for (auto w : n.w_in)
                    printf("%f ", *w);
                printf("]\nOut wights: [");
                for (auto &w : n.w_out)
                    printf("%f ", w.second);
                std::cout << "]" << std::endl;
            }
        }
    }
};

#endif

#ifndef __NEURON_H__
#define __NEURON_H__

#include <string>
#include <list>
#include <numeric>  // For std::inner_product
#include <assert.h>

#include "output.h"
#include "input.h"
#include "error.h"
#include "label.h"
#include "structures.h"
#include "activation.h"
#include "derivative.h"

class neuron : public activation, public derivative
{
public:
    double learning_rate;
    bool in_forward;
    bool in_backward;

    neuron() : learning_rate(0.001), in_forward(false), in_backward(false) {}

    // Forward pass: computes weighted sum + bias, applies activation function
    void forward(std::list<node>::iterator n_id)
    {
        assert(n_id->w_in.size() == n_id->in.size());

        // Weighted sum using inner_product
        double result = std::inner_product(
            n_id->w_in.begin(), n_id->w_in.end(), n_id->in.begin(), 0.0,
            std::plus<>(),
            [](const auto &w, const auto &i) { return (*w) * (*i); }
        );

        n_id->out = function(n_id->f, result + n_id->b);
    }

    // Backward pass: updates weights and biases based on error
    void backward(std::list<node>::iterator n_id)
    {
        assert(n_id->w_out.size() == n_id->error.size());

        double accumulated_error = 0.0;

        auto err_it = n_id->error.begin();
        auto label_it = n_id->label.begin();
        auto weight_it = n_id->w_out.begin();

        while (err_it != n_id->error.end() &&
               label_it != n_id->label.end() &&
               weight_it != n_id->w_out.end())
        {
            if (**err_it != 0.0)
            {
                double safe_label = (**label_it != 0.0) ? **label_it : 1e-6; // avoid division by zero
                double factor = (n_id->out * weight_it->second) / safe_label;

                **err_it = (**label_it > 0.0) ? **err_it * factor : **err_it * (-factor);

                if (weight_it->first && n_id->out != 0.0)
                {
                    weight_it->second += (**err_it * learning_rate / n_id->out);

                    if (weight_it->second != 0.0)
                        accumulated_error += (**err_it / weight_it->second);
                }
                else
                {
                    accumulated_error += **err_it;
                }
            }

            ++err_it;
            ++label_it;
            ++weight_it;
        }

        if (!n_id->w_out.empty())
            accumulated_error /= n_id->w_out.size();

        n_id->b += learning_rate * accumulated_error;
        n_id->delta = accumulated_error;
    }
};

#endif

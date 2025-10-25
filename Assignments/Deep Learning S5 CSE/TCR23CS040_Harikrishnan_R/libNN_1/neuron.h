#ifndef __NEURON_H__
#define __NEURON_H__

#include <string>
#include <list>
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

    neuron()
    {
    }

    void forward(std::list<node>::iterator n_id)
    {
        assert(n_id->w_in.size() == n_id->in.size());

        double result = 0;

        auto it_in = n_id->in.begin();

        auto it_w_in = n_id->w_in.begin();

        while (it_in != n_id->in.end())
        {
            result += (**it_in) * (**it_w_in);

            ++it_in;

            ++it_w_in;
        }

        n_id->pre_activation = result + n_id->b;
        n_id->out = function(n_id->f, n_id->pre_activation);
    }

    void backward(std::list<node>::iterator n_id)
    {
        assert(n_id->w_out.size() == n_id->error.size());

        double acc_err = 0;

        auto e_id = n_id->error.begin();

        auto w_id = n_id->w_out.begin();

        while (e_id != n_id->error.end() && w_id != n_id->w_out.end())
        {
            acc_err += (**e_id) * w_id->second;

            ++e_id;

            ++w_id;
        }

        double activation_grad = gradient(n_id->f, n_id->out);
        n_id->delta = acc_err * activation_grad;

        auto it_in = n_id->in.begin();
        auto it_w_in = n_id->w_in.begin();

        while (it_in != n_id->in.end())
        {
            **it_w_in += learning_rate * n_id->delta * (**it_in);

            ++it_in;

            ++it_w_in;
        }
        n_id->b += learning_rate * n_id->delta;
    }
};

#endif
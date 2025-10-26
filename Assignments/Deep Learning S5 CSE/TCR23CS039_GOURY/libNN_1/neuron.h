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

    neuron() {
        learning_rate = 0.05;  // ✅ Missing semicolon fixed
        in_forward = false;
        in_backward = false;
    }

    void forward(std::list<node>::iterator n_id) 
    {
        assert(n_id->w_in.size() == n_id->in.size());

        double result = 0.0;

        auto it_in = n_id->in.begin(); 
        auto it_w_in = n_id->w_in.begin(); 

        while (it_in != n_id->in.end()) 
        {
            result += (**it_in) * (**it_w_in);
            ++it_in;
            ++it_w_in;
        }

        n_id->out = function(n_id->f, (result + n_id->b));
    }

    void backward(std::list<node>::iterator n_id)
    {
        assert(n_id->w_out.size() == n_id->error.size());

        double acc_err = 0.0;

        auto e_id = n_id->error.begin();
        auto l_id = n_id->label.begin();
        auto w_id = n_id->w_out.begin();

        while (e_id != n_id->error.end() && 
               l_id != n_id->label.end() && 
               w_id != n_id->w_out.end())
        {
            if (**e_id != 0.0)
            {
                // Simplified stable error propagation
                **e_id = **e_id * 1.0;  // placeholder for future scaling

                if (w_id->first)  // trainable weight
                {
                    w_id->second += (**e_id * learning_rate);
                }

                acc_err += **e_id;
            }

            ++e_id;
            ++l_id;
            ++w_id;
        }

        if (!n_id->w_out.empty())
        {
            acc_err /= n_id->w_out.size();
        }

        n_id->b += (learning_rate * acc_err); // update bias
        n_id->delta = acc_err; // store delta
    }
};

#endif

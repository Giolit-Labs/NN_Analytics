#include <chrono>
#include <unistd.h>
#include <list>
#include <iostream>

#include "data_set.h"
#include "training.h"
#include "model.h"

// Define a structure to hold input and label lists
struct Dataset
{
    std::list<double> input;
    std::list<double> label;
};

int main()
{
    data_set dts = data_set();
    model mdl = model();
    mdl.set();

    // Create a list of datasets
    std::list<Dataset> datasets = {
        {{2, 3, 4}, {2, 6, 12}},
        {{6, 7, 8}, {30, 42, 54}} //x^2-x
        // Add more datasets as needed
    };

    double delta = 0.001; // Threshold for the error
    training obj = training();

    // Iterate over each dataset and train the model
    #include <cmath>   // for std::isfinite

for (int i = 0; i < 55; i++) // epochs
{
    for (auto &dataset : datasets)
    {
        bool result = obj.train(mdl._nn, dataset.input, dataset.label, delta);

        // Check if any output value is NaN or Inf
        bool valid_output = true;
        for (double val : dataset.input)
            if (!std::isfinite(val)) valid_output = false;
        for (double val : dataset.label)
            if (!std::isfinite(val)) valid_output = false;

        // Print messages clearly
        if (result && valid_output)
        {
            std::cout << "Training successful" << std::endl;
        }
        else
        {
            std::cout << "Try again" << std::endl;
        }
    }
    std::cout << "In iteration: " << i << std::endl;
}


    return 0;
}
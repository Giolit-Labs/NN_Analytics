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
    /*std::list<Dataset> datasets = {
        {{4, 10, 16}, {22, 28, 34}},
        {{1, 2, 3}, {6, 8, 10}},
        {{5, 7, 9}, {15, 21, 27}}
        // Add more datasets as needed
    };*/
    std::list<Dataset> datasets = {
        {{1, 2, 3}, {2, 5, 10}},
        {{2, 3, 4}, {5, 10, 17}},
        {{3, 4, 5}, {10, 17, 26}},
        {{4, 5, 6}, {17, 26, 37}},
        {{5, 6, 7}, {26, 37, 50}}
        // Add more datasets as needed
    };


    double delta = 0.05; // Threshold for the error
    training obj = training();

    // Iterate over each dataset and train the model
    for(int i=0;i<80;i++){    //epochs
    for (auto &dataset : datasets)
    {
        bool result = obj.train(mdl._nn, dataset.input, dataset.label, delta);

        if (result)
        {
            std::cout << "Training successful" << std::endl;
        }
        else
        {
            std::cout << "Try again" << std::endl;
        }
    }
    std::cout << "in iteration: " << i << std::endl;
}

    return 0;
}
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
    {{2, 4, 6}, {12, 16, 216}},  // input: 2,4,6 -> label: sum of the inputs=12, square of 4=16, cube of 6=216
    {{1, 3, 5}, {9, 9, 125}}, // input : 1,3,5 label: sum of the inputs=9, square of 3=9, cube of 5=125
    {{3, 5, 7}, {15, 25, 343}} // input : 3,5,7 label: sum of the inputs=15, square of 5=25, cube of 7=343
    //f(x1​,x2​,x3​)=[x1​+x2​+x3​, x2^2​, x3^3​]
};


    double delta = 0.01; // Threshold for the error
    training obj = training();

    // Iterate over each dataset and train the model
    for(int i=0;i<50;i++){    //epochs
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
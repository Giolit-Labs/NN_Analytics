#include <chrono>
#include <unistd.h>
#include <list>
#include <iostream>

#include "data_set.h"
#include "training.h"
#include "model.h"

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

   std::list<Dataset> datasets = {
        {{1, 2, 3},  {5.5, 9, 13.5}},   //x^2 + x + 1
        {{2, 3, 4},  {9, 13.5, 19}},
        {{3, 4, 5},  {13.5, 19, 25.5}},
        {{4, 5, 6},  {19, 25.5, 33}},  
    };


    double delta = 0.1;
    training obj = training();

    for (int epoch = 0; epoch < 50; epoch++)
    {
        std::cout << "\n=== Epoch " << epoch << " ===" << std::endl;
        int success_count = 0;

        for (auto &dataset : datasets)
        {
            bool result = obj.train(mdl._nn, dataset.input, dataset.label, delta);

            if (result)
            {
                success_count++;
            }
        }

        std::cout << "Success rate: " << success_count << "/" << datasets.size() << std::endl;
    }

    return 0;
}
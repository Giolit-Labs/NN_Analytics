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
        {{4, 10, 16}, {22, 28, 34}},
        {{1, 2, 3}, {6, 8, 10}},
        {{5, 7, 9}, {15, 21, 27}},
        {{2, 4, 6}, {10, 14, 18}},
        {{3, 5, 7}, {12, 17, 22}},
        {{6, 8, 10}, {18, 24, 30}},
        {{7, 9, 11}, {21, 27, 33}},
        {{0, 1, 2}, {4, 6, 8}},
        {{8, 12, 14}, {26, 34, 40}},
        {{10, 15, 20}, {35, 45, 55}}};

    double delta = 0.5;
    training obj = training();

    for (int epoch = 0; epoch < 10; epoch++)
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
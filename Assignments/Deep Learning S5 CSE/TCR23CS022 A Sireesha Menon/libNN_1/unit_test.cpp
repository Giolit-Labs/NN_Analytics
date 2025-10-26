#include <chrono>
#include <unistd.h>
#include <list>
#include <iostream>
#include <cstdlib>
#include "data_set.h"
#include "training.h"
#include "model.h"

// Structure to hold a dataset
struct Dataset {
    std::list<double> input;
    std::list<double> label;
};

int main() {
    data_set dts;
    model mdl;
    mdl.set();

    double delta = 0.1;   // Error threshold
    int epochs = 60;      // Number of epochs

    // Configurable parameters for dataset generation
    unsigned int dataset_size = 3;   // number of features/labels per sample
    double lower_bound = -100.0;
    double upper_bound = 100.0;
    long max_rand = 1000;

    // Generate 3 datasets with random values
    std::list<Dataset> datasets;
    for (int i = 0; i < 3; i++) {
        Dataset ds;
        ds.input = dts.get_list(dataset_size, lower_bound, upper_bound, max_rand);
        ds.label = dts.get_list(dataset_size, lower_bound, upper_bound, max_rand);
        datasets.push_back(ds);
    }

    training obj;

    // Training loop
    for (int epoch = 0; epoch < epochs; epoch++) {
        std::cout << "Epoch: " << epoch + 1 << std::endl;

        for (auto &ds : datasets) {
            bool result = obj.train(mdl._nn, ds.input, ds.label, delta);

            if (result) {
                std::cout << "Training successful" << std::endl;
            } else {
                std::cout << "Try again" << std::endl;
            }
        }
        std::cout << "--------------------------" << std::endl;
    }

    return 0;
}

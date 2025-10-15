#include <chrono>
#include <unistd.h>
#include <list>
#include <vector>
#include <utility>
#include <cmath>
#include <iostream>

#include "data_set.h"
#include "training.h"
#include "model.h"

int main()
{
    data_set dts = data_set();
    model mdl = model();
    mdl.set();
    double delta = 0.1; // Increased delta for sin(x) training
    training obj = training();

    // Define and initialize your dataset for sin(x) prediction
    // Input: x values (normalized), Output: sin(x) values
    std::vector<std::pair<std::list<double>, std::list<double>>> dataset;
    
    // Generate training data for sin(x) from 0 to 2π
    int num_samples = 20;
    for (int i = 0; i < num_samples; ++i) {
        double x = (2 * M_PI * i) / num_samples; // x from 0 to 2π
        double normalized_x = mdl.normalize_input(x); // Normalize to [0,1]
        double sin_x = sin(x);
        
        dataset.push_back({{normalized_x}, {sin_x}});
    }

    std::cout << "Starting sin(x) training..." << std::endl;
    std::cout << "Training with " << num_samples << " samples from 0 to 2π" << std::endl << std::endl;

    // Loop a large number of times to train on the entire dataset
    for (int epoch = 0; epoch < 5000; ++epoch) {
        double total_error = 0.0;
        int count = 0;
        
        for (auto& data : dataset) {
            bool result = obj.train(mdl._nn, data.first, data.second, delta);
            
            // Calculate error for monitoring
            std::list<double> output = mdl._nn.get_out_put();
            std::list<double> errors = obj.difference(output, data.second);
            for (double error : errors) {
                total_error += fabs(error);
                count++;
            }
            
            // Print progress for first sample of each epoch
            if (epoch % 500 == 0 && &data == &dataset[0]) {
                std::cout << "Epoch " << epoch << " - Sample: x=" << (data.first.front() * 2 * M_PI) 
                          << " (" << (data.first.front() * 2) << "π)" 
                          << ", True sin(x)=" << data.second.front()
                          << ", Predicted=" << output.front()
                          << ", Error=" << errors.front() << std::endl;
            }
        }
        
        // Print average error every 500 epochs
        if (epoch % 500 == 0) {
            std::cout << "Epoch " << epoch << " - Average Error: " << (total_error / count) << std::endl;
            std::cout << "---" << std::endl;
        }
    }
    
    std::cout << "Training completed!" << std::endl << std::endl;

    // Test with new data points after training
    std::cout << "Testing with new data points:" << std::endl;
    std::cout << "==============================" << std::endl;
    
    std::vector<double> test_points = {
        M_PI/6,    // 30° = π/6
        M_PI/4,    // 45° = π/4  
        M_PI/3,    // 60° = π/3
        M_PI/2,    // 90° = π/2
        2*M_PI/3,  // 120° = 2π/3
        3*M_PI/4,  // 135° = 3π/4
        5*M_PI/6,  // 150° = 5π/6
        M_PI,      // 180° = π
        7*M_PI/6,  // 210° = 7π/6
        5*M_PI/4,  // 225° = 5π/4
        4*M_PI/3,  // 240° = 4π/3
        3*M_PI/2,  // 270° = 3π/2
        5*M_PI/3,  // 300° = 5π/3
        7*M_PI/4,  // 315° = 7π/4
        11*M_PI/6  // 330° = 11π/6
    };

    for (double x : test_points) {
        double normalized_x = mdl.normalize_input(x);
        double true_sin = sin(x);
        
        std::list<double> test_input = {normalized_x};
        std::list<double> test_label = {true_sin};

        bool result = obj.train(mdl._nn, test_input, test_label, delta);
        
        std::list<double> output = mdl._nn.get_out_put();
        std::list<double> errors = obj.difference(output, test_label);

        std::cout << "x = " << x << " (" << (x/M_PI) << "π)" << std::endl;
        std::cout << "True sin(x): " << true_sin << std::endl;
        std::cout << "Predicted:   " << output.front() << std::endl;
        std::cout << "Error:       " << errors.front() << std::endl;
        
        if(result) {
            std::cout << "✓ Prediction Successful" << std::endl;
        } else {
            std::cout << "✗ Prediction Needs Improvement" << std::endl;
        }
        std::cout << "---" << std::endl;
    }

    // Interactive testing
    std::cout << std::endl << "Interactive testing:" << std::endl;
    std::cout << "===================" << std::endl;
    std::cout << "Enter x values to predict sin(x) (enter -1 to quit):" << std::endl;
    
    double x;
    while (true) {
        std::cout << "Enter x (0 to 2π): ";
        std::cin >> x;
        
        if (x < 0) {
            std::cout << "Quitting..." << std::endl;
            break;
        }
        
        if (x > 2 * M_PI) {
            std::cout << "Warning: x > 2π, prediction may be less accurate" << std::endl;
        }
        
        double normalized_x = mdl.normalize_input(x);
        std::list<double> test_input = {normalized_x};
        std::list<double> test_label = {sin(x)}; // For error calculation
        
        obj.train(mdl._nn, test_input, test_label, delta);
        std::list<double> output = mdl._nn.get_out_put();
        std::list<double> errors = obj.difference(output, test_label);
        
        std::cout << "sin(" << x << ") = " << output.front() << std::endl;
        std::cout << "True value: " << test_label.front() << std::endl;
        std::cout << "Error: " << errors.front() << std::endl << std::endl;
    }

    return 0;
}
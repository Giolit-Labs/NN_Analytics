NN_Analytics - Modified Version

This repository contains a modified version of the NN_Analytics neural network project. The original code has been updated for improved compilation compatibility, enhanced clarity, and minor structural corrections.

Overview

NN_Analytics is a C++ implementation of a simple feedforward neural network that supports:

Multiple layers and nodes

Custom activation functions

Forward and backward propagation

Training using delta-based error threshold

Changes Made

The following updates have been made to the original repository:

 1.Activation Function Updates
    1.The ACT_FUN enum was updated to avoid conflicts with standard math functions in C++.
    2.The activation class was updated to use a properly named function for the hyperbolic tangent
2.Dataset Randomization
      Replaced random() with rand() in data_set.h for portability across compilers.

3.Network Forward/Backward Functions
      Updated network::predict() and network::train() to correctly pass node references to the forward() and backward() functions.
4.Unit Test
       The unit_test.cpp file allows testing of the neural network with multiple datasets. The structure has been modified to make it easier to:
        1.Change dataset values
        2.Adjust delta threshold
        3.Control the number of epochs
    

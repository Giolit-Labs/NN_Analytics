## Changes Made

1. **Activation Functions:**

   * Redefined activation functions in `activation.h` and included `<cmath>` for proper mathematical functions..
   * changed tanh function name into tanh_fun.

2. **Dataset Update:**

   * Updated dataset in `unit_test.cpp` to train on a new function: 2x + 1 instead of previous arithmetic sequences.
  
 ```cpp std::list<Dataset> datasets = { {{1, 2, 3}, {3, 5, 7}}, {{10, 11, 12}, {21, 23, 25}}, {{5, 6, 7}, {11, 13, 15}} }; ``` 


3. **Delta (Error Threshold):**

   * Initially increased delta to observe faster learning.
   * Current threshold set to `0.005`.
   * Observation: Higher delta allows faster learning but may reduce final accuracy.
   * Low delta with more epochs is expected to improve accuracy but slows down learning.
   * double delta = 0.005; // Threshold for the error


4. **Epochs:**

   * Initially decreased number of epochs to test fast learning.
   * Current number of epochs set to `50`.
   * Observation: Fewer epochs and high delta → faster learning and more successful updates.

5. **Learning Rate:**

   * Current learning rate set to `0.0001`.
   * Observation: Allows stable training with faster convergence.

6. **Random Function Update:**

   * Replaced `random` with `rand()` in the code for generating random values.


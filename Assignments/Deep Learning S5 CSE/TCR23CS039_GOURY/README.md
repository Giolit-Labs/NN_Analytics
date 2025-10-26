# Deep Learning Neural Network - C++ (Assignment)

**Project Overview:**  
Simple feedforward neural network implemented in C++ with customizable activation functions and manual training loop. Only tested on small datasets.

---

## Key Updates

1. **Training Dataset**
   - Added zero and negative values.
   - Expanded dataset for better generalization.
   - Error threshold (`delta`) reduced to `0.001`.

2. **Activation Functions**
   - Implemented: Sigmoid, ReLU, Leaky ReLU (with alpha), Tanh.
   - Fixed `tanh` naming conflict with standard library (`tanh_act`).

3. **Derivative Functions**
   - Correct derivatives for Sigmoid, ReLU, Leaky ReLU.
   - Matches updated activation functions.

4. **Neuron & Network**
   - Simplified forward/backward propagation.
   - Default learning rate set to `0.05`.
   - Fixed weight update logic and connection references.

5. **Dataset & Training**
   - `rand()` used instead of `random()` for compatibility.
   - Training loop continues until output converges to labels or maximum steps reached.

---

**Build & Run:**

```bash
g++ -std=c++11 unit-test.cpp -o neural_network
./neural_network


# Changes I have made to the model

Changes made in activation.h

## 1. Added cmath include

Why:
The math functions exp() and tanh() come from the C++ cmath library. Without this include, the compiler will throw an “undefined function” error.

🔧 2. Gave correct mathematical implementations

Your original activation functions returned x directly — they were placeholders.
I replaced them with actual activation function formulas:

**sigmoid**
double sigmoid(double x) {
    return 1.0 / (1.0 + std::exp(-x));
 }
  Implements the logistic sigmoid fu

 **leaky_relu**
'return (x > 0.0) ? x : 0.01 * x;'
Adds small slope for negatives (prevents dead neurons)

**tanh**
 `return std::tanh(x);` : Uses built-in hyperbolic tangent

🔧 3. Renamed tanh method to tanh_act

Change:

double tanh_act(double x) { return std::tanh(x); }

Why:
tanh is also a function in cmath
Using the same name for your method can confuse the compiler or shadow the standard function, so renaming prevents conflicts.

🔧 4. Marked activation functions as private

Change:

private:
    double sigmoid(double x);
    double relu(double x);
    double leaky_relu(double x);
    double tanh_act(double x);

Why:
These helper functions are only meant to be used internally via function(), not called directly by other classes — so private access is cleaner and safer.

### Changes Made to `data_set` Class

1. **Removed `max_rand` and `seed` arguments**  
   - Original code used `std::srand(seed)` and `random() % max_rand`, which:
     - Re-seeded the RNG every time → poor randomness.
     - Introduced bias because of modulo.
   - New code uses `std::mt19937` and `std::uniform_real_distribution`, which generates high-quality random doubles directly.

2. **Replaced `random()` with `<random>` library**
   - `<random>` is standard, portable, and modern C++.
   - `std::mt19937` (Mersenne Twister) gives better randomness than `rand()` or `random()`.

3. **Removed time-based seeding in `get_list()`**
   - Original code used elapsed nanoseconds as seed → non-random patterns and inefficient.
   - New code generates each number without reseeding.

4. **Removed unnecessary includes**
   - `<iostream>` was unused.
   - Added `<random>` for the new RNG.

5. **Simplified `get_val()`**
   - Now takes only `lower_bound` and `upper_bound`.
   - Returns a `double` in the correct range without extra calculations.

6. **Simplified `get_list()`**
   - Loops through `size` and calls `get_val()` for each value.
   - Returns a `std::list<double>` without time calculations or seeds.

7. **Modern C++ style**
   - `data_set() = default;` for the default constructor.
   - Static RNG to avoid repeated construction of `std::mt19937` and `std::random_device`.

---

## Changes Made in `derivative` Class

```cpp
1. Added `<cmath>` include
#include <cmath>  // Needed for std::tanh

2. Renamed tanh function to avoid conflict
// Old: double tanh(double x)
// New:
double tanh_derivative(double x) {
    double t = std::tanh(x);
    return 1.0 - t * t;  // Correct derivative of tanh
}

3. Corrected sigmoid derivative
// Old: return x * (1 - x); // only valid if x = sigmoid(x)
// New (if x is raw input):
double sigmoid(double x) {
    double s = 1.0 / (1.0 + std::exp(-x));
    return s * (1.0 - s);
}
// OR keep old if x is already sigmoid output

4. Fixed leaky ReLU derivative
// Old: return (0.01 * x);
// New:
double leaky_relu(double x) {
    return (x > 0.0) ? 1.0 : 0.01; // constant slope for negative input
}

5. Ensured relu derivative is correct
// Already correct:
double relu(double x) {
    return (x > 0.0) ? 1.0 : 0.0;
}

6. Made all helper functions private
// Only the public function 'loss()' is exposed:
private:
    double sigmoid(double x);
    double relu(double x);
    double leaky_relu(double x);
    double tanh_derivative(double x);

7. Updated loss() to call the corrected private functions
double loss(ACT_FUN id, double x) {
    switch(id) {
        case ACT_FUN::sigmoid: return sigmoid(x);
        case ACT_FUN::relu: return relu(x);
        case ACT_FUN::tanh: return tanh_derivative(x);
        case ACT_FUN::leaky_relu: return leaky_relu(x);
        default: return 1.0;
    }
}

##Changes in model class


1. Increased network layers from 3 → 5:
   - Input Layer: 3 neurons
   - Hidden Layer 1: 4 neurons
   - Hidden Layer 2: 3 neurons
   - Hidden Layer 3: 2 neurons
   - Output Layer: 3 neurons

2. Mixed activation functions across layers:
   - relu, leaky_relu, tanh_act

3. Varied weights for connections (positive/negative) for more randomness.

4. Partial and full connections between neurons:
   - Some layers are fully connected, others partially connected to introduce variety.

5. Slightly increased learning rate for faster convergence.

##Changes in neuron class

1. Initialized learning_rate and flags in constructor:
   - learning_rate = 0.001
   - in_forward = false
   - in_backward = false

2. Optimized forward() using std::inner_product for clarity and efficiency.

3. Added safety in backward() to avoid division by zero with labels:
   - double safe_label = (**label_it != 0.0) ? **label_it : 1e-6;

4. Improved readability in backward():
   - Renamed iterators to descriptive names (err_it, label_it, weight_it)
   - Organized weight updates and error accumulation more clearly

5. Overall, backward() now handles weight and bias updates safely and clearly.


##Changes in training class:

1. Optimized is_close() using std::abs for clarity.
2. Optimized difference() function for readability.
3. Optional: Added verbose flag in train() to control printing of inputs, outputs, and errors.
4. Ensured compatibility with updated neuron class:
   - Forward and backward methods now handle all neurons correctly.
   - Learning rate can be set for all neurons before training if needed.
5. Added safety checks in training loops (max steps) to prevent infinite loops.

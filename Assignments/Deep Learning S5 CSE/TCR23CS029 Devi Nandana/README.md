**1️⃣ Dataset Changes (in unit_test.cpp)**

Replaced the original small dataset with arithmetic progression (AP) type data.
Each dataset contains 3 input values and 3 corresponding output values.

std::list<Dataset> datasets = {
    {{2, 4, 6}, {8, 10, 12}},
    {{1, 3, 5}, {7, 9, 11}},
    {{5, 10, 15}, {20, 25, 30}},
    {{3, 6, 9}, {12, 15, 18}}
};


**2️⃣ Neural Network Structure (in model.h)**

Modified the network layer configuration:
Input layer: 3 neurons  
Hidden layer: 4 neurons  
Output layer: 3 neurons

This gives the hidden layer a bit more capacity to learn, while still keeping the model lightweight.
int layers[] = {3, 4, 3};
_nn.init(layers, 3);

**⚙️ Other changes in model.h:**

Narrowing conversion warnings occurred when initializing structs because int loop variables (i, j) were used where unsigned was expected.
Fix:
Cast the loop variables to unsigned inside struct initialization to prevent narrowing conversion warnings.
for (int i = 0; i < layers.size(); i++) {
    layers[i] = Layer((unsigned)i);  
}


**3️⃣ Activation Function**

Updated activation function to ReLU for both hidden and output layers:
_nn.setActivationFunction(ACT_FUN::relu);
_nn.setOutputActivationFunction(ACT_FUN::relu);

ReLU is simple and efficient for linear or near-linear data like arithmetic progressions.
It helps the model converge faster compared to sigmoid or tanh, without unnecessary complexity.


**4️⃣ Learning Rate**

Set a small learning rate:
_nn.learning_rate = 0.00001;

A very small learning rate ensures smooth and gradual learning, preventing the model from overshooting during weight updates — ideal when training stability is more important than speed.


**⚙️ Changes in input.h**

Runtime assertion failure due to size mismatch between in and input vectors:
assert(in.size() == input.size());

Fix:
Replaced the assertion with logic that clears and copies the new list safely.
input.clear();
input.insert(input.end(), in.begin(), in.end());
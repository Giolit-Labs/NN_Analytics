# Neural Network Implementation

## Changes

---

### 1. Added pre_activation field to node struct

```cpp
struct node
{
    double b;
    ACT_FUN f;
    unsigned int l_index;
    unsigned int p_index;
    std::list<double *> w_in;
    std::list<double *> in;
    double out;
    double pre_activation;
    std::list<double *> error;
    std::list<double *> label;
    double delta;
    std::list<std::pair<bool, double>> w_out;
};
```

### 2. Fixed implementation of activation functions and their derivatives including ReLU, sigmoid and Leaky ReLU

**Changes**:

```cpp
double sigmoid(double x)
    {
        return (1 / (1 + exp(-x)));
    }

    double relu(double x)
    {
        if (x > 0.0)
        {
            return x;
        }
        return 0;
    }

    double leaky_relu(double x)
    {
        if (x > 0.0)
        {
            return x;
        }
        return (0.01 * x);
    }
```

### 3. Rewrote backprop function to be less complicated

```cpp
void backward(std::list<node>::iterator n_id)
{
    assert(n_id->w_out.size() == n_id->error.size());

    // Step 1: Accumulate error from downstream neurons
    double acc_err = 0;
    auto e_id = n_id->error.begin();
    auto w_id = n_id->w_out.begin();

    while (e_id != n_id->error.end() && w_id != n_id->w_out.end())
    {
        acc_err += (**e_id) * w_id->second;
        ++e_id;
        ++w_id;
    }

    // Step 2: Apply activation function derivative
    double activation_grad = gradient(n_id->f, n_id->out);
    n_id->delta = acc_err * activation_grad;

    // Step 3: Update weights using gradient descent
    auto it_in = n_id->in.begin();
    auto it_w_in = n_id->w_in.begin();

    while (it_in != n_id->in.end())
    {
        **it_w_in += learning_rate * n_id->delta * (**it_in);
        ++it_in;
        ++it_w_in;
    }

    // Step 4: Update bias
    n_id->b += learning_rate * n_id->delta;
}
```

### 6. Hyperparameter Tuning

- Learning rate was too small
- Initial weights were too large (`0.5` to `4.0`)
- Biases were initialized to large random values

### 7. Added to Dataset

Added new datapoints to the dataset which previously had only 3 points which was insufficient for good generalization.

**General Pattern**:

```
output[0] = 2 × input[0] + input[1] + 2
output[1] = 2 × input[1] + input[2] + 2
output[2] = 2 × input[2] + input[0] + 2
```

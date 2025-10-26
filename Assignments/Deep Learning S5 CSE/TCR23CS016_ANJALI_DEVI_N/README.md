*Defined activation functions in activation.h and derivative.h instead of returning just x.
*Activation function tanh is renamed as tanh_act due to name confilct with the built in function tanh() in <cmath>.

🔧 Code Modifications:

• Modified dataset values to follow the function y = x² − x
        The dataset was updated to represent a quadratic relationship rather than a linear or arbitrary set of values.

• Adjusted delta value to 0.001
        The delta (learning rate or small adjustment factor) was reduced to 0.001.

• Changed number of epochs to 55
        The total training iterations were raised to 55 epochs to give the network additional time to learn from the data.

• Updated weight initialization in model.h
        The initial weights in the model were manually fine-tuned to enhance convergence speed and avoid unstable updates.

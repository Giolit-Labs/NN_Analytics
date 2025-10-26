Updates
✅ Dataset
   updated dataset to 
   f(x1​,x2​,x3​)=[x1​+x2​+x3​, x2^2​, x3^3​]  instead of the previous arithmetic sequence.

   std::list<Dataset> datasets = {
    {{2, 4, 6}, {12, 16, 216}},  // input: 2,4,6 -> label: sum of the inputs=12, square of 4=16, cube of 6=216
    {{1, 3, 5}, {9, 9, 125}}, // input : 1,3,5 label: sum of the inputs=9, square of 3=9, cube of 5=125
    {{3, 5, 7}, {15, 25, 343}} // input : 3,5,7 label: sum of the inputs=15, square of 5=25, cube of 7=343
    //f(x1​,x2​,x3​)=[x1​+x2​+x3​, x2^2​, x3^3​]
};

✅ Delta value
   delta is updated to 0.01
   Training now continues until output matches label within ±0.01 tolerance

   double delta = 0.01; // Threshold for the error

✅ Epochs/iterations
   changed the number of epochs to 50

   for(int i=0;i<50;i++)   //epochs

✅ Learning Rate
   Learning rate decreased for finer gradient updates and smoother convergence.
   current value is 0.00001

   _nn.set_learning_rate(0.00001);

✅ Random Number Generation Fix

Replaced the non-standard C function random() with rand() for generating random values.

This resolved the error:
'random' was not declared in this scope


✅ Pair Object Construction Fix

Replaced incorrect use of std::pair(...) with std::make_pair(...) for automatic type deduction.   

✅ All neurons use Leaky ReLU activation.    
      

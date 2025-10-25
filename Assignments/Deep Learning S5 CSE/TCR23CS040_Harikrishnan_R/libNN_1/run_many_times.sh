#/bin/bash

a=0

# lt is less than operator

#Iterate the loop until a less than 10

while [ $a -lt 10 ]
do

# Print the values
g++ unit_test.cpp -o unit_test && ./unit_test

echo $a
# increment the value
a=`expr $a + 1`
done


#include <iostream>
#include <vector>
#include <random>
#include "gmll.h"

int main() {
    // std::vector<size_t> shape = {2, 3, 4};
    // Tensor<float> tensor(shape);
    // // fill the tensor with random values
    // std::random_device rd;
    // std::mt19937 gen(rd());
    // std::uniform_real_distribution<float> dis(0.0, 1.0);

    // for (size_t k = 0; k < shape[2]; k++) {
    //     for (size_t i = 0; i < shape[0]; i++) {
    //         for (size_t j = 0; j < shape[1]; j++) {
    //             tensor(i, j, k) = dis(gen);
    //         }
    //     }
    // }
    // tensor.print();

    Tensor<float> input = *(new Tensor<float> ({5,2,1}));
    Tensor<float> target = *(new Tensor<float> ({5,1,1}));

    input(0,0,0) = 2;
    input(0,1,0) = 5;
    target(0,0,0) = 1;
    input(1,0,0) = -11;
    input(1,1,0) = -6;
    target(1,0,0) = 1;
    input(2,0,0) = -2;
    input(2,1,0) = 3;
    target(2,0,0) = 0;
    input(3,0,0) = 7;
    input(3,1,0) = -9;
    target(3,0,0) = 0;
    input(4,0,0) = 17;
    input(4,1,0) = 20;
    target(4,0,0) = 1;
    // input(5,0,0) = 63;
    // input(5,1,0) = 23;
    // target(5,0,0) = 1;
    // input(6,0,0) = -22;
    // input(6,1,0) = -20;
    // target(6,0,0) = 1;
    // input(7,0,0) = 4;
    // input(7,1,0) = -65;
    // target(7,0,0) = 0;
    // input(8,0,0) = -32;
    // input(8,1,0) = 9;
    // target(8,0,0) = 0;
    // input(9,0,0) = -48;
    // input(9,1,0) = 2;
    // target(9,0,0) = 0;
    // input(10,0,0) = 10;
    // input(10,1,0) = 83;
    // target(10,0,0) = 1;
    

    Model<float> model = *(new Model<float>());
    model.add_layer(new Dense<float> (2, 2, "sigmoid"));
    model.add_layer(new Dense<float> (2, 1, "sigmoid"));
    

    model.compile("MeanSquaredError");
    
    model.fit(input, target, 5, 100, 0.0001);


    return 0;
}

#include <bits/stdc++.h>
#include "tensor.h"

using namespace std;

int main() {
	Tensor<float> x({2,2,1});
	x(0,0,0) = 1;
	x(0,1,0) = 1;
	x(1,1,0) = 1;
	x(1,0,0) = 1;
	

	Tensor<float> y;
	y = x *x;
	Tensor<float> z;
	z = x*x +y;
	// z+=y;

	z.print();

	return 0;
}
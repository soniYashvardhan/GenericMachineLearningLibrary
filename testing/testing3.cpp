// // // // #include <iostream>
// // // // #include <vector>
// // // // class A
// // // // {
// // // // public:
// // // // 	int mx;
// // // // 	double my;
// // // // };
// // // // class B
// // // // {
// // // // public:
// // // // 	B(int x, double y) : mx{ x }, my{ y } {}
// // // // 	int mx;
// // // // 	double my;
// // // // };

// // // // class C
// // // // {
// // // // public:
// // // // 	C(int x, double y) : mx{ x }, my{ y } {}
// // // // 	C(const std::initializer_list<int>& v) {
// // // // 		mx = *(v.begin());
// // // // 		my = *(v.begin() + 1);
// // // // 	}

// // // // 	int mx;
// // // // 	double my;
// // // // };

// // // // int main()
// // // // {
// // // // 	// Aggregate initialization
// // // // 	A a{ 1, 3.7 };
// // // // 	// Regular constructor
// // // // 	B b{ 2, 9.8 };

// // // // 	// Initializer_list
// // // // 	C c{ 3, 7 };

// // // // 	std::cout << a.mx << " " << a.my << std::endl;
// // // // 	std::cout << b.mx << " " << b.my << std::endl;
// // // // 	std::cout << c.mx << " " << c.my << std::endl;

// // // // 	return 0;
// // // // }


// // // #include <bits/stdc++.h>
// // // using namespace std;

// // // // Time Class
// // // class Time {
// // // 	int hour;
// // // 	int mins;

// // // public:
// // // 	// Default Constructor
// // // 	Time()
// // // 	{
// // // 		hour = 0;
// // // 		mins = 0;
// // // 	}

// // // 	// Parameterized Constructor
// // // 	Time(int t)
// // // 	{
// // // 		hour = t / 60;
// // // 		mins = t % 60;
// // // 	}

// // // 	// Function to print the value
// // // 	// of class variables
// // // 	void Display()
// // // 	{
// // // 		cout << "Time = " << hour
// // // 			<< " hrs and "
// // // 			<< mins << " mins\n";
// // // 	}
// // // };

// // // // Driver Code
// // // int main()
// // // {
// // // 	// Object of Time class
// // // 	Time T1;
// // // 	float dur = 95;

// // // 	// Conversion of int type to
// // // 	// class type
// // // 	T1 = dur;
// // // 	T1.Display();

// // // 	return 0;
// // // }


// // template <typename T, int N>
// // class Array{
// // public:
// //  int getSize() const{
// //  return N;
// //  }
// // private:
// //  T elem[N];
// // };
// // int main() {
// // int x{5};
// //  const int y{5};
// //  Array<int, 5> myArr1; // (1)
// //  Array<int, 10> myArr2; // (2)
// //  Array<int, 5> myArr3; // (3)
// //  Array<int, x> myArr4;// (4)
// //  Array<int,y > myArry5; // (5)
// // }
// #include <bits/stdc++.h>
// using namespace std;

// template <typename T, int size>
// void print_array(T (&arr)[size]) {
// for (int i = 0; i < size; i++) {
// 	 std::cout << arr[i] << " ";
//  }
//  std::cout << std::endl;
// }

// int main() {
//     int arr[] = {1, 2, 3, 4, 5};
//     print_array(arr);
//     double arr2[] = {1.1, 2.2, 3.3};
//     print_array<double,3>(arr2);
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;

#define pow(x,y) x*pow(x,y-1)

int main() {
	int v = pow(5,2);
	cout<<v<<endl;

	return 0;
}
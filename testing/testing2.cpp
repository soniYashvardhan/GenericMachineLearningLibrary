#include <bits/stdc++.h>
#include <assert.h>
using namespace std;

template <typename T>
class A {
	public:
	virtual void forward(T x) = 0;
	virtual ~A() {}
};

template <typename T>
class B: public A<T> {
	public:
	B(size_t x) {
		cout<<"hello"<<endl;
		int this->y = 5;
	}

	void forward(T x) override {
		cout<<x<<endl;
	}
};

int main() {
	B<float> temp(3);

	return 0;
}
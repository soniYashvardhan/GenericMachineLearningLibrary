#include <bits/stdc++.h>

using namespace std;

class base1 {
	public:
	virtual void func() = 0;
};

class base3: public base1 {
	public:
	base3() {
		x=10;
	}
	void func() {
		cout<<"Hello "<<x<<endl;
	}
	private:
	int x;
};

void funct(base1* ptr) {
	ptr->func();
}

int main() {
	base3 x;
	funct(&x);

	return 0;
}
#include <iostream>
using namespace std;

//int main() {
//	double d = 12.34;
//	int a = static_cast<int>(d);
//	cout << a << endl;
//
//	return 0;
//}
//
//int main() {
//	volatile const int a = 2;
//	int* p = const_cast<int*>(&a);
//	*p = 3;
//	cout << a << endl;
//	cout << *p << endl;
//	return 0;
//}

class A1 {
public:
	virtual void f() {}
public:
	int _a1 = 0;
};

class A2 {
public:
	virtual void f() {}
public:
	int _a2 = 0;
};

class B : public A1, public A2 {
public:
	int _b = 1;
};

int main() {
	B bb;
	A1* ptr1 = &bb;
	A2* ptr2 = &bb;
	cout << ptr1 << endl;
	cout << ptr2 << endl;

	B* pb1 = (B*)ptr1;
	B* pb2 = (B*)ptr2;
	cout << pb1 << endl;
	cout << pb2 << endl;
	
	B* pb3 = dynamic_cast<B*>(ptr1);
	B* pb4 = dynamic_cast<B*>(ptr2);
	cout << pb3 << endl;
	cout << pb4 << endl;
	return 0;
}
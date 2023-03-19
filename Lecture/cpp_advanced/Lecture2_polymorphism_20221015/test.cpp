#include <iostream>
using namespace std;

//class Person
//{
//public:
//	virtual void BuyTicket()
//	{
//		cout << "full-price" << endl;
//	}
//};
//
//class Student : public Person
//{
//public:
//	// 虚函数重写/覆盖，要求函数三同：函数名、参数和返回值相同
//	// 不符合重写就是隐藏关系
//	virtual void BuyTicket()
//	{
//		cout << "half-price" << endl;
//	}
//};
//
//class Soldier : public Person
//{
//public:
//	virtual void BuyTicket()
//	{
//		cout << "No-line" << endl;
//	}
//};
//
//void Func(Person& p) // 父类的指针或者引用来调用虚函数
//{
//	p.BuyTicket();
//}
//
//int main()
//{
//	Person ps;
//	Student st;
//	Soldier sd;
//	Func(ps);
//	Func(st);
//	Func(sd);
//	return 0;
//}

//class Person
//{
//public:
//	virtual Person* BuyTicket()
//	{
//		cout << "full-price" << endl;
//		return this;
//	}
//};
//
//class Student : public Person
//{
//public:
//	// 虚函数重写/覆盖，要求函数三同：函数名、参数和返回值相同
//	// 不符合重写就是隐藏关系
//	virtual Student* BuyTicket()
//	{
//		cout << "half-price" << endl;
//		return this;
//	}
//};
//
//void Func(Person& p) // 父类的指针或者引用来调用虚函数
//{
//	p.BuyTicket();
//}
//
//int main()
//{
//	Person ps;
//	Student st;
//	Func(ps);
//	Func(st);
//	return 0;
//}

//class A
//{
//public:
//	virtual void func(int val = 1) { std::cout << "A->" << val << std::endl; }
//	virtual void test() { func(); } 
//	// A类里的普通函数test()而言，它的第一个默认参数永远是A *this，因此构成了函数重载
//};
//class B : public A
//{
//public:
//	void func(int val = 0) { std::cout << "B->" << val << std::endl; } 
// // 缺省值没有效果，这是因为重写是进行接口继承，用的是父类的接口
//};
//int main(int argc, char* argv[])
//{
//	A* pa_B = new B;
//	B* pb_B = new B; // 调用 this->test()，该this指针是A，形成切片
//	A* pa_A = new A;
//	//B* pb_A = new A; // 父类不能给子类切片
//	pa_B->test();
//	pb_B->test();
//	pa_A->test();
//	//pb_A->test();
//	return 0;
//}

//class A
//{
//	virtual void Func1();
//	virtual void Func2();
//	void Func3();
//	void Func4();
//	int _b;
//};
//
//int main()
//{
//	cout << sizeof(A) << endl;
//}

//class Base {
//public:
//	virtual void Func1() { cout << "Func1-Base" << endl; }
//	virtual void Func2() { cout << "Func2" << endl; }
//	void Func3() { cout << "Func3" << endl; }
//protected:
//	int _age = 1;
//};
//class Derived : public Base {
//public:
//	virtual void Func1() 
//	{ cout << "Func1-Derived" << endl; }
//protected:
//	int _num = 2;
//};
//
//void Test(Base& b)
//{
//	b.Func1();
//}
//
//int main()
//{
//	Base b;
//	Test(b);
//	b.Func3();
//
//	Derived d;
//	Test(d);
//
//	return 0;
//}


//class Car
//{
//public:
//	virtual void Drive() = 0;
//};
//class Benz :public Car
//{
//public:
//	virtual void Drive()
//	{
//		cout << "Benz-舒适" << endl;
//	}
//};
//class BMW :public Car
//{
//public:
//	virtual void Drive()
//	{
//		cout << "BMW-操控" << endl;
//	}
//};
//void Test()
//{
//	//Car c;
//	Car* pBenz = new Benz;
//	pBenz->Drive();
//	Car* pBMW = new BMW;
//	pBMW->Drive();
//}


//class Person
//{
//public:
//	virtual void BuyTicket() { cout << "Full-price for Person" << endl; }
//	virtual void Func1() { cout << "Func1()" << endl; }
//};
//
//class Student : public Person
//{
//public:
//	virtual void BuyTicket() { cout << "Half-price for Student" << endl; }
//	virtual int Func2() { cout << "Func2()" << endl; return 0; }
//};

typedef void(*VFPTR)(); // 因为上面的成员函数都是空函数指针，所以对空函数指针重定义
// 即使虚函数的返回类型不是void，或者有其他参数（这种情况下VS2019也会报错），它的函数指针也会被强转为空函数指针

void PrintVFTable(VFPTR table[])
{
	 for (size_t i = 0; table[i] != nullptr; i++) // VS中虚表以nullptr结尾，而Linux没有这个设计
//	for (size_t i = 0; i < 3; i++) // VS中虚表以nullptr结尾，而Linux没有这个设计
	 {
		 printf("第%d个虚表函数指针 vft[%d]: %p ", i + 1, i, table[i]);
		 //table[i]();
		 VFPTR pf = table[i];
		 pf();
	 }
}

//int main()
//{
//	// 同一个类型的对象共用一个虚表
//	Person p1;
//	Person p2;
//	// VS下，不管是 否完成重写，子类虚表跟父类虚表都不是同一个
//	Student s1;
//	Student s2;
//
//	PrintVFTable((VFPTR*)(*(int*)(&s1))); // 对于32位系统，虚表是前4个字节地址强转为int*，64位则强转为 long long*
//	// 取s1地址 -> 强转为 int*，目的是为了取放在s1地址最前面的虚表地址
//	// -> 因为虚表里存的是一个函数指针的数组的地址，所以对它再解引用就得到了该函数指针数组的地址
//	// -> 然后因为对int*指针解引用后得到是int类型，需要强转为空指针类型给PrintVFTable
//	return 0;
//}


// 多继承

void test() {}

class Base1 {
public:
	virtual void func1() { cout << "Base1::func1" << endl; }
	virtual void func2() { cout << "Base1::func2" << endl; }
private:
	int b1 = 1;
};

class Base2 {
public:
	virtual void func1() { cout << "Base2::func1" << endl; }
	virtual void func2() { cout << "Base2::func2" << endl; }
private:
	int b2 = 2;
};

class Derive : public Base1, public Base2 {
public:
	// 重写了func1，没有重写func2，有一个独立的虚函数func3
	virtual void func1() { cout << "Derive::func1" << endl; }
	virtual void func3() { cout << "Derive::func3" << endl; }
private:
	int d = 3;
};

int main()
{
	Base1 b1;
	Base2 b2;
	Derive d;
	PrintVFTable((VFPTR*)*(int*)&d);
	cout << endl;
	PrintVFTable((VFPTR*)*(int*)((char*)&d+sizeof(Base1)));

	//// 利用切片
	//Base2* ptr = &d;
	//PrintVFTable((VFPTR*)(*(int*)(ptr)));	

	cout << endl;
//	cout << test << endl; // 普通函数的名字就是其地址

	//cout << &Derive::func3 << endl; // 语法规定取成员函数的地址时要用&

	printf("%p\n", &Derive::func1);

	d.func1();

	Base1* ptr1 = &d;
	ptr1->func1();

	Base2* ptr2 = &d;
	ptr2->func1();

	return 0;
}






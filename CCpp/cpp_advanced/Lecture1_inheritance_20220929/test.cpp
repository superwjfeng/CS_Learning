#include <iostream>
using namespace std;

//class Person
//{
//protected:
//	string _name = "wjf";
//	int _num = 111;
//};
//
//class Student : public Person
//{
//public:
//	void Print()
//	{
//		cout << "Name: " << _name << endl;
//		cout << "stuID: " << _num << endl;
//		cout << "ID: " << Person::_num << endl;
//	}
//protected:
//	int _num = 999;
//};

//class Person
//{
//protected:
//	string _name;
//	string _sex;
//	int _age;
//};
//
//class Student : public Person
//{
//public:
//	int _No;
//};
//
//int main()
//{
//	Student sobj;
//	// 子类对象可以赋值给父类对象/指针/引用
//	// 这里虽然是不同类型，但是不是隐式类型转换
//	// 从引用不需要加const来保证常性就可以看出来
//	// 这里是一个语法天然支持的特殊支持
//	Person pobj = sobj;
//	Person* pp = &sobj;
//	Person& rp = sobj;
//	return 0;
//}

//class Student;
//class Person
//{
//public:
//	friend void Display(const Person& p, const Student& s);
//	//Person(const char* name = "peter")
//	Person(const char* name)
//		:_name(name)
//	{
//		cout << "Person()" << endl;
//	}
//	Person(const Person& p)
//		: _name(p._name)
//	{
//		cout << "Person(const Person& p)" << endl;
//	}
//	~Person()
//	{
//		cout << "~Person()" << endl;
//	}
//	Person& operator=(const Person& p)
//	{
//		cout << "Person & operator=(const Person & p)" << endl;
//		if (this != &p)
//			_name = p._name;
//		return *this;
//	}
//protected:
//	string _name;
//	string _sex;
//	int _age;
//};
//
//class Student : public Person
//{
//public:
//	friend void Display(const Person& p, const Student& s);
//	Student(const char* name, int num)
//		:Person(name) // 整个父类的构造函数，不能给单独一个父类成员
//		, _num(num)
//	{}
//
//	Student(const Student& s) // 子类显式的拷贝构造
//		:Person(s) // 赋值转换切片
//		, _num(s._num)
//	{}
//
//	Student& operator=(const Student& s)
//	{
//		if (this != &s)
//		{
//			Person::operator=(s); // 显式调用父类的operator=
//			_num = s._num;
//		}
//		return *this;
//	}
//
//	// 子类的析构函数跟父类的析构函数构成隐藏 
//	~Student()
//	{
//		////父类的析构函数不应该显式调用，因为他会自动调用
//		//Person::~Person();
//		cout << "~Student()" << endl;
//		// ...
//	}
//
//	//Student* operator&()
//	//{
//	//	return this;
//	//}
//protected:
//	int _num;
//};
//
//void Display(const Person& p, const Student& s)
//{
//	cout << p._name << endl;
//	cout << s._num << endl;
//}
//
//int main()
//{
//	Student s1("zhangsan", 2);
//	Student s2(s1);
//
//	Student s3("lisi", 2);
//	s1 = s3;
//	return 0;
//}


//class Student;
//class Person
//{
//public:
//	friend void Display(const Person& p, const Student& s);
////protected:
//	static int _count;
//	string _name; // 姓名
//};
//
//int Person::_count = 0;
//
//class Student : public Person
//{
//	friend void Display(const Person& p, const Student& s);
//protected:
//	int _stuNum; // 学号
//};
//
//void Display(const Person& p, const Student& s)
//{
//	cout << p._name << endl;
//	cout << s._stuNum << endl;
//}
//
//void main()
//{
//	Person p;
//	Student s;
//	//Display(p, s);
//
//	++Person::_count;
//	cout << Person::_count++ << endl;
//	cout << Person::_count++ << endl;
//	cout << &Person::_count << endl;
//	cout << &Student::_count << endl;
//
//}

//class A final
//{
//private:
//	A()
//	{}
//protected:
//	int _a;
//};
//
//class B : public A
//{};
//
//// 1、父类构造函数私有 2、子类对象实例化，无法调用构造函数
//int main()
//{
////	B b;
//	return 0;
//}

class Base1 { public: int _b1; };
class Base2 { public: int _b2; };
class Derive : public Base1, public Base2 { public: int _d; };

int main()
{
	Derive d;
	Base1* p1 = &d;
	Base2* p2 = &d;
	Derive* p3 = &d;
	cout << sizeof(d) << endl;
	return 0;
}

//class Person
//{
//public:
//	string _name; // 姓名
//
//	// int _age;
//	// ...
//};
//
//class Student : virtual public Person // 虚继承
//{
//protected:
//	int _num; //学号
//};
//
//class Teacher : virtual public Person
//{
//protected:
//	int _id; // 职工编号
//};
//
//class Assistant : public Student, public Teacher
//{
//protected:
//	string _majorCourse; // 主修课程
//};
//
//int main()
//{
//	Assistant at;
//
//	// 菱形继承的二义性问题
//	// 零星虚拟继承同时解决了数据冗余和二义性问题
//	at._name = "张三";
//	//at.Student::_name = "张三";
//	//at.Teacher::_name = "李四";
// 
//	return 0;
//}

//class A
//{
//public:
//	int _a;
//};
////class B : public A
//class B : virtual public A
//{
//public:
//	int _b;
//};
////class C : public A
//class C : virtual public A
//{
//public:
//	int _c;
//};
//class D : public B, public C
//{
//public:
//	int _d;
//};
//int main()
//{
//	D d;
//	d.B::_a = 1;
//	d.C::_a = 2;
//	d._b = 3;
//	d._c = 4;
//	d._d = 5;
//	//B b = d; // 切片
//	//B* pb = &d;
//	//C c = d;
//	//C* pc = &d;
//	cout << sizeof(B) << endl;
//
//	B bb;
//	bb._a = 1;
//	bb._b = 2;
//	return 0;
//}



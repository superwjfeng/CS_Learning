#include "Person.h"

int age = 0; // age的定义、声明分离

// 这里需要指定PrintPersonInfo是属于Person这个类域
void Person::PrintPersonInfo() 
{
	cout << "address of static size: " << &size << endl;
	cout << "address of age: " << &age << endl;
//	cout << _name << " " << _gender << " " << _age << endl;
}
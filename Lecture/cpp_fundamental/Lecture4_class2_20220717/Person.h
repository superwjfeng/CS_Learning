#pragma once
#include <iostream>
using std::cout;
using std::endl;

// int age; // 定义
// 注意，在头文件里的全局变量有可能会在链接时产生冲突，因为可能被展开了多次   
extern int age; // 声明全局变量的正确方式

// 另一种定义方式，链接属性不同
// int size // 所有文件可见
static int size; // 仅当前文件可见，不会放进符号表里

class Person
{
public:
	void PrintPersonInfo(); // 声明 
private:
	char _name[20]; // 声明
	char _gender[3];
	int _age;
}; 

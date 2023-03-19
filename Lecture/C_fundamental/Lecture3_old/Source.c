#include <stdio.h>
#include <string.h>

typedef unsigned int u_int; // redefine type

extern int Add(int, int);

//#define MAX 100 // 定义标识符常量

#define MAX(X, Y) (X>Y?X:Y)//定义宏 Macro

// Struct is a type created by coder
struct Book
{
	char name[20];
	short price;
};

void test()
{
	static int g = 1; // static means variable will not be deleted each time exit the function
	g++;
	printf("g = %d\n", g);
}

int main()
{
	int a = 0;
	int b = ~a;
	// Negative number is stored inside memory as one's Complement
	int logical_sum = a && b;
	printf("%d\n", logical_sum);
	/*
	True -- Every number except 0
	False -- 0
	&& logical and, wihch is different with & bitwise and
	*/
	printf("%d\n", b); // We use and print the number as Sign-Magnitude

	int c = 10;
	int d = c++;
	//int e = ++c;
	printf("%d, %d\n", c, d);

	int f = (int)3.14; // Forced type conversion

	// int is defautly set as signed int, we can also assign 'unsigned int'
	/*
	data storage (read speed): register > cache > memory > hard drive
	register int a -- a is very ofen used, so assign a as a register variable
	*/
	/*
	auto keyword: (auto) int a : for local variables, it is also called auto variable,
	becauce the local variables found and killed automatically locally
	*/
	int i = 0;
	while (i < 5)
	{
		test();
		i++;
	}

	extern int g_val;
	printf("g_val = %d\n", g_val);

	int ex_a = 10;
	int ex_b = 20;
	int ex_z = Add(ex_a, ex_b);
	printf("External Add function's result is %d\n", ex_z);

	int max = MAX(ex_a, ex_b);
	printf("Macro test = % d\n", max);

	int test_address = 0;
	printf("address = %p\n", &test_address); //&取地址
	int* p = &test_address;//指针变量 Pointer 是用来存放地址的
	printf("address = %p\n", p);
	*p = 20; //解引用操作符 -- 找到指针变量*p指向的地址所存储的值并重新赋值
	printf("%d\n", test_address);

	char ch = 'w';
	char* pc = &ch;
	*pc = 'a';
	printf("%c\n", ch);
	printf("%d\n", sizeof(pc)); //32位>>4, 64位>>8

	double g = 3.14;
	double* pg = &d;
	printf("%d\n", sizeof(pg));

	struct Book b1 = { "C Programming", 55 }; // Struct variable
	printf("Book name: %s\n", b1.name);
	b1.price = 15;
	printf("After price: %d\n", b1.price);
	//b1.name = "Another book"; //name is a char, which essentially is an address
	//strcpy(b1.name, "c++");

	struct Book* pb = &b1;
	printf("%s\n", pb->name);
	printf("%d\n", pb->price);
	// . struct variable
	// -> struct pointer

	return 0;
}
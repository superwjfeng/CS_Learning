#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

//struct Stu
//{
//	char name[20];
//	int age;
//	char sex[8];
//	float score;
//}s1,s2,s3; //s1,s2,s3是通过struct Stu类型创建的变量
////s1,s2,s3是全局变量
//
//typedef struct Stu1
//{
//	char name[20];
//	int age;
//	char sex[8];
//	float score;
//}Stu1;
//
//typedef struct Stu Stu;//类型重定义
//
//int main()
//{
//	struct Stu s4; //局部变量
//	struct Stu s5; 
//	Stu s7;
//	return 0;
//}

//struct Point
//{
//	int x;
//	int y;
//}p1 = {10,15};
//
//struct S
//{
//	char c;
//	struct Point sp;
//	double d;
//	char arr[20];
//};
//
//void print1(struct S s)
//{
//	printf("%c\n", s.c);
//	printf("%d %d\n", s.sp.x, s.sp.y);
//	printf("%lf\n", s.d);
//	printf("%s\n", s.arr);
//}
//
//void print2(struct S* ps)
//{
//	printf("%c\n", ps->c);
//	printf("%d %d\n", ps->sp.x, ps->sp.y);
//	printf("%lf\n", ps->d);
//	printf("%s\n", ps->arr);
//}
//
//int main()
//{
//	//struct Point p = { 100,200 };
//	struct S ss = { 'w',{100,20},5.5,"Hello" };
//	
//	//ss.sp.x = 1000;
//	//strcpy(ss.arr, "world");
//
//	print1(ss);
//	print2(&ss); //结构体占用的内存空间比较大，用指针的实现方式比较好
//	return 0;
//}

void test2()
{
	printf("hehe\n");
}
void test1()
{
	test2();
}
void test()
{
	test1();
}
int main()
{
	test();
	return 0;
}

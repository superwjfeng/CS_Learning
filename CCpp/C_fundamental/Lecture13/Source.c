#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct Stu
{
	char name[20];
	int age;
	float score;
};

void print1(struct Stu ss)
{
	printf("%s %d %f\n", ss.name, ss.age, ss.score);
}

void print2(struct Stu* ps)
{
	//printf("%s %d %f\n", (*ps).name, (*ps).age, (*ps).score);
	printf("%s %d %f\n", ps->name, ps->age, ps->score);
}

int main()
{
	//int num = 0;
	//scanf("%d", &num);
	//int i = 0;
	//int count = 0;
	//_Bool flag1 = false;
	//bool flag2 = true;
	//if (flag2)
	//	printf("hehe\n");

	//for (i = 0; i < 32; i++)
	//{
	//	if ((num >> i) & 1)
	//	{
	//		count++;
	//	}
	//}
	//printf("%d\n", count);

	//int a = 10;
	//int* pa = &a;
	//int arr[10] = { 0 };
	//&arr;//取出数组的地址，数组的地址应该放到【数组指针】中去

	//struct S s = { 0 };
	//struct S* ps = &s;

	//sizeof 是一个操作符，不是函数，计算变量所占内存的大小，单位是字节
	//int a = 10;
	//printf("%d\n", sizeof a);
	//printf("%d\n", sizeof (a));
	//printf("%d\n", sizeof (int));
	//short s = 0;
	//printf("%d\n", sizeof(s = a + 2));
	//printf("%d\n", s); //sizeof内部中的表达式是不进行运算的

	//int arr[10] = { 0 };
	//printf("%d\n", sizeof(arr));

	//int a = 0;
	//printf("%d\n", ~a); //~a=-1
	//
	//int b = 11;
	//b |= 1 << 2;
	//b &= (~(1 << 2));
	
	
	//while (~scanf("%d", &n)
	//{

	//}

	//while (scanf("%d", &n) != EOF)
	//{

	//}

	//int a = (int)3.14;
	//printf("%d\n", a);

	//int a = 3;
	//int b = 0;
	//int m = (a > b ? a : b);
	//if (a > 5)
	//	b = 3;
	//else
	//	b = -3;
	//b = a > 5 ? 3 : -3;

	////arr[4] <==> *(arr + 4) <==> *(4 + arr) <==> 4[arr];
	////说明[]是一个操作符, a+b = b+a <==>arr[4] = 4[arr]

	struct Stu s = { "ZhangSan",20,90.5f };
	//s.name = "ZhangSanfeng"; 错误
	//*(s.name) = "ZhanSanfeng"; //字符串地址指向的是一个元素，放不下
	strcpy(s.name, "ZhangSanfeng");
	//scanf("%s", s.name);正确
	print1(s);
	print2(&s);

	return 0;
}

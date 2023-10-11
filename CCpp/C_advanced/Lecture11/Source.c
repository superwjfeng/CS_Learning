#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>


//栈区：局部变量、函数的形式参数
//堆区：malloc, free, calloc, realloc（动态内存管理）
//静态区：全局变量、静态变量

////malloc, free
////void *malloc( size_t size );
//int main()
//{
//	//int arr[10];
//	//char arr2[40];
//	int* ptr = (int*)malloc(40); //malloc(0)是C语言标准未定义的，取决于编译器，不要这么写
//	//int* ptr = (int*)malloc(INT_MAX); //申请失败：返回 malloc: Not enough space
//	int* p = ptr; //不能直接使用ptr，因为free的时候ptr已经走到了空间的后面，必须要记住起始未知，否则内存泄露
//	if (p == NULL) //malloc申请失败返回空指针
//	{
//		perror("malloc");
//		return 1;
//	}
//	int i = 0;
//	for (i = 0; i < 10; i++)
//	{
//		*p = i;
//		p++;
//	}
//	/* 不创建临时变量p的写法，这么写不会改变ptr
//	for (i = 0; i < 10; i++)
//	{
//		*(ptr + i) = i;
//	}
//	*/
//	
//	free(ptr); //ptr已经被释放了，但还是保存了ptr当前的未知，是野指针
//	ptr = NULL; //free完置成空指针
//	//当我们不释放动态申请的内存的时候
//	//如果程序结束，动态申请的内存由操作系统自动回收
//	//但是如果程序不结束，动态内存是不会自动回收的，就会形成内存泄露的问题
//	//某些程序有保护机制，限制程序申请内存的量，但如果没有这种保护机制，有大量的此类程序时就会使程序宕机
//
//	if (ptr != NULL)
//	{
//		*ptr = 100;
//	}
//
//	return 0;
//}

////calloc
//int main()
//{
//	int* p = (int*)calloc(10, sizeof(int)); //calloc 森请的空间会被初始化为0，malloc不会，但malloc会返回初始地址
//	if (p == NULL)
//	{
//		perror("calloc");
//		return 1;
//	}
//	int i = 0;
//	for (i = 0; i < 10; i++)
//	{
//		*(p + i) = i;
//	}
//
//	
//	int* ptr = realloc(p, 80); //如果realloc失败也会返回NULL，那么原来的数据就丢失了，所以用ptr中转一下
//	if (ptr != NULL)
//	{
//		p = ptr;
//	}
//
//	free(p);
//	p = NULL;
//
//	return 0;
//}


//常见错误

////1. 对NULL指针的解引用错误
////解决办法：对malloc函数的返回值进行判断
//int main()
//{
//	int* p = (int*)malloc(1000);
//	int i = 0;
//	if (p == NULL)
//	{
//		//...
//		return 1;
//	}
//	//使用
//	for (i = 0; i < 250; i++)
//	{
//		*(p + i) = i;
//	}
//
//	free(p);
//	p = NULL;
//
//	return 0;
//}

////2.对动态开辟空间的越界访问
//int main()
//{
//	int* p = (int*)malloc(100);
//	int i = 0;
//	if (p == NULL)
//	{
//		//...
//		return 1;
//	}
//
//	for (i = 0; i <= 25; i++) //26个int越界了
//	{
//		*(p + i) = i;
//	}
//
//	return 0;
//}

////3.对非动态开辟内存使用free释放
//int main()
//{
//	int a = 10; //栈区和静态区中存的局部变量和全局变量的是编译器自动释放的
//	int* p = &a;
//	//...
//
//	free(p);
//	p = NULL;
//	return 0;
//}

////4.使用free释放一块动态开辟内存的一部分
//int main()
//{
//	int* p = (int*)malloc(100);
//	if (p == NULL)
//	{
//		return 1;
//	}
//
//	int i = 0;
//	for (i = 0; i < 10; i++)
//	{
//		*p = i;
//		p++;
//	}
//
//	free(p); //不能从动态内存的中间开始释放，必须要从开头开始释放
//	p = NULL;
//
//	return 0;
//}

////5.对同一块动态内存多次释放
//int main()
//{
//	int* p = malloc(100);
//	if (p == NULL)
//		return 1;
//	
//	free(p);
//	//...
//	free(p);
//	p = NULL;
//}

////6.动态开辟内存忘记释放（内存泄漏）

//void test()
//{
//	int* p = malloc(100);
//	if (1)
//		return;  //也会内存泄露，若if成立则直接返回了，没机会走到下一步
//	free(p);
//	p = NULL;
//}


//void test()
//{
//	int* p = malloc(100);
//}
//
//int main()
//{
//	test();
//	while (1)
//	{
//		;
//	}
//	return 0;
//}

//void(GetMemory(char* p))
//{
//	p = (char*)malloc(100); //p是形参对实参不影响，且内存泄漏
//}
//
//void Test(void)
//{
//	char* str = NULL;
//	GetMemory(str);
//	strcpy(str, "HelloWorld"); //对空指针解引用了
//	printf(str);
//}
//
//int main()
//{
//	Test();
//	return 0;
//}

//void(GetMemory(char** p))
//{
//	*p = (char*)malloc(100);
//}
//
//void Test(void)
//{
//	char* str = NULL;
//	GetMemory(&str);
//	strcpy(str, "HelloWorld");
//	printf(str);
//}
//
//int main()
//{
//	Test();
//	return 0;
//}

////返回栈空间地址的问题
//char* GetMomory(void)
//{
//	char p[] = "HelloWorld";
//	return p;
//}
//
//void Test(void)
//{
//	char* str = NULL;
//	str = GetMomory(); //p出了GetMemory已经销毁了，形成野指针
//	printf(str);
//}
//
//int main()
//{
//	Test();
//	return 0;
//}

//void GetMemory(char** p, int num)
//{
//	*p = (char*)malloc(num);
//}
//void Test(void)
//{
//	char* str = NULL;
//	GetMemory(&str, 100);
//	strcpy(str, "hello");
//	printf(str); //没free
//}
//
//int main()
//{
//	Test();
//	return 0;
//}
//
//void Test(void)
//{
//	char* str = (char*)malloc(100);
//	strcpy(str, "hello");
//	free(str);
//	//str = NULL; 修改：指针置空
//	if (str != NULL)
//	{
//		strcpy(str, "world"); //野指针
//		printf(str);
//	}
//}
//
//int main()
//{
//	Test();
//	return 0;
//}

/*
1. 
int* f1(void)
{
	int x = 10;
	return &x; //返回栈空间地址的问题
}

2.
int* f2(void)
{
	int* ptr;
	*ptr = 10; //ptr没有赋值，是随机值，解引用形成野指针
	return ptr;   //注意：返回变量名是没有问题的，栈帧空间在销毁是会把变量名和值放到寄存器里，再给其他值
}
这两道题一定要注意区别！！
*/

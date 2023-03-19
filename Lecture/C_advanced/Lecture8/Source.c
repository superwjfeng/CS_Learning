#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>

////strtok 字符串分割
//int main()
//{
//	char arr[] = "wj.feng@tum.de";
//	char buf[30] = { 0 };
//
//	strcpy(buf, arr); //strok会修改原数据，因此使用buf拷贝
//	const char* sep = "@."; //不区分分隔符的出现顺序，相同的分隔符只要写一个
//	char* str = NULL;
//	for (str = strtok(buf, sep); str != NULL; str = strtok(NULL, sep))
//	{
//		printf("%s\n", str); 
//	}
//
//	//printf("%s\n", strtok(arr, sep)); //只找第一个标记
//	//printf("%s\n", strtok(NULL, sep)); //是从上一次保存好的位置开始继续往后找
//	//printf("%s\n", strtok(NULL, sep)); //函数内部有一个静态指针变量保存字符串位置，函数调用结束后不会被销毁，可以下一次调用时被用到
//	//printf("%s\n", strtok(NULL, sep));
//	return 0;
//}

//// strerror 头文件：#include <errno.h>
//// 全局变量：errno（错误码）比如说404就是一种错误码
//int main()
//{
//	printf("%s\n", strerror(0));
//	printf("%s\n", strerror(1));
//	printf("%s\n", strerror(2));
//	printf("%s\n", strerror(3));
//
//	int* p = (int*)malloc(INT_MAX);
//	if (p == NULL)
//	{
//		printf("%s\n", strerror(errno));
//		perror("malloc"); //与strerror（不打印）使用场景不同
//		return 1;
//	}
//	return 0;
//}

//int main()
//{
//	int ret = isdigit('5');
//	int ret2 = isdigit('q');
//	char ch = 'a';
//	/*
//	if(ch >= 'a' && ch <= 'z')
//	{
//	;
//	}
//	*/
//	int ret3 = islower(ch); //增强C语言的通用性和规范性
//	printf("%d\n", ret3);
//	return 0;
//}

////void * memcpy ( void * destination, const void * source, size_t num );
//void* my_memcpy(void* dest, const void* src, size_t count)
//{
//	assert(dest && src);
//	void* ret = dest;
//	while (count--)
//	{
//		*(char*)dest = *(char*)src;
//	//	dest = (char*)dest + 1;
//	//	src = (char*)src + 1;
//		//(char*)dest = (char*)dest + 1;
//		//(char*)src = (char*)src + 1;
//		((char*)dest)++;
//		((char*)src)++;
//	}
//	
//	return ret;
//}
//
//int main()
//{
//	int arr1[10] = { 1,2,3,4,5,6,7,8,9,10 };
//	int arr2[5] = { 0 };
//	my_memcpy(arr2, arr1, 20);
//	int i = 0;
//	for (i = 0; i < 5; i++)
//	{
//		printf("%d", arr2[i]);
//	}
//	return 0;
//}

////void * memmove ( void * destination, const void * source, size_t num );
////第一种写法，前->后/后->前/后->前
//void* my_memmove(void* dest, const void* src, size_t count)
//{
//	assert(dest && src);
//	void* ret = dest;
//	//1
//	if (dest < src)
//	{//前->后
//		while (count--)
//		{
//			*(char*)dest = *(char*)src;
//			dest = (char*)dest + 1;
//			src = (char*)src + 1;
//
//			//++(char*)dest; //在某些编译器下可能会有问题
//			//++(char*)src;
//		}
//	}
//	else
//	{//后->前
//		while (count--)
//		{
//			*((char*)dest + count) = *((char*)src + count);//以count=20为例，则第一个之间相差19个字节
//		}
//	}
//	return ret;
//}

////第二种写法，前->后/后->前/前->后
//void* my_memmove(void* dest, const void* src, size_t count)
//{
//	assert(dest && src);
//	void* ret = dest;
//	if (dest > src && dest < ((char*)src + count))
//	{//后->前
//		while (count--)
//		{
//			*(char*)dest = *(char*)src;
//			dest = (char*)dest + 1;
//			src = (char*)src + 1;
//		}
//	}
//	else
//	{//前->后
//		while (count--)
//		{
//			*((char*)dest + count) = *((char*)src + count);
//		}
//	}
//	return ret;
//}

//int main()
//{
//	int arr1[10] = { 1,2,3,4,5,6,7,8,9,10 };
//	int sz = sizeof(arr1) / sizeof(arr1[0]);
//	//int arr2[10] = { 0 }; //创建一个临时空间不是一个好的写法，因为很难给定到底给多少大小，因此还是用自己的空间
//	////my_memcpy(arr2, arr1, 20);
//	//my_memcpy(arr1 + 2, arr1, 20); //从3开始复制 期望结果: 1 2 1 2 3 4 5 8 9 10
//	////实际结果：1 2 1 2 1 2 1 8 9 10
//	////memcopy不适合重叠内存拷贝（自己拷贝到自己），要用memmove
////	my_memmove(arr1 + 2, arr1, 20);
//	my_memmove(arr1, arr1 + 2, 20);
//
//	int i = 0;
//	for (i = 0; i < sz; i++)
//	{
//		printf("%d ", arr1[i]);
//	}	
//	return 0;
//}

////memcmp
////int memcmp(const void* ptr1, const void* ptr2, size_t num); //因为要兼容所有数据类型，所以用了void*，因此这里是一个字节一个字节进行比较的
////形参与实参数据类型不一致时，强制转换为形参的数据类型void*
//int main()
//{
//	int arr1[5] = { 1,2,3,4,5 };
//	int arr2[5] = { 1,2,3,4,0x11223305 };
//	int ret = memcmp(arr1, arr2, 18); //1，逐字节比较
//	int ret = memcmp(arr1, arr2, 17); //0
//	printf("%d\n", ret);
//	return 0;
//}

////memset 初始化内存单位
////void* memset(void* dest, int c, size_t count);
//int main()
//{
//	int arr[] = { 1,2,3,4,5 };
//	memset(arr, 0xFF, 20); //以字节为单位来初始化内存单元的
//	return 0;
//}

//顺序表
////下面这么写是错误的，类似于递归，无法确定数据类型的大小
//struct Node
//{
//	int data;
//	struct Node n;
//};
//
//int main()
//{
//	struct Node n;
//	return 0;
//}

struct Node
{
	int data; //数据域
	struct Node* next; //指针域
};

struct Book
{
	char name[20];
	float price;
	char id[12];
} s = {"Harry Potter", 55.5f, "XXXXXX1"};

//int main()
//{
//	struct Node n;
//	struct Book s2 = { "Harry Potter 2",60.0f, "XXXXXX2"};
//	return 0;
//}

////或者这么写
//typedef struct Node
//{
//	int data;
//	struct Node* next;
//} Node;
//
//int main()
//{
//	struct Node n1;
//	Node n2;
//}

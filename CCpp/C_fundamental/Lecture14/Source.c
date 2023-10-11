#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>


int main()
{
	//指针数组应用
	int data1[] = { 1,2,3,4,5 };
	int data2[] = { 2,3,4,5,6 };
	int data3[] = { 3,4,5,6,7 };
	int* arr[3] = { data1,data2,data3 };
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		int j = 0;
		for (j = 0; j < 5; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}

//int main()
//{
//	int a = 10;
//	int* pa = &a; //pa是指针变量（一级指针）
//	int** ppa = *pa; //ppa是一个二级指针
//	//'*'表示ppa是一个指针变量 'int*'说明ppa指向的对象是int*类型的
//}

//int main()
//{
//	int arr[10] = { 0 };
//	printf("%p\n", arr); //数组名是首元素的地址
//	printf("%p\n", arr + 1);
//
//	printf("%p\n", &arr[0]);
//	printf("%p\n", &arr[0] + 1);
//
//	printf("%p\n", &arr); //&arr取的是整个数组的地址
//	printf("%p\n", &arr + 1);
//
//	return 0;
//}

//int main()
//{
//	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
//	int* p = arr;
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	int i = 0;
//	for (i = 0; i < sz; i++)
//	{
//		printf("%d ", *(p + i));
//	}
//	return 0;
//}

//int my_strlen(char* str)
//{
//	char* start = str;
//	while (*str)
//	{
//		str++;
//	}
//	return str - start;
//}
//
//int main()
//{
//	char arr[] = "abcdef";
//	int len = my_strlen(arr);
//	printf("%d\n", len);
//	return 0;
//}

//int* test()
//{
//	int a = 10;
//	printf("%d\n", a);
//	return &a;
//}
//
//int main()
//{
//	int* p = test();
//	*p = 100; //test调用完后a的内存空间已释放，p为野指针
//	return 0;
//}

//int main()
//{
//	int a = 10;
//	int* p = &a;
//
//	//0地址是给内核使用的，用户不能使用
//	int* q = NULL; //给指针赋空值，避免野指针
//	if (q != NULL)
//	{
//		//...
//	}
//	return 0;
//}

//int main()
//{
	//int a = 1;
	//int b = (++a) + (++a) + (++a);
	//printf("%d\n", b);

	//int a = 0x11223344;
	//int* pa = &a;
	//printf("%p", pa);
	//*pa = 0;
	//char* pa = &a;
	//*pa = 0; //这种情况下解引用只能操作一个字节

	//int arr[10] = { 0 };

	//int* p = arr;
	//int i = 0;
	//for (i = 0; i < 10; i++)
	//{
	//	*p = 0x11223344;
	//	p++;
	//}

	//char* p = (char*)arr;
	//int i = 0;
	//for (i = 0; i < 40; i++)
	//{
	//	*p = 'x';
	//	p++;
	//}
	
//	return 0;
//}
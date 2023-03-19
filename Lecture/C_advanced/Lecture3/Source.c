#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//int main()
//{
//	char ch = 'w';
//	char* pc = &ch;
//	*pc = 'a';
//	printf("%c\n", ch);
//	return 0;
//};

//int main()
//{
//	const char* p = "abcdef"; //字符串的首元素'a'的地址存到*p指针里
//	// *p = 'w'; //错误，常量字符串是不可被修改的，放到数组里的字符是可以改的
//	//和以下的数组指针类似，p也是arr数组的第一个元素的地址
//	//int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
//	//int* p = arr;
//
//	printf("%c\n", *p);
//	printf("%s\n", p);
//}

//int main()
//{
//	const char* p1 = "abcdef"; //两个相同的常量字符串在静态区只创建一份
//	const char* p2 = "abcdef"; //因此p1和p2的地址相同，都指向"abcdef"的第一个字符的地址
//
//	char arr1[] = "abcdef"; //用abcdef\0初始化了arr1和arr2，因此是两个不同的数组，其首元素地址不同
//	char arr2[] = "abcdef";
//	
//	if (p1 == p2)
//	{
//		printf("p1 == p2\n");
//	}
//	else
//	{
//		printf("p1 != p2\n");
//	}
//
//	if (arr1 == arr2)
//	{
//		printf("arr1 == arr2");
//	}
//	else
//	{
//		printf("arr1 != arr2");
//	}
//
//	return 0;
//}

//int main()
//{
//	int a = 10;
//	int b = 20;
//	int c = 30;
//
//	int* p1 = &a;
//	int* p2 = &b;
//	int* p3 = &c;
//
//	int* arr[3] = { &a,&b,&c };
//	int i = 0;
//	for (i = 0; i < 3; i++)
//	{
//		printf("%d\n", *(arr[i]));
//	}
//	return 0;
//}

//int main()
//{
//	int arr1[5] = { 1,2,3,4,5 };
//	int arr2[5] = { 2,3,4,5,6 };
//	int arr3[5] = { 3,4,5,6,7 };
//
//	int* parr[3] = { arr1,arr2,arr3 };
//	int i = 0;
//	for (i = 0; i < 3; i++)
//	{
//		int j = 0;
//		for (j = 0; j < 5; j++)
//		{
//			printf("%d", parr[i][j]);
//			//printf("%d ", *(parr[i]+j));
//		}
//		printf("\n");
//	}
//	return 0;
//}

//int main()
//{
//	int a = 10;
//	int* p = &a;
//	int arr[10] = { 0 };
//	printf("%p\n", arr);
//	printf("%p\n", &arr[0]);
//	printf("%p\n", &arr); //整个数组的地址也是从arr[0]开始的
//
//	return 0;
//}

////形参写成数组的形式
//void print1(int arr[], int sz)
//{
//	int i = 0;
//	for (i = 0; i < sz; i++)
//	{
//		printf("%d ", arr[i]);
//	}
//	printf("\n");
//}
//
////形参写成指针的形式
//void print1(int* arr, int sz)
//{
//	int i = 0;
//	for (i = 0; i < sz; i++)
//	{
//		printf("%d ", *(arr + i));
//	}
//	printf("\n");
//}
//
//int main()
//{
//	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	print1(arr, sz);
//	return 0;
//}

////用数组指针，不推荐，一般不会用在一维数组上
//void print1(int(*p)[10], int sz)
//{
//	int i = 0;
//	for (i = 0; i < sz; i++)
//	{
//		printf("%d ", *(*p + i)); //*p就是数组名=首元素地址，所以*p就是&arr[0]
//	}
//	printf("\n");
//}
//
//int main()
//{
//	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	print1(&arr, sz);
//	return 0;
//}

////二维数组
////写成数组形式
//void print2(int arr[3][5], int c, int r)
//{
//	int i = 0;
//	for (i = 0; i < c; i++)
//	{
//		int j = 0;
//		for (j = 0; j < r; j++)
//		{
//			printf("%d ", arr[i][j]);
//		}
//		printf("\n");
//	}
//}

//写成指针形式
void print2(int(*p)[5], int c, int r)
{
	int i = 0;
	for (i = 0; i < c; i++)
	{
		int j = 0;
		for (j = 0; j < r; j++)
		{
			printf("%d ", *(*(p + i) + j));
			//printf("%d ", p[i][j]);
		}
		printf("\n");
	}

}

int main()
{
	int arr[3][5] = { {1,2,3,4,5},{2,3,4,5,6},{3,4,5,6,7} };
	print2(arr, 3, 5); //二维数组的数组名表示首元素地址，即第一行一维数组的地址
	return 0;
}



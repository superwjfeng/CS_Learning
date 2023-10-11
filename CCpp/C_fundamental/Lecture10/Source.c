#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int a; //全局变量未初始化默认为0

void bubble_sort(int arr[], int sz) //形参写成 int arr[]只是更容易理解语法，是一种惯例
//void bubble_sort(int* arr, int sz) //这样写也没有错
{
	//int sz = sizeof(arr) / sizeof(arr[0]); //趟数
	//错误原因：int arr[]实际上是 int* arr 是arr首元素的指针，因此形参传入的也是4字节的地址
	int i = 0;
	for (i = 0; i < sz - 1; i++)
	{
		int flag = 1;//假设已经有序
		int j = 0;
		for (j = 0; j < sz-1-i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				flag = 0;
				int tmp = arr[j];  //和整形数的交换需要取地址不同，数组的操作是直接使用地址的
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
		if (1 == flag)
		{
			break;
		}
	}

}

int main()
{
	//static int b; //静态变量未初始化默认为0
	////在静态区创建的变量默认为0，在栈区创建的变量（局部变量、形式参数）不初始化就是随机值
	//int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	//int arr1[100] = { 0 };

	//int arr2[10] = { 1,2,3,4 }; //不完全初始化，未初始化的默认为0

	//char ch1[] = { 'a','b','c' }; //a b c
	//char ch2[] = { 'a', 98, 'c' }; //不指定数组大小时自动指定
	//char ch3[] = "abc"; //a b c \0 四个字符

	//int arr3[10]; //未初始化的化生成随机值

	//int i = 0;
	//int arr[100] = { 0 };
	//for (i = 0; i < 100; i++)
	//{
	//	arr[i] = i + 1;
	//}
	//for (i = 0; i < 100; i++)
	//{
	//	printf("%d\n", arr[i]);
	//}


	////一维数组在内存中的存储
	//int i = 0;
	//int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	//int sz = sizeof(arr) / sizeof(arr[0]);
	//int* p = &arr[0];

	//for (i = 0; i <= sz; i++)
	//{
	//	printf("&arr[%d] = %p <===> %p\n", i, &arr[i], p + i);
	//}

	//int arr1[3][5] = { 1,2,3,4,5,6 };//可以行省略，但不能列省略
	//int arr2[3][5] = { {1,2},{3,4},{5,6} };

	//int arr[][5] = { {1,2},{3,4},{5,6} };
	//int i = 0;
	//for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	//{
	//	int j = 0;
	//	for (j = 0; j < sizeof(arr[0])/sizeof(arr[0][0]); j++)
	//	{
	//		printf("%d ", arr[i][j]);
	//	}
	//	printf("\n");
	//

	////Bubble sorting
	//int arr[] = { 9,8,7,6,5,4,3,2,1,0 };
	//int i = 0;
	//int sz = sizeof(arr) / sizeof(arr[0]);
	//bubble_sort(arr, sz);
	//for (i = 0; i < sz; i++)
	//{
	//	printf("%d ", arr[i]);
	//}

	//三子棋



	return 0;
}
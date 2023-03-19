#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>


int get_max(int x, int y)
{
	//return (x > y ? x : y);
	if (x > y)
		return x;
	else
		return y;
}

//int x, int y称为函数的形参 Formal parameter
//当实参传给形参的时候，形参是实参的一份临时拷贝，对形参的修改不会影响实参
void swap1(int x, int y)
{
	int tmp = 0;
	tmp = x;
	x = y;
	y = tmp;
}

//通过指针使swap2内部和swap2(a,b)给的实参变量之间建立真正的联系
void swap2(int* pa, int* pb)
{
	int tmp = *pa;
	*pa = *pb;
	*pb = tmp;
}


int is_prime(int n)
{
	int j = 0;
	for (j = 2; j <= sqrt(n); j++)
	{
		if (n % j == 0)
		{
			return 0;
		}
	}
	return 1;
}

int is_leap_year(int n) //尽量让函数的功能单一，不要往里面加很多功能，这样就可以重复利用
{
	if (((n % 4 == 0) && (n % 100 != 0)) || (n % 400 == 0))
	{
		return 1;
	}
	else
		return 0;
}

//                int arr[]其实是一个int指针 int* arr
int binary_search(int arr[], int k, int sz)
{
	int left = 0;
	int right = sz - 1;
	//int sz = sizeof(arr) / sizeof(arr[0]);
	//如果选择不传入sz，而是在函数中计算sz的话会出错
	//数组在传参的时候，传递的不是整个数组而是首元素的地址
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (arr[mid] < k)
		{
			left = mid + 1;
		}
		else if (arr[mid] > k)
		{
			right = mid - 1;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}


void test(int* p)
{
	*p += 1;
	//(*p)++; ++优先级更高
}

int main()
{
	//char arr1[] = "abcdef";
	//char arr2[20] = "XXXXXXXX";
	//strcpy(arr2, arr1);
	//printf("%s\n", arr2);

	//char arr[] = "Hello bit";
	//memset(arr, 'X', 5);
	//printf("%s\n", arr);

	//int a, b = 0;
	//scanf("%d %d", &a, &b);
	//int m = get_max(a, b);
	//printf("%d\n", m);

	//int a, b = 0;
	//scanf("%d %d", &a, &b);
	//printf("a=%d,b=%d\n", a, b);
	////a,b称为实参 Actual parameter
	////swap1(a, b);
	//swap2(&a, &b);
	//printf("a=%d,b=%d\n", a, b);

	//int i = 0;
	//for (i = 100; i <= 200; i++)
	//{
	//	if (is_prime(i) == 1)
	//	{
	//		printf("%d\n", i);
	//	}
	//}

	//int Year = 0;
	//for (Year = 1000; Year <= 2000; Year++)
	//{
	//	if (is_leap_year(Year)==1)
	//	{
	//		printf("%d  ", Year);
	//	}
	//}


	////二分查找：找到了就返回下标，找不到返回-1
	//int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	//int k = 0;
	//scanf("%d", &k);
	//int sz = sizeof(arr) / sizeof(arr[0]);
	//int ret =binary_search(arr, k, sz);
	//if (-1 == ret)
	//	printf("No such result.\n");
	//else
	//	printf("Index = %d\n", ret);

	int num = 0;
	scanf("%d", &num);
	test(&num);
	printf("%d\n", num);
	


	return 0;

}
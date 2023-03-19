#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
////Problem 9
//void bubble_sort(int arr[], int sz)
//{
//	int i = 0;
//	for (i = 0; i < sz - 1; i++)
//	{
//		int j = 0;
//		for (j = 0; j < sz - 1 - i; j++)
//		{
//			if (arr[j] > arr[j + 1]) //升序
//			{
//				int tmp = arr[j];
//				arr[j] = arr[j + 1];
//				arr[j + 1] = tmp;
//			}
//		}
//	}
//}
//
//int main()
//{
//	int arr[] = { 10,9,8,7,6,5,4,3,2,1 };
//	
//	int i = 0;
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	for (i = 0; i < sz; i++)
//	{
//		printf("%d ", arr[i]);
//	}
//
//	bubble_sort(arr, sz);
//	printf("\n");
//	for (i = 0; i < sz; i++)
//	{
//		printf("%d ", arr[i]);
//	}
//	return 0;
//}

////Problem 10
//void init(int arr[], int sz)
//{
//	int i = 0;
//	for (i = 0; i < sz; i++)
//	{
//		arr[i] = 0;
//	}
//}
//
void print(int arr[], int sz)
{
	int i = 0;
	for (i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}
//
//void reverse(int* arr, int sz)
//{
//	int left = 0;
//	int right = sz - 1;
//	while (left < right)
//	{
//		int tmp = arr[left];
//		arr[left] = arr[right];
//		arr[right] = tmp;
//		left++;
//		right--;
//	}
//
//}
//
//int main()
//{
//	int arr[5];
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	int arr_test[5] = { 3,2,1,5,4 };
//	init(arr, sz);
//	print(arr_test, sz);
//	reverse(arr_test, sz);
//	print(arr_test, sz);
//	
//	return 0;
//}


//Problem 11
void swap(int* arr_a, int* arr_b, int sz)
{
	int i = 0;
	for (i = 0; i < sz; i++)
	{
		int tmp = arr_a[i];
		arr_a[i] = arr_b[i];
		arr_b[i] = tmp;
	}
}

int main()
{
	int arr_a[5] = { 1,2,3,4,5 };
	int arr_b[5] = { 6,7,8,9,10 };
	int sz = sizeof(arr_a) / sizeof(arr_a[0]);
	printf("Original: array a and b:\n");
	print(arr_a, sz);
	print(arr_b, sz);
	swap(arr_a, arr_b, sz);
	printf("After swap: array a and b:\n");
	print(arr_a, sz);
	print(arr_b, sz);
	return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

////Problem 1
//int main()
//{
//	int money = 0;
//	scanf("%d", &money);
//	int bottle = money;
//	int count = bottle;
//	while (bottle >= 2)
//	{
//		count += (bottle / 2);
//		bottle = bottle / 2 + bottle % 2;
//	}
//	printf("Money: %d\n", money);
//	printf("Total: %d\n", count);
//
//
//	return 0;
//}

//Problem 2

void odd_sort(int arr[], int sz)
{
	int left = 0;
	int right = sz - 1;
	int i = 0;
	while (left < right)
	{
		int tmp = 0;
		if ((left < right) && (arr[left] % 2 == 1))//left<right 是为了防止全奇数时，数组越界
		{
			left++;
		}

		if ((left < right) && (arr[right] % 2 == 0))//left<right 是为了防止全偶数时，数组越界
		{
			right--;
		}

		if (left < right)
		{
			tmp = arr[right];
			arr[right] = arr[left];
			arr[left] = tmp;
		}

	}
	for (i = 0; i < sz; i++)
	{
		printf("%d", arr[i]);
	}

}

int main()
{
	int arr[6] = { 3,2,4,5,1,2 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	odd_sort(arr, sz);
	return 0;
}

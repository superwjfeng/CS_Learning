#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

////Problem 9
//int main()
//{
//	int arr[5] = { 1,2,3,4,5 };
//	int* p = arr;
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	int i = 0;
//	for (i = 0; i < sz; i++)
//	{
//		printf("%d ", *p++);
//	}
//	return 0;
//}

////Problem 10
//int main()
//{
//	char arr[10000] = { 0 };
//	gets(arr);
//	//fgets(arr, 100, stdin);
//	int len = strlen(arr);
//	char* left = arr;
//	char* right = arr + len - 1;
//	
//	while (left < right)
//	{
//		char tmp = *left;
//		*left = *right;
//		*right = tmp;
//		left++;
//		right--;
//	}
//	printf("%s", arr);
//	
//	return 0;
//}

////Problem 11
//int main()
//{
//	int a = 0;
//	scanf("%d", &a);
//	int i = 0;
//	int tmp = 0;
//	int sum = 0;
//
//	for (i = 0; i < 5; i++)
//	{
//		tmp = tmp * 10 + a;
//		sum += tmp;
//	}
//	printf("Sn=%d", sum);
//	return 0;
//}

//Problem 12
//水仙花数是一种自幂数
int pow(int n, int i)
{
	int j = 0;
	int product = 1;
	for (j = 1; j <= i; j++)
	{
		product *= n;
	}
	return product;
}

int count_bit(int n)
{
	int count = 1;
	while (n /= 10)
	{
		count++;
	}
	return count;
}

int main()
{
	int i = 0;
	for (i = 0; i <= 100000; i++)
	{
		int j = i;
		int sum = 0;
		int bit = count_bit(j);
		while (j > 0)
		{
			sum += pow((j % 10), bit);
			j /= 10;
		}
		if (i == sum)
			printf("%d\n", i);
	}
	return 0;
}

////Problem 13
//int main()
//{
//	int line = 0;
//	scanf("%d", &line);
//	int i = 0;
//	for (i = 1; i <= line; i++)
//	{
//		int j = 0;
//		for (j = 0; j < line - i; j++)
//		{
//			printf(" ");
//		}
//		for (j = 0; j < 2 * i - 1; j++)
//		{
//			printf("*");
//		}
//		printf("\n");
//	}
//	for (i = 1; i <= line - 1; i++)
//	{
//		int j = 0;
//		for (j = 0; j < i; j++)
//		{
//			printf(" ");
//		}
//		for (j = 0; j < (2 * (line - i)) - 1; j++)
//		{
//			printf("*");
//		}
//		printf("\n");
//	}
//	return 0;
//}

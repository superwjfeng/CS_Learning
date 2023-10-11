#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int print(int n)
{
	if (n > 9)
		print(n / 10);

	printf("%d ", n % 10);
}

int factorial(int n)
{
	if (0 == n)
		return 1;
	else
		return n * factorial(n - 1);
}

int digit_sum(int n)
{
	if (n <= 9)
		return n;
	else
		return (n % 10) + digit_sum(n / 10);
}

int power_func(int n, int k)
{
	if (0 == n)
	{
		printf("Root can not be 0");
		return 0;
	}
	if (1 == k)
		return n;
	else
		return n * power_func(n, k - 1);
}

int my_strlen(char chr)
{
	
}


int main()
{

	////Problem 3
	//int n = 0;
	//scanf("%d", &n);
	//print(n);

	////Problem 4 Non-iterative
	//int n = 0;
	//int i = 0;
	//int ret = 1;
	//scanf("%d", &n);
	//for (i = 1; i <= n; i++)
	//{
	//	ret *= i;
	//}
	//printf("Non-iterative method: %d", ret);

	////Probelm 4 Iterative
	//int n = 0;
	//scanf("%d", &n);
	//int ret = factorial(n);
	//printf("Iterative method: %d", ret);

	//Problem 5 Non-iterative
	/* 这么写错误的原因是chr是一个数组，而chr表示的是数组首个数据的地址，地址是不可以进行自增计算的
	////*  int my_strlen(char* str)
 ////{
 ////	int count = 0;
 ////	while('\0' != *str)
 ////	{
 ////		count++;
 ////		str++;
 ////	}
 ////	return count;
 ////}

	这么写对的原因是因为str是一个字符串，字符串可以进行自加
	char chr[20] = { 0 };
	scanf("%s", &chr);
	int count = 0;
	while ('\0' != *chr)
	{
		count++;
		chr++;
	}
	*/

	//while ('\0' != chr[count])
	//{
	//	count++;
	//}
	//printf("%d", count);
	
	//Problem 5 Iterative
	char chr[20] = { 0 };
	scanf("%s", &chr);
	printf("%d", my_strlen(chr));

	////Problem 7
	//int n = 0;
	//scanf("%d", &n);
	//printf("%d", digit_sum(n));

	////Problem 8
	//int n = 0;
	//int k = 0;
	//printf("Please input the number of root and power:>\n");
	//scanf("%d%d", &n, &k);
	//printf("%d", power_func(n, k));
	
	//Problem 9 Non-iterative
	
	//Problem 9 Iterative

	return 0;
}
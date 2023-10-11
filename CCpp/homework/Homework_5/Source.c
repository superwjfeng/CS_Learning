#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int main()
{

	//// Problem 7
	//int a, b, c;
	//scanf("%d%d%d", &a, &b, &c);
	//if (a < b)
	//{
	//	int tmp = a;
	//	a = b;
	//	b = tmp;
	//}
	//if (a < c)
	//{
	//	int tmp = a;
	//	a = c;
	//	c = tmp;
	//}
	//if (b < c)
	//{
	//	int tmp = b;
	//	b = c;
	//	c = tmp;
	//}

	//printf("a=%d, b=%d, c=%d", a, b, c);



	//// Problem 8 print multiple of 3 between 1-100
	//int i = 1;
	//while (i <= 100)
	//{
	//	if (i % 3 == 0)
	//	{
	//		printf("i=%d ;", i);
	//	}
	//	i++;
	//}

	//// Problem 8 revised
	//int i = 0;
	//for (i = 3; i <= 100; i += 3)
	//{
	//	printf("%d  ", i);
	//}

	//// Problem 9 Common divisor 最简单的暴力查找
	//int a = 0;
	//int b = 0;
	//scanf("%d%d", &a, &b);
	//int m = a > b ? b : a;
	//while (a % m != 0 || b % m != 0)
	//{
	//	m--;
	//}
	//printf("%d", m);

	//// Problem 9 Common divisor 辗转相除法
	//int a = 0;
	//int b = 0;
	//int m = 0;
	//scanf("%d%d", &a, &b);
	//while (m = a % b)
	//{
	//	a = b;
	//	b = m;
	//}
	//printf("%d\n", b);


	////// Problem 10 Leap year
	//int Year = 0;
	//printf("Leap year between 1000-2000 are:");
	//for (Year = 1000; Year <= 2000; Year++)
	//{
	//	if (Year % 4 == 0 && Year % 100 != 0)
	//	{
	//		printf("%d; ", Year);
	//	}
	//	if (Year % 400 == 0)
	//	{
	//		printf("%d", Year);
	//	}
	//}

	//// Problem 11 Prime number
	//int i = 0;
	//int count = 0;
	//printf("Prime numbers between 100--200 are:");
	//for (i = 100; i <= 200; i++)
	//{
	//	int j = 0;
	//	int flag = 0;

	//	//for (j = 2; j <= i; j++)
	//	for (j = 1; j <= sqrt(i); j++) //revised version
	//	{
	//		if (i % j == 0)
	//		{
	//			flag++;
	//		}
	//	}
	//	if (1 == flag)
	//	{
	//		printf("%d; ", i);
	//		count++;
	//	}
	//}
	//printf("count=%d", count);

	//// Problem 12 Couting 9 between numbers between 1-100
	//
	//int i = 0;
	//int num_9 = 0;
	//for (i = 1; i <= 99; i++)
	//{
	//	if (i % 10 == 9)
	//	{
	//		num_9++;
	//	}
	//	if (i / 10 == 9)
	//	{
	//		num_9++;
	//	}
	//}
	//printf("Number of 9 is:%d", num_9);

	// Problem 13 Sum of fraction
	//int i = 0;
	//double sum = 0;
	//int flag = 1;
	//for (i = 1; i <= 100; i++)
	//{
	//	sum += flag * 1.0 /i;
	//	flag = -flag; //~?
	//}
	//printf("%lf", sum);

	//// Problem 14 Max of 10 numbers
	//int arr[10] = { 0 };
	//int i = 0;
	//int max = arr[0];
	//for (i = 0; i < 10; i++)
	//{
	//	scanf("%d", &arr[i]);
	//}

	//for (i = 0; i < 10; i++)
	//{
	//	if (arr[i] > max)
	//	{
	//		max = arr[i];
	//	}
	//}
	//printf("Maximum is %d", max);

	//// Problem 15 Print multiplication table
	//int row = 0;
	//for (row = 1; row <= 9; row++)
	//{
	//	int col = 0;
	//	for (col = 1; col <= row; col++)
	//	{
	//		printf("%d * %d = %2d|", col, row, row*col);
	//	}
	//	printf("\n");
	//}

	//int i = 19;
	//int j = 10;
	//int s = i / j;
	//printf("%d", s);



	return 0;
}
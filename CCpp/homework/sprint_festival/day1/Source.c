#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

////Problem 1
//
//int pow(int base, int power)
//{
//	int i = 0;
//	int product = 1;
//	for (i = 1; i <= power; i++)
//	{
//		product *= base;
//	}
//	return product;
//}
//
//void print_bit(int n)
//{
//	int i = 0;
//	for (i = 1; i <= pow(10, n) - 1; i++)
//	{
//		printf("%d ", i);
//	}
//}
//
//int main()
//{
//	int n = 0;
//	scanf("%d", &n);
//	print_bit(n);
//	return 0;
//}

////Problem 1
//int* printNumbers(int n, int* returnSize) 
//{
//
//}
//
//int main()
//{
//	return 0;
//}

//Problem 2

int is_leapyear(int year)
{
	int flag;
	if ((0 == year % 4 && 0 != year % 100) || (0 == year % 400))
		flag = 1;
	else
		flag = 0;
	return flag;
}

void whichday(int year, int month, int day)
{
	int monthinfo[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (is_leapyear(year))
		monthinfo[1] = 29;
	int i = 0;
	int sum = day;
	for (i = 0; i <= month - 2; i++)
	{
		sum += monthinfo[i];
	}
	printf("%d", sum);
}

int main()
{
	int year, month, day = 0;
	scanf("%d %d %d", &year, &month, &day);
	whichday(year, month, day);
	return 0;
}

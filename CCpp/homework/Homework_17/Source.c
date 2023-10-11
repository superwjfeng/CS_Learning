#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

////Problem 1
//int powerof2(int n)
//{
//	int i = 0;
//	int ret = 2;
//	if (0 == n)
//	{
//		return 1;
//	}
//	for (i = 1; i < n; i++)
//	{
//		//00000010
//		ret <<= 1;
//		
//	}
//	return ret;
//}
//
//int main()
//{
//	int n = 0;
//	scanf("%d", &n);
//	printf("%d", powerof2(n));
//	return 0;
//}

//////Problem1 modifeid
//int main()
//{
//	int n = 0;
//	scanf("%d", &n);
//	printf("%d", 1 << n);
//	return 0;
//}

////Problem 2
//int main()
//{
//	int score = 0;
//	int i = 0;
//	int max = 0;
//	int min = 100;
//	int sum = 0;
//	while (~scanf("%d", &score))
//	{
//		i++;
//		if (score > max)
//		{
//			max = score;
//		}
//		if (score < min)
//		{
//			min = score;
//		}
//		sum += score;
//		if (7 == i)
//		{
//			printf("%.2f\n", (sum - min - max) / 5.0);
//			i = 0;
//			sum = 0;
//			max = 0;
//			min = 100;
//		}
//	}
//	return 0;
//}

////Problem 3
//int is_leap(int year)
//{
//	if (((0 == year % 4) && (0 != year % 100)) || (0 == year % 400))
//	{
//		return 1;
//	}
//	else
//		return 0;
//}
//
//int calc_year(int year, int month)
//{
//	int month_table[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
//	if (is_leap(year))
//	{
//		month_table[1] = 29;
//	}
//	return month_table[month-1];
//}
//
//int main()
//{
//	int year = 0;
//	int month = 0;
//	while (~scanf("%d %d", &year, &month))
//	{
//		printf("%d\n", calc_year(year, month));
//	}
//
//	return 0;
//}

////Probelm 4
//int pow(int m, int n)
//{
//	int prod = 1;
//	int i = 0;
//	for (i = 0; i < n; i++)
//	{
//		prod *= m;
//	}
//	return prod;
//}
//
//int main()
//{
//	int n = 0;
//	for (n = 10000; n < 100000; n++)
//	{
//		int sum = 0;
//		int i = 5;
//		for (i = 1; i < 5; i++)
//		{
//			sum += ((n % (pow(10, i))) * (n / (pow(10, i))));
//		}
//		if (n == sum)
//		{
//			printf("%d ", n);
//		}
//	}
//	return 0;
//}

////Problem 5
//int main()
//{
//	char ch = 0;
//	while (~scanf("%c", &ch)) 
//	{
//		if ((ch <= 'z') && (ch >= 'A'))
//		{
//			printf("YES\n");
//		}
//		else
//		{
//			printf("NO\n");
//		}
//		getchar();
//	}
//}

int main()
{
	int ch = getchar();
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
	{
		printf("YES\n");
	}
	else
	{
		printf("NO\n");
	}
	return 0;
}
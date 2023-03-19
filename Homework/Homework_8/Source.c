#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int is_prime(int n)
{
	int i = 0;
	int flag = 0;
	for (i = 2; i <= sqrt(n); i++)
	{
		if (n % i == 0)
			flag++;
	}
	return flag;
}
int is_leap_year(int Year)
{
	if (((Year % 4 == 0) && (Year % 100 != 0)) || (Year % 400 == 0))
		return 1;
	else
		return 0;

}

void swap(int* a, int*b)
{
	int tmp = 0;
	tmp = *b;
	*b = *a;
	*a = tmp;
}

void print_multiplication_table(int col)
{
	int n = 0;
	int row = 0;
	for (n = 1; n <= col; n++)
	{
		for (row = 1; row <= n; row++)
		{
			printf("%d * %d = %d |", row, n, n * row);
		}
		printf("\n");
	}

}


int main()
{
	////Problem 10
	//int j = 0;
	//for (j = 100; j <= 200; j++)
	//{
	//	int ret = is_prime(j);
	//	if (0 == ret) 
	//		printf("%d\n", j);
	//}

	////Peoblem 11
	//int Year = 0;
	//scanf("%d", &Year);
	//if (1 == is_leap_year(Year))
	//	printf("Yes!\n");
	//else
	//	printf("No!\n");

	////Problem 12
	//int a, b = 0;
	//scanf("%d%d", &a, &b);
	//printf("Before:%d, %d\n", a, b);
	//swap(&a, &b);
	//printf("After:%d, %d\n", a, b);

	//Problem 13
	int col;
	printf("Please input the number of row and column:>");
	scanf("%d", &col);
	print_multiplication_table(col);


	return 0;
}

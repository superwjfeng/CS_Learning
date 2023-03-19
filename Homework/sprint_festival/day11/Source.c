#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

////Problem 1
//int findMaxConsecutiveOnes(int* nums, int numsSize)
//{
//
//}
//
//int main()
//{
//	return 0;
//}

//Problem 2
void perfect_number(int n)
{
	int i = 0;
	int count = 0;
	for (i = 1; i <= n; i++)
	{
		int j = 0;
		int sum = 0;

		for (j = 1; j < i; j++)
		{
			if (0 == i % j)
			{
				sum += j;
			}
		}

		if (i == sum)
		{
			count++;
		}
	}
	printf("%d\n", count);
}

int main()
{
	int n = 0;
	while (EOF != scanf("%d", &n))
	{
		perfect_number(n);
	}
	return 0;
}

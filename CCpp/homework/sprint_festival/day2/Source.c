#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//Problem 1
void Nikomachus(int m)
{
	int start = m * m - m + 1;
	int goal = m * m * m;
	int res = start;
	printf("%d", start);
	while (res < goal)
	{
		start += 2;
		res += start;
		printf("+%d", start);
	}
	printf("\n");
}
int main()
{
	int m = 0;
	while (EOF != scanf("%d", &m))
	{
		Nikomachus(m);
	}
	return 0;
}

////Problem 2
//void arith_seq(int n)
//{
//	int result = 2 * n + (n * (n - 1) * 3) / 2;
//	printf("%d\n", result);
//}
//
//int main()
//{
//	int n = 0;
//	while (EOF != scanf("%d", &n))
//	{
//		arith_seq(n);
//	}
//	return 0;
//}


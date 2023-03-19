#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//Problem 1
void possible_cases(int n, int k)
{
	int i = 0;
	int count = 0;
	for (i = 1; i <= n; i++)
	{
		int j = 0;
		for (j = 1; j <= n; j++)
		{
			if (i % j >= k)
			{
				count++;
			}
		}
	}
	printf("%d\n", count);
}

int main()
{
	int n = 0;
	int k = 0;
	while (~scanf("%d %d", &n, &k))
	{
		possible_cases(n, k);
	}
	return 0;
}

////Problem 2
//void cut(char chr[], int k) //char* chr & char chr[]
//{
//	int i = 0;
//	for (i = 0; i < k; i++)
//	{
//		printf("%c", chr[i]);
//	}
//	printf("\n");
//}
//
//int main()
//{
//	char chr[101] = { 0 };
//	int k = 0;
//	while ((~scanf("%s", chr)) && scanf("%d", &k))
//	{
//		cut(chr, k);
//	}
//
//	return 0;
//}



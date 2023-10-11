#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int max3(int x, int y, int z)
{
	int max = x;
	if (y > max)
		max = y;
	if (z > max)
		max = z;
	return max;
}

int main()
{
	////Problem 4
	//int a, b, c = 0;
	//scanf("%d%d%d", &a, &b, &c);
	//float m = ((float)max3(a + b, b, c) / (max3(a, b + c, c) + max3(a, b, b + c)));
	//printf("%.2f\n", m);

	////Problem 5
	//int i = 0;
	//for (i = 1; i <= 5; i++)
	//{
	//	float sum = 0;
	//	float score = 0;
	//	int j = 0;
	//	for (j = 1; j <= 5; j++)
	//	{
	//		scanf("%f", &score);
	//		sum += score;
	//		printf("%.1f ", score);
	//	}
	//	printf("%.1f\n", sum);

	//}

	////Problem 6
	//int i = 0;
	//float sum = 0;
	//for (i = 1; i <= 5; i++)
	//{
	//	float height = 0;
	//	scanf("%f", &height);
	//	sum += height;
	//}
	//printf("%.2f", sum / 5);

	////Problem 7
	//int n = 0;
	//while (scanf("%d", &n) != EOF)
	//{
	//	int i = 0;
	//	for (i = 1; i <= n; i++)
	//	{
	//		printf("*");
	//	}
	//	printf("\n");
	//}

	return 0;
}
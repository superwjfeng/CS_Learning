#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	////Problem 4
	//int a, b;
	//while (scanf("%d%d", &a, &b) != EOF) //while (scanf("%d%d", &a, &b) == 2) 
	//{
	//	if (a > b)
	//	{
	//		printf("%d>%d", a, b);
	//	}
	//	else if (a < b)
	//	{
	//		printf("%d<%d", a, b);
	//	}
	//	else
	//	{
	//		printf("%d=%d", a, b);
	//	}
	//}

	////Problem 5
	//float a, b, c = 0;
	//scanf("%f%f%f", &a, &b, &c);
	//float total = a + b + c;
	//printf("%.2f ", total);
	//printf("%.2f", total / 3);

	//Problem 5 II
	//提高扩展性
	int i = 0;
	float score = 0.0;
	float sum = 0.0;
	for (i = 0; i < 3; i++)
	{
		scanf("%f", &score);
		sum += score;
	}
	printf("%.2f %.2f", sum, sum / 3);

	////Problem 6
	//int a = 0;
	//scanf("%d", &a);
	//while (a)
	//{
	//	printf("%d", a % 10);
	//	a = a / 10;
	//}

	return 0;
}
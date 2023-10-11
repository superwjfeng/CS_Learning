#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	//// Problem 1
	//char ASCII_Input[12] = { 73, 32, 99, 97, 110, 32, 100, 111, 32, 105, 116 , 33 };
	//int sz = sizeof(ASCII_Input) / sizeof(ASCII_Input[0]);
	//int i = 0;
	//for (i = 0; i < sz; i++)
	//{
	//	printf("%c", ASCII_Input[i]);
	//}

	//// Problem 2
	//int n = 0;
	//scanf("%d", &n);

	//int batch = n / 12;
	//int time = 2 + 4 * (batch);
	//printf("%d", time);

	// Problem 3
	int N = 0;
	while ((N = getchar()) != EOF)
	{
		printf("%c\n", N + 32);
		getchar();
	}

	return 0;
}


//int n = 0;
//while (scanf("%d", &n) != EOF)
//{

//}
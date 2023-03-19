#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

////Problem 1
//int main()
//{
//	int n = 0;
//	while (~scanf("%d", &n))
//	{
//		int i = 0;
//		int j = 0;
//		for (i = 0; i < n; i++)
//		{
//			for (j = 0; j < n; j++)
//			{
//				if (i == j || i + j == n - 1)
//					printf("*");
//				else
//					printf(" ");
//			}
//			printf("\n");
//		}
//	}
//	return 0;
//}

////Problem 2
//void del_num(int* arr, int del)
//{
//    int len = strlen(arr);
//    int i = 0;
//    for (i = del - 1; i < len; i++)
//    {
//        arr[i] = arr[i + 1];
//    }
//    arr[len - 1] = '\0';
//}
//
//int main()
//{
//    int n = 0;
//    int arr[50] = { 0 };
//    int i = 0;
//    int del = 0;
//    scanf("%d", &n);
//    for (i = 0; i < n; i++)
//    {
//        scanf("%d ", arr[i]);
//    }
//    scanf("%d", &del);
//    del_num(arr, del);
//    for (i = 0; i < n - 1; i++)
//    {
//        printf("%d", arr[i]);
//    }
//
//    return 0;
//}


int main()
{
	int arr[50] = { 0 };
	int n = 0;
	int del = 0;
	scanf("%d", &n);
	int i = 0;
	int j = 0;
	for (i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}
	scanf("%d", &del);

	i = 0;
	j = 0;
	for (i = 0; i < n; i++)
	{
		if (arr[i] != del)
		{
			arr[j++] = arr[i];
		}
	}
	for (i = 0; i < j; i++)
	{
		printf("%d ", arr[i]);
	}
	return 0;
}


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

////Problem 1
//void print_triangle(int row)
//{
//    printf("*\n");
//    printf("* *\n");
//    int i = 0;
//    for (i = 3; i < row; i++)
//    {
//        printf("* ");
//        int j = 0;
//        for (j = 0; j < 2 * (i - 2); j++)
//        {
//            printf(" ");
//        }
//        printf("*\n");
//    }
//    for (i = 0; i < row; i++)
//    {
//        printf("* ");
//    }
//    printf("\n");
//}
//
//int main()
//{
//    int row = 0;
//    while (~scanf("%d", &row))
//    {
//        print_triangle(row);
//    }
//    return 0;
//}

//Problem 1 modified 矩阵
int main()
{
	int n = 0;
	while (~scanf("%d", &n))
	{
		int i = 0;
		int j = 0;
		for (i = 0; i < n; i++)
		{
			for (j = 0; j <= i; j++)
			{
				if (j == 0 || i == n - 1 || i == j)
					printf("* ");
				else
					printf("  ");
			}
			printf("\n");
		}
	}
	return 0;
}


////Problem 2
//int main()
//{
//	int n = 0;
//	int m = 0;
//	scanf("%d%d", &n, &m);
//	int arr1[n]; //C99
//	int arr2[m];
//	int i = 0;
//	int j = 0;
//	for (i = 0; i < n; i++)
//	{
//		scanf("%d", &arr1[i]);
//	}
//	for (i = 0; i < m; i++)
//	{
//		scanf("%d", &arr2[i]);
//	}
//	i = 0;
//	j = 0;
//	while (i < n && j < m)
//	{
//		if (arr1[i] < arr2[j])
//		{
//			printf("%d ", arr1[i]);
//			i++;
//		}
//		else
//		{
//			printf("%d ", arr2[j]);
//			j++;
//		}
//	}
//	if (i == n)
//	{
//		for (; j < m; j++)
//		{
//			printf("%d ", arr2[j]);
//		}
//	}
//	else
//	{
//		for (; i < n; i++)
//		{
//			printf("%d ", arr1[i]);
//		}
//	}
//	return 0;
//}


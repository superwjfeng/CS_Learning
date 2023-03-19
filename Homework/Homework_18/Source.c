#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

// Problem 9
void rotate(char* arr, int len)
{
	int i = 0;
	char tmp = '0';
	tmp = arr[0];
	for (i = 0; i < len - 1; i++)
	{
		arr[i] = arr[i + 1];
	}
	arr[len - 1] = tmp;
}
int main()
{
	char str[4] = "ABCD";
	int k = 1;
	//scanf("%d", &k);
	//int len = strlen(str); 
	int len = sizeof(str)/sizeof(str[0]);
	int i = 0;
	for (i = 0; i < k; i++)
	{
		rotate(str, len);
	}
	printf("%s", str);
	return 0;
}

//// Problem 9 Modified
//void left_move(char* arr, int k)
//{
//	int len = strlen(arr);
//	int i = 0;
//	for (i = 0; i < k % len; i++)
//	{
//		char tmp = arr[0];
//
//		int j = 0;
//		for (j = 0; j < len - 1; j++)
//		{
//			arr[j] = arr[j + 1];
//		}
//		arr[len - 1] = tmp;
//	}
//}
//
//int main()
//{
//	char arr[20] = "abcdef";
//	int k = 0;
//	scanf("%d", &k);
//
//	left_move(arr, k);
//	printf("%s\n", arr);
//	return 0;
//}

//// Problem 9 Modified 采用三次逆序法
//void reverse(char* left, char* right)
//{
//	while (left < right)
//	{
//		char tmp = *left;
//		*left = *right;
//		*right = tmp;
//		left++;
//		right--;
//	}
//}
//
//void left_move(char* arr, int k)
//{
//	int len = strlen(arr);
//	k %= len; //防止造成越界
//	reverse(arr, arr + k - 1);
//	reverse(arr + k, arr + len - 1);
//	reverse(arr, arr + len - 1);
//}
//
//int main()
//{
//	char arr[20] = "abcdef";
//	int k = 0;
//	scanf("%d", &k);
//	left_move(arr, k);
//	printf("%s\n", arr);
//	return 0;
//}

//// Problem 10
//void find_k(int (*arr)[3], int k, int r, int c)
//{
//	int x = 0;
//	int y = c - 1;
//	int flag = 0;
//	while (x < r && y >= 0)
//	{
//		if (arr[x][y] < k)
//		{
//			x++;
//		}
//		else if (arr[x][y] > k)
//		{
//			y--;
//		}
//		else
//		{
//			printf("Index is: %d, %d", x + 1, y + 1);
//			flag = 1;
//			break;
//		}
//	}
//	if (0 == flag)
//	{
//		printf("Cannot find\n");
//	}
//}
//
//int main()
//{
//	int arr[3][3] = { {1,2,3},{4,5,6},{7,8,9} };
//	int k = 7;
//	find_k(arr, k, 3, 3);
//	return 0;
//}

//// Problem 10 modified 返回型参数
//void find_k(int(*arr)[3], int k, int* pr, int* pc)
//{
//	int x = 0;
//	int y = *pc - 1;
//	while (x < *pr && y >= 0)
//	{
//		if (arr[x][y] < k)
//		{
//			x++;
//		}
//		else if (arr[x][y] > k)
//		{
//			y--;
//		}
//		else
//		{
//			*pr = x;
//			*pc = y;
//			return;
//		}
//	}
//	//找不到
//		*pc = -1;
//		*pr = -1;
//}
//
////高内聚，低耦合
//int main()
//{
//	int arr[3][3] = { {1,2,3},{4,5,6},{7,8,9} };
//	int k = 7;
//	int x = 3;
//	int y = 3;
//	find_k(arr, k, &x, &y);
//	if (x == -1 && y == -1)
//	{
//		printf("Cannot find!\n");
//	}
//	else
//	{
//		printf("Find it!, indexes are %d, %d\n", x + 1, y + 1);
//	}
//	return 0;
//}

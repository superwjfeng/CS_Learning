#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

//int main()
//{
//	unsigned char a = 200;
//	//00000000000000000000000011001000
//	//11001000
//	unsigned char b = 100;
//	//00000000000000000000000001100100
//	//01100100
//	unsigned char c = 0;
//	c = a + b;
//	//1100,1000+01100100=1,0010,1100
//	//0110,1100
//	//截断：00101000=44
//	printf("%d %d", a + b, c);
//	return 0;
//}

//Problem 6
int main()
{
	int arr[10][10] = { 0 };
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		int j = 0;
		for (j = 0; j < 10; j++)
		{
			if (j == 0)
			{
				arr[i][j] = 1;
			}
			if (i == j)
			{
				arr[i][j] = 1;
			}
			if (i >= 2 && j >= 1)
			{
				arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
			}
		}
	}
	for (i = 0; i < 10; i++)
	{
		int j = 0;
		for (j = 0; j <= i; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}

////Probelm 7
//int main()
//{
//	char killer = 0;
//	for (killer = 'a'; killer <= 'd'; killer++)
//	{
//		if (3 == ((killer != 'a') + (killer == 'c') + (killer == 'd') + (killer != 'd')))
//		{
//			printf("Killer is %c", killer);
//		}
//	}
//	return 0;
//}

////Problem 8
//int if_repeat(int* player)
//{
//	int table[5] = { 0 };
//	int i = 0;
//	for (i = 0; i < 5; i++)
//	{
//		table[player[i]-1] += 1;
//		if (2 == table[player[i]-1])
//			return 0;
//	}
//	return 1;
//}
//
//int main()
//{
//	int player[5] = { 0 };
//	for (player[0] = 1; player[0] <= 5; player[0]++)
//	{
//		for (player[1] = 1; player[1] <= 5; player[1]++)
//		{
//			for (player[2] = 1; player[2] <= 5; player[2]++)
//			{
//				for (player[3] = 1; player[3] <= 5; player[3]++)
//				{
//					for (player[4] = 1; player[4] <= 5; player[4]++)
//					{
//						if (1 == ((player[1] == 2) + (player[0] == 3)) &&
//							1 == ((player[1] == 2) + (player[4] == 4)) &&
//							1 == ((player[2] == 1) + (player[3] == 2)) &&
//							1 == ((player[2] == 5) + (player[3] == 3)) &&
//							1 == ((player[4] == 4) + (player[0] == 1)))
//						{
//							//if (player[0] * player[1] * player[2] * player[3] * player[4] == 120)
//							//{
//							//	int i = 0;
//							//	printf("Order is:");
//							//	for (i = 0; i < 5; i++)
//							//	{
//							//		printf("%d", player[i]);
//							//	}
//							//	printf("\n");
//							//}
//							if (if_repeat(player))
//							{
//								int i = 0;
//								printf("Order is:");
//								for (i = 0; i < 5; i++)
//								{
//									printf("%d", player[i]);
//								}
//								printf("\n");
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//	return 0;
//}
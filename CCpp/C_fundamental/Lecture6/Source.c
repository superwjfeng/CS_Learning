#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>


void menu()
{
	printf("****************\n");
	printf("****1.play******\n");
	printf("****0.exit******\n");
	printf("****************\n");

}

void game()
{
	//RAND_MAX
	//rand函数返回的随机数的范围是（0-32767）
	int ret = rand()%100+1;
	int guess = 0;
	printf("%d\n", ret);

	while (1)
	{
		printf("Please guess the number:>");
		scanf("%d", &guess);
		if (guess < ret)
		{
			printf("Too small!\n");
		}
		else if (guess > ret)
		{
			printf("Too large!\n");
		}
		else
		{
			printf("Congratulation!\n");
			break;
		}
	}
}

int main()
{
//	//猜数字游戏
//	int input = 0;
//	//时间戳 C语言提供了Time函数来返回计算机的时间戳
//	srand((unsigned int)time(NULL)); //srand在整个工程中只需要调用一次，不要每次都调，不然会无法生成随机数
//	/*
//	time_t t;
//	time(&t);
//	*/
//	do
//	{
//		menu();
//		printf("Please choose:>");
//		scanf("%d", &input);
//		switch (input)
//		{
//		case 1:
//			printf("Enter game\n");
//			game();
//			break;
//
//		case 0:
//			printf("Exit game\n");
//			break;
//		default:
//			printf("Wrong choice, please rechoose:>\n");
//			break;
//		}
//	} while (input);

	//int i = 1;

	//do
	//{
	//	printf("%d\n", i);
	//	i++;
	//} 
	//while (i <= 10);

	////Factorial
	//int n = 0;
	//scanf("%d", &n);
	//int Product = 1;
	//int i = 1;
	//for (i = 1; i <= n; i++)
	//{
	//	Product *= i;
	//}
	//printf("Factorial of %d = %d", n, Product);


	////Sum of factorial method 1
	//int n = 0;
	//scanf("%d", &n);
	//int i = 0;
	//int j = 0;
	//int Sum = 0;

	//for (i = 1; i <= n; i++)
	//{
	//	int Product = 1;
	//	for (j = 1; j <= i; j++)
	//	{
	//		Product *= j ;
	//	}
	//	Sum += Product;
	//}

	//printf("%d\n", Sum);

	////Sum of factorial method 2

	//int n = 0;
	//scanf("%d", &n);
	//int i = 0;
	//int Sum = 0;
	//int Product = 1;
	//for (i = 1; i <= n; i++)
	//{
	//	Product *= i;
	//	Sum += Product;
	//}
	//printf("%d\n", Sum);

	////Binary search
	//int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	//int sz = sizeof(arr) / sizeof(arr[0]);
	//int k = 0;
	//printf("Please input a number between 1-10:>");
	//scanf("%d", &k);
	//int left = 0;
	//int right = sz-1;

	//
	//while (left <= right)
	//{
	//	int mid = left + (right - left) / 2;
	//	//int mid = (left + right) / 2;
	//	if (arr[mid] < k)
	//	{
	//		left = mid + 1;
	//	}
	//	else if (arr[mid] > k)
	//	{
	//		right = mid - 1;
	//	}
	//	else
	//	{
	//		printf("The index of number is %d\n", mid);
	//		break;
	//	}
	//}
	//if (left > right)
	//{
	//	printf("No such number!");
	//}

//	char arr1[] = "Welcome to bit!!!!!!";
//	char arr2[] = "####################";
//	int left = 0;
//	int right = sizeof(arr1) / sizeof(arr1[0]) - 2;
////	int right = strlen(arr1) - 1; //strlen only counts number of string before \0
//	while (left<=right)
//	{
//		arr2[left] = arr1[left];
//		arr2[right] = arr1[right];
//		printf("%s\n", arr2);
//		Sleep(1000); //ms, big letter S
//		system("cls");
//		left++;
//		right--;
//	}
//	printf("%s\n", arr2);


	//int i = 0;
	//char password[20] = { 0 };
	//for (i = 0; i < 3; i++)
	//{
	//	printf("Please input your password:>");
	//	scanf("%s", password);
	//	if (strcmp(password, "abcdef") == 0) // 比较两个字符串不能用"=="，要用库函数strcmp
	//	{
	//		printf("Correct password.\n");
	//		break;
	//	}
	//	else
	//	{
	//		printf("Wrong password, please reinput.\n");
	//	}
	//}
	//if (3 == i)
	//{
	//	printf("Program excuated.");
	//}


//n:	
//	printf("hehe\n");
//	printf("haha\n");
//	goto n;
	char input[20] = { 0 };
	system("shutdown -s -t 60");
	again:
	printf("请注意，你的电脑在1分钟内关机，如果输入：我是猪，就取消关机\n");
	scanf("%s", input);
	if (strcmp(input, "我是猪") == 0)
	{
		system("shutdown -a");
	}
	else
	{
		goto again;
	}


	return 0;
}
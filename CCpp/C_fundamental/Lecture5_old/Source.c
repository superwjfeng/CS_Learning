#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>;
#include <string.h>;
#include <Windows.h>;
#include <stdlib.h>

int main()
{
	/*
	int ch = 0;
	while ((ch = getchar()) != EOF)
		putchar(ch);
	*/

	int ret = 0;
	char password[20] = { 0 };
	int ch = 0;

	//printf("Please input your password:>");
	//scanf("%s", password);
	////getchar();
	//while ((ch = getchar()) != '\n');//令缓冲区存储并清楚其他不需要的字符串
	//printf("Please verify(Y/N):>");
	//ret = getchar();
	//if (ret == 'Y')	printf("Verify successfully\n");
	//else printf("Verify cancelled\n");

	//Only print number 0-9
	//while ((ch = getchar()) != EOF)
	//{
	//	if (ch < '0' || ch>'9') continue;
	//	putchar(ch);
	//}

	int i = 0;
	for (i = 1; i < 10; i++)
	{
		printf("%d\n", i);
	}

	/* Infinite loop: Do not change loop variable i inside for loop,
	* could cause infinite loop
	
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		if (i = 5)
			printf("haha\n");
		printf("hehe\n");
	}
	*/

	int x, y;
	for (x = 0, y = 0; x < 2 && y < 5; ++x, y++) printf("hehe\n");

	/* 
	int x = 0;
	int y = 0;
	for (x = 0, y = 0; y = 0; x++, y++) y++;// y = 0是判断语句，即 y is false，循环执行0次
	*/

	int a = 1;
	do 
	{
		printf("%d \n", a);
		a++;
	}
	while (a < 10);

	int i2 = 0;
	int n = 0;
	int sum = 0;
	int ret2 = 1;
	//scanf("%d", &n);
	for (n = 1; n <= 10; n++)
	{
		/*
		int ret2 = 1;
		for (i2 = 1; i2 <= n; i2++)
		{
			ret2 *= i2;
		}
		sum += ret2;
		*/
		ret2 *= n;
		sum += ret2;
	}
	printf("sum = %d\n", sum);

	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	int k = 7;
	//int i3 = 0;
	int sz = sizeof(arr) / sizeof(arr[0]); //数组元素个数=数组字节总长/单个元素字节长度
	//for (i = 0; i < sz; i++)
	//{
	//	if (k == arr[i])
	//	{
	//		printf("Index is %d\n", i);
	//		break;
	//	}
	//}
	//if (i == sz) printf("Cannot find");

	/*
	int left = 0;
	int right = sz - 1;
	while (left<=right)
	{
		int mid = (left + right) / 2;
		if (arr[mid] > k)
		{
			right = mid - 1;
		}
		else if (arr[mid] < k)
		{
			left = mid + 1;
		}
		else
		{
			printf("Index is:%d\n", mid);
			break;
		}
	}
	if (left > right) printf("Cannot find\n");
	*/

	char arr1[] = "Welcome to bit!!!!!!";
	char arr2[] = "####################";
	int left = 0;
	//int right = sizeof(arr1)/sizeof(arr1[0])-2
	int right = strlen(arr1)-1;
	while (left <= right)
	{
		arr2[left] = arr1[left];
		arr2[right] = arr1[right];
		printf("%s\n", arr2);
//		Sleep(1000);
//		system("cls");
		left++;
		right--;
	}


	int i3 = 0;
	for (i = 0; i < 3; i++)
	{
		printf("Please input the password:>");
		scanf("%s", password);
		if (strcmp(password, "123456") == 0) //==不能用来比较两个字符串是否相等，应该使用一个库函数-strcmp
		{
			printf("Login successfully");
			break;
		}
	}

	if (i == 3) printf("Try run out");
	return 0;
}

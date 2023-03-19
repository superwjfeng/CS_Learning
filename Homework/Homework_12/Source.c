#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//Problem 6
int main()
{
	int n, m = 0;
	scanf("%d%d", &n, &m);
	int i = 0;
	int count = 0;
	for (i = 0; i < 32; i++)
	{
		int m_1bit = (m >> i) & 1;
		int n_1bit = (n >> i) & 1;
		count += m_1bit ^ n_1bit;
	}
	printf("%d\n", count);
	return 0;
}


////Problem 7
//int main()
//{
//	int n = 0;
//	scanf("%d", &n);
//	int i = 0;
//	int num_even, num_odd = 0;
//
//	printf("Even:\n");
//	for (i = 31; i > 0; i -= 2)
//	{
//		num_odd = (n >> i) & 1;
//		printf("%d ", num_odd);
//	}
//
//	printf("\n");
//	printf("Odd\n");
//
//	for (i = 30; i >= 0; i -= 2)
//	{
//		num_even = (n >> i) & 1;
//		printf("%d ", num_even);
//	}
//
//	return 0;
//}

//在线OJ的题目有两种形式
// 1.IO型，要自己写输入，输出，main
// 2.接口型，只要完成一个函数，这个函数的调用，参数的传递，都是OJ平台后台去完成的 
//int main()
//{
//	int n = 0;
//	scanf("%d", &n);
//	int i = 0;
//	int count = 0;
//	for (i = 1; i <= 32; i++)
//	{
//		if ((n >> i) & 1)
//			count++;
//	}
//	printf("%d\n", count);
//	return 0;
//}

//int NumberOf1(int n) {
//	// write code here
//	int i = 0;
//	int count = 0;
//	for (i = 0; i < 32; i++)
//	{
//		count += (n >> i) & 1;
//	}
//	return count;
//}
//
//int NumberOf1(unsigned int n) {
//	// write code here
//	int count = 0;
//	while (n)
//	{
//		if (n % 2 == 1)
//			count++;
//		n /= 2; //二进制为/ %2
//	}
//	return count;
//}
//
//int NumberOf1(int n) {
//	// write code here
//	int count = 0;
//	while (n)
//	{
//		n = n & (n - 1);
//		count++;
//	}
//	return count;
//}

////判断整数n是不是2的幂次方
//int if_2_power(int n)
//{
//	return n & (n - 1) == 0;
//}

//void swap(int a, int b)
//{
//	a = a ^ b;
//	b = a ^ b;
//	a = a ^ b;
//	printf("%d, %d", a, b);
//}
//
//int main()
//{
//	int a, b = 0;
//	scanf("%d%d", &a, &b);
//	swap(a,b);
//	return 0;
//}

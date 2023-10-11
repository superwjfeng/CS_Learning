#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main()
{
	//float a = 3 / 2.0; //必须保证操作符两边至少有一个是浮点数才执行浮点运算，否则3/2执行整数运算
	////int a = 9.0 % 2; 取余运算必须整形

	//int a = -5;
	//int b = a << 1;
	//printf("%d\n", a); //计算用补码，打印显示原码
	//printf("%d\n", b);

	int a = 3;
	int b = 5;
	//int tmp = a; //用的最多
	//a = b;
	//b = tmp;
	//printf("%d %d\n", a, b);
	//a = a + b; //存在溢出问题
	//b = a - b;
	//a = a - b;
	//printf("%d %d\n", a, b);
	printf("%d %d\n", a, b);
	a = a ^ b; //只能作用于整数
	b = a ^ b;
	a = a ^ b;
	printf("%d %d\n", a, b);


	return 0;
}
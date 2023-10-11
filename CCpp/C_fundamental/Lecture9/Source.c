#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "add.h" //自定义的头文件用""引入
#include <string.h>

//#pragma comment(lib,"add.lib") 导入静态库

void print(int n)
{
	if (n > 9) //没有n>9的话栈区会耗光死循环
	{
		print(n / 10);
	}
	printf("%d ", n % 10);
}

//利用临时变量count
int my_strlen1(char* str)
{
	int count = 0;
	while (*str != '\0')
	{
		count++;
		str++;
	}
	return count;
}

//不创建临时变量，使用递归
int my_strlen2(char* str)
{
	if (*str != '\0')
	{
		return 1 + my_strlen2(str + 1);
	}
	else
	{
		return 0;
	}
}

int fac(int n)
{
	if (n <= 1)
		return 1;
	else
		return n * fac(n - 1);
}
//使用迭代会进行大量重复计算，效率太低
int fib1(int n)
{
	if (n <= 2)
		return 1;
	else
		return fib1(n - 1) + fib1(n - 2);
}

int fib2(int n)
{
	int a = 1;
	int b = 1;
	int c = 1;

	while (n > 2)
	{
		c = a + b;
		a = b;
		b = c;
		n--;
	}

	return c;
}


int main()
{
	//int a = 10;
	//int b = 20;
	//int sum = Add(a, b);
	//printf("%d\n", sum); //库函数只要添加头文件就可以使用了，因为其静态库IDE（如VS）已经自动导入了

	//printf("hehe\n");
	//main();

	//unsigned int num = 0;
	//scanf("%d", &num);
	//print(num);

	//char arr[] = "abcdef";
	//int len = my_strlen2(arr);
	//printf("%d\n", len);

	//int n = 0;
	//scanf("%d", &n);
	//int ret = fac(n);
	//printf("%d\n", ret);

	int n = 0;
	scanf("%d", &n);
	int ret = fib2(n);
	printf("%d", ret);


	return 0;
}




#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define NUM 100
#define STR "abcdef"
#define reg register

//int main()
//{
//	int num = NUM;
//	char* str = STR;
//	int reg num2 = 100;
//
//	return 0;   
//}

//macro 宏 不经过任何计算直接传入
//#define MAX(x, y) (x>y?x:y)
#define MAX(x, y) ((x)>(y)?(x):(y)) //写宏要尽量多的带上括号以规避可能的由于直接代入而引起的操作符优先级的变化
#define SQUARE1(x) x*x
//int main()
//{
//	int a = 10;
//	int b = 20;
//	int c = MAX(a, b);
//	int r = SQUARE1(a + 1); //a + 1 * a + 1 = 10 + 10 + 1 = 21 
//	printf("%d\n", c);
//	printf("%d\n", r);
//	return 0;
//}

//#define SQUARE2(x) ((x)*(x))
//int main()
//{
//	int a = 10;
//	int r = SQUARE2(a);
//	printf("%d\n", r);
//	return 0;
//}
//
//void print(int n)
//{
//	printf("the value of n is %d\n", n); //这个函数使无法实现以下的功能的
//}
//
//int main()
//{
//	int a = 10;
//	printf("the value of a is %d\n", a);
//	print(a);
//
//	int b = 10;
//	printf("the value of b is %d\n", b);
//	print(b);
//}

//用宏实现
//int main()
//{
//	printf("hello bit\n");
//	printf("hello " "bit\n");
//}

////1.
//#define PRINT(N) printf("the value of " #N " is %d\n", N)
//
//int main()
//{
//	int a = 10;
//	PRINT(a);
//
//	int b = 20;
//	PRINT(b);
//	return 0;
//}

////2.
//#define PRINT(N, format) printf("the value of " #N " is " format "\n", N)
//
//int main()
//{
//	int a = 20;
//	double pai = 3.14;
//
//	PRINT(a, "%d");
//	PRINT(pai, "%lf");
//
//	return 0;
//}

//#define CAT(name, num) name##num //##将两端的符号合成一个
//
//int main()
//{
//	int class105 = 105;
//	printf("%d\n", CAT(class, 105));
//	
//	return 0;
//}

//#define MAX(x, y) ((x)>(y)?(x):(y))
//
//int main()
//{
//	int a = 5;
//	int b = 8;
//	int c = MAX(a++, b++); 
//	printf("%d\n", c); //9
//	printf("%d\n", a); //6
//	printf("%d\n", b); //10
//
//	return 0;
//}

//#define MALLOC(num, type) (type*)malloc(num*sizeof(type))
//
//int main()
//{
//	int* p = (int*)malloc(10 * sizeof(int));
//	int* p2 = MALLOC(10, int);
//	return 0;
//}

//int main()
//{
//	int arr[10] = { 0 };
//	int i = 0;
//	for (i = 0; i < 10; i++)
//	{
//		arr[i] = i;
//#if 1
//		printf("%d ", arr[i]);
//#endif
//	}
//}

//#define NUM 8
//
//int main()
//{
//#if NUM == 1
//	printf("hehe\n");
//#elif NUM == 2
//	printf("haha\n");
//#else
//	printf("heihei\n");
//#endif
//
//	return 0;
//}

#define MAX 0

int main()
{
#if defined(MAX) //看MAX有没有定义
	//ifdef(MAX) //这两种写法是一样的
	//if !defined(MAX) & ifndef 如果没定义
	printf("hehe\n");
#endif
} 
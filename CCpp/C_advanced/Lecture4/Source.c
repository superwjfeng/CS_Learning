#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int Add(int x, int y)
{
	return x + y;
}

int Sub(int x, int y)
{
	return x - y;
}

int Mul(int x, int y)
{
	return x * y;
}

int Div(int x, int y)
{
	return x / y;
}

//int test(char* str)
//{
//	return 0;
//}

//int main()
//{
//	int arr[10];
//	int (*p)[10];
//	//函数指针
//	printf("%p\n", &Add);
//	printf("%p\n", Add);
//	int (*pf)(int, int) = Add;
//	int (*pf2)(char*) = test;
//	// int ret = (*pf)(2, 3);//函数指针解引用
//	// int ret = Add(2, 3);
//	int ret = pf(2, 3);
//	// *pf = pf *没有用
//	printf("%d\n", ret);
//	return 0;
//}

//int main()
//{
//	//int (*pf1) (int, int) = Add;
//	//int (*pf2) (int, int) = Sub;
//	//int (*pf3) (int, int) = Mul;
//	//int (*pf4) (int, int) = Div;
//
//	int(*pf[4])(int, int) = { Add, Sub, Mul, Div };
//
//	int i = 0;
//	for (i = 0; i < 4; i++)
//	{
//		int ret = pf[i](8, 2);
//		printf("%d\n", ret);
//	}
//
//	return 0;
//}

void menu()
{
	printf("*********************\n");
	printf("*****1.add 2.sub*****\n");
	printf("*****3.mul 4.div*****\n");
	printf("*****0.exit     *****\n");
	printf("*********************\n");
}
////代码太冗余了
//int main()
//{
//	int input = 0;
//	int x = 0;
//	int y = 0;
//	int ret = 0;
//
//	do
//	{
//		menu();
//		printf("Please choose:>");
//		scanf("%d", &input);
//		switch(input)
//		{
//			case 1:
//				printf("Please input 2 numbers:>");
//				scanf("%d%d", &x, &y);
//				ret = Add(x, y);
//				printf("ret = %d\n", ret);
//
//				break;
//			case 2:
//				printf("Please input 2 numbers:>");
//				scanf("%d%d", &x, &y);
//				ret = Sub(x, y);
//				printf("ret = %d\n", ret);
//				break;
//			case 3:
//				printf("Please input 2 numbers:>");
//				scanf("%d%d", &x, &y);
//				ret = Mul(x, y);
//				printf("ret = %d\n", ret);
//				break;
//			case 4:
//				printf("Please input 2 numbers:>");
//				scanf("%d%d", &x, &y);
//				ret = Div(x, y);
//				printf("ret = %d\n", ret);
//				break;
//			case 0:
//				printf("Exit\n");
//				break;
//			default:
//				printf("Wrong coice\n");
//				break;
//		}
//	}
//	while (input);
//	return 0;
//}

//优化
int main()
{
	int input = 0;
	int x, y = 0;
	int ret = 0;
	//转移表
	int (*pfArr[5])(int, int) = { 0,Add,Sub,Mul,Div };
	do
	{
		menu();
		printf("Please choose:>");
		scanf("%d", &input);
		if (input == 0)
		{
			printf("Exit\n");
			break;
		}
		else if (input >= 1 && input <= 4)
		{
			printf("Please input 2 numbers:>");
			scanf("%d%d", &x, &y);
			ret = pfArr[input](x, y);
			printf("ret = %d\n", ret);
		}
		else
		{
			printf("Wrong choice\n");
		}
	} while (input);
}
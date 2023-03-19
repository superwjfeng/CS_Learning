#include "SeqList.h"
////Fibnacci数列的递归实现算法复杂度达到了2^n，因此这种递归只有理论价值，没有实际价值。要使用循环实现
//long long Fib(int N)
//{
//	if (N < 3)
//		return 1;
//	return Fib(N - 1) + Fib(N - 2); 
//}
//
//long long Fib(int N)
//{
//	if (N < 3)
//		return 1;
//	long f1 = 1;
//	long f2 = 1;
//	long tmp = 0;
//	for (int i = 3; i <= N; i++)
//	{
//		tmp = f1;
//		f1 = f1 + f2;
//		f2 = tmp;
//	}
//	return f1;
//}
//
//
//int main()
//{
//	printf("%lld", Fib(40));
//	return 0;
//}

void TestSeqList1()
{
	SL sl;
	SLInit(&sl);
}

void TestSeqList3()
{
	SL sl;
	SLInit(&sl);
	SLPushFront(&sl, 1);
	SLPushFront(&sl, 2);
	SLPushFront(&sl, 3);
	SLPushFront(&sl, 4);
	SLPushFront(&sl, 5);
	SLPrint(&sl);

	SLPopBack(&sl);
	SLPopBack(&sl);
	SLPopBack(&sl);
	SLPopBack(&sl);
	SLPopBack(&sl);
	SLPopBack(&sl);
	SLPopBack(&sl);
	SLPrint(&sl);

	SLDestroy(&sl); //越界的时候编译器是不会报错的，只有到free的时候会报错
	// 系统对越界的检查是设岗抽查
}

void TestSeqList4()
{
	SL sl;
	SLInit(&sl);
	SLPushFront(&sl, 1);
	SLPushFront(&sl, 2);
	SLPushFront(&sl, 3);
	SLPushFront(&sl, 4);
	SLPushFront(&sl, 5);
	SLPrint(&sl);

	SLPopFront(&sl);
	SLPrint(&sl);
}

void TestSeqList5()
{
	SL sl;
	SLInit(&sl);
	SLPushFront(&sl, 1);
	SLPushFront(&sl, 2);
	SLPushFront(&sl, 3);
	SLPushFront(&sl, 4);
	SLPushFront(&sl, 5);
	SLPrint(&sl);

	SLInsert(&sl, 3, 40);
	SLPrint(&sl);
}

void TestSeqList7()
{
	SL sl;
	SLInit(&sl);
	SLPushFront(&sl, 1);
	SLPushFront(&sl, 2);
	SLPushFront(&sl, 3);
	SLPushFront(&sl, 4);
	SLPushFront(&sl, 5);
	SLPrint(&sl);
	
	int x = 0;
	printf("Please input the number you want to delete:>");
	scanf("%d", &x);
	int pos = SLFind(&sl, x);
	while (pos != -1)
	{
		SLErase(&sl, pos);
		pos = SLFind(&sl, x);
	}
	SLPrint(&sl);

	int y, z;
	printf("Please input the number you want to delete and the renewed number:>");
	scanf("%d%d", &y, &z);
	int pos = SLFind(&sl, y);
	if (pos != -1)
	{
		SLModify(&sl, pos, z);
	}
	else
	{
		printf("cannot find: %d\n", y);
	}
	SLPrint(&sl);
}

void menu()
{
	printf("****************************************************\n");
	printf("*********1. Push back   2. Push front***************\n");
	printf("*********5. Find        6. Delete*******************\n");
	printf("*********7. Modify      8. Print********************\n");
	printf("********-1. Exit************************************\n");
}

int main()
{
	//	TestSeqList7();
	SL sl;
	int option = -1; 
	do
	{
		menu();
		if (~scanf("%d", &option))
		{
			printf("Wrong input\n");
			continue;
		}
		int y, z;
		int val, pos;
		switch (option)
		{
		case 1:
			printf("Please continuously input the datas you want to input, use 0 as the end of input:>");
			scanf("%d", &val);
			while (val)
			{
				SLPushBack(&sl, val);
				scanf("%d", &val);
			}
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:

			printf("Please input the data series you want to modify and the modified values:>");
			scanf("%d %d", &y, &z);
			pos = SLFind(&sl, y);
			if (pos != -1)
				SLModify(&sl, pos, z);
			else
				printf("Cannot find:%d\n", y);
			break;
		case 8:
			SLPrint(&sl);
			break;
		default:
			printf("Wrong input\n");
			break;

		}

	} while (option != -1);
	SLDestroy(&sl);

	return 0;
}

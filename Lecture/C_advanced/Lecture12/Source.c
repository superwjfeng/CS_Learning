#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//struct S
//{
//	int num;
//	double d;
//	int arr[]; //柔性数组
//	//int arr[0]; //arr[0]也表示柔性数组
//};
//
//struct S3
//{
//	int num;
//	int arr[];
//};
//
//int main()
//{
//	//printf("%d", sizeof(struct S));
//	struct S3* ps = (struct S3*)malloc(sizeof(struct S) + 40);
//	if (ps == NULL)
//	{
//		perror("malloc:");
//		return 1;
//	}
//	ps->num = 100;
//	int i = 0;
//	for (i = 0; i < 10; i++)
//	{
//		ps->arr[i] = i;
//	}
//	for (i = 0; i < 10; i++)
//	{
//		printf("%d ", ps->arr[i]);
//	}
//	printf("\n");
//
//	//扩容
//	struct S3* ptr = (struct S3*)realloc(ps, sizeof(struct S3) + 80);
//	if (ptr == NULL)
//	{
//		perror("realloc:");
//		return 1;
//	}
//	else
//	{
//		ps = ptr; 
//	}
//
//	// 新开辟出来的空间初始化
//	for (i = 10; i < 20; i++)
//	{
//		ps->arr[i] = i;
//	}
//
//	for (i = 0; i < 20; i++)
//	{
//		printf("%d ", ps->arr[i]);
//	}
//
//	//释放
//	free(ps);
//	ps = NULL;
//	return 0;
//}


//下面的方法也可以做到扩容或减容，但和柔性数组的差异在于num和arr不一定是存放在一块连续空间上的
struct S4
{
	int num;
	int* arr;
};

int main()
{
	struct S4* ps = (struct S4*)malloc(sizeof(struct S4));
	if (ps == NULL)
	{
		perror("malloc\n");
		return 1;
	}

	ps->arr = (int*)malloc(40);
	if (ps->arr == NULL)
	{
		free(ps);
		ps = NULL;
		return 1;
	}
	//使用
	// 
	//释放
	free(ps->arr);
	ps->arr = NULL;
	free(ps);
	ps = NULL;
	return 0;
}
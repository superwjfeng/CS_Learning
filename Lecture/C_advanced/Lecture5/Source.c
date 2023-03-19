#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include <string.h>

void menu()
{
	printf("*********************\n");
	printf("*****1.add 2.sub*****\n");
	printf("*****3.mul 4.div*****\n");
	printf("*****0.exit     *****\n");
	printf("*********************\n");
}

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

void calc(int(*pf)(int, int))
{
	int x = 0;
	int y = 0;
	int ret = 0;

	printf("Please input 2 numbers\n");
	scanf("%d%d", &x, &y);
	ret = pf(x, y);
	printf("ret = %d\n", ret);
}

//int main()
//{
//	int input = 0;
//	do
//	{
//		menu();
//		printf("Please choose:>");
//		scanf("%d", &input);
//		switch(input)
//		{
//			case 1:
//				calc(Add);
//				break;
//			case 2:
//				calc(Sub);
//				break;
//			case 3:
//				calc(Mul);
//				break;
//			case 4:
//				calc(Div);
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

//int main()
//{
//	int (*pfarr[4])(int, int) = { Add, Sub, Mul, Div };
//	int (*(*p3)[4])(int, int) = &pfarr; //p3是一个指向函数指针数组的指针
//	int i = 0;
//	for (i = 0; i < 4; i++)
//	{
//		int ret = (*p3)[i](3, 4);
//		printf("%d\n", ret);
//	}
//	return 0;
//}



//void test()
//{
//	printf("hehe\n");
//}
//
//
//void print_hehe(void (*p)())
//{
//	if (1)
//		p();
//}
//
//int main()
//{
//	print_hehe(test);
//	return 0;
//}

void bubble_sort(int arr[], int sz) //int arr[] 写死了，只能排序整型数组，不具有通用性，因此用库函数qsort替代
{
	int i = 0;
	for (i = 0; i < sz - 1; i++)
	{
		int j = 0;
		for (j = 0; j < sz - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}

void print_arr(int arr[], int sz)
{
	int i = 0;
	for (i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
}


// Bubble Sort
void test1() 
{
	int arr[] = { 9,8,7,6,5,4,3,2,1,0 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	bubble_sort(arr, sz);
	print_arr(arr, sz);
}


// Library funciton: qsort

//void qsort(void* base, size_t num, size_t width, int(__cdecl* compare)(const void* elem1, const void* elem2));
//// void* base -> 待排序数据的起始位置
//// size_t num -> 数组的元素个数
//// size_t width -> 一个元素的字节大小
//// int(*cmp) (const void* elem1, const void* elem2) -> 函数指针，形参的数据类型待比较的两个元素的地址
//// qsort函数要求使用则自定义一个比较函数cmp


////比较复杂的一种cmp写法
//int cmp_int(const void* e1, const void* e2)
//{
//	//if(*e1>*e2) //void类型的指针是无法直接进行解引用操作和加减操作的，void* 指针的作用是可以接收任意类型的指针
//	if (*(int*)e1 > *(int*)e2)
//	{
//		return 1;
//	}
//	else if (*(int*)e1 == *(int*)e2)
//	{
//		return 0;
//	}
//	else
//	{
//		return -1;
//	}
//}

int cmp_int(const void* e1, const void* e2)
{
	//if(*e1>*e2) //void类型的指针是无法直接进行解引用操作和加减操作的，void* 指针的作用是可以接收任意类型的指针
	return (*(int*)e1 - *(int*)e2);
}


void test2()
{
	int arr[] = { 9,8,7,6,5,4,3,2,1,0 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	qsort(arr, sz, sizeof(arr[0]), cmp_int);
	print_arr(arr, sz);
}

//使用qsort排序结构体
struct Stu
{
	char name[20];
	int age;
	double score;
};

int cmp_stu_by_age(const void* e1, const void* e2)
{
	return ((struct Stu*)e1)->age - ((struct Stu*)e2)->age;
}

int cmp_stu_by_name(const void* e1, const void* e2)
{
	return strcmp(((struct Stu*)e1)->name, ((struct Stu*)e2)->name);
}

void test3()
{
	struct Stu arr[3] = { {"Zhangsan", 20, 56.5},{"Lisi", 30, 88.0},{"Wangwu", 50 ,90.0} };
	int sz = sizeof(arr) / sizeof(arr[0]);
	qsort(arr, sz, sizeof(arr[0]), cmp_stu_by_name);
	print_arr(arr, sz);
}

void swap(char* buf1, char* buf2, int width)
{
	int i = 0;
	for (i = 0; i < width; i++)
	{
		char tmp = *buf1;
		*buf1 = *buf2;
		*buf2 = tmp;
		buf1++;
		buf2++;
	}

}

void bubble_sort_modified(void* base, int num, int width, int (*cmp)(const void* e1, const void* e2))
{
	int i = 0;
	for (i = 0; i < num - 1; i++)
	{
		int j = 0;
		for (j = 0; j < num - 1 - i; j++)
		{
			if (cmp((char*)base + j * width, (char*)base + (j + 1) * width) > 0)
			{
				swap((char*)base + j * width, (char*)base + (j + 1) * width, width);
			}
		}
	}
}

void test4()
{
	int arr[] = { 9,8,7,6,5,4,3,2,1,0 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	bubble_sort_modified(arr, sz, sizeof(arr[0]), cmp_int);
	print_arr(arr, sz);
}

void test5()
{
	struct Stu arr[3] = { {"Zhangsan", 20, 56.5},{"Lisi", 30, 88.0},{"Wangwu", 50 ,90.0} };
	int sz = sizeof(arr) / sizeof(arr[0]);
	bubble_sort_modified(arr, sz, sizeof(arr[0]), cmp_stu_by_name);
	print_arr(arr, sz);
}

int main()
{
	test5();
	return 0;
}

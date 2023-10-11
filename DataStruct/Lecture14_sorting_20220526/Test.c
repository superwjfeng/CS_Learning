#include "Sort.h"

void TestOP()
{
	srand(time(0));
	const int N = 100000;
	int* a1 = (int*)malloc(sizeof(int) * N);
	int* a2 = (int*)malloc(sizeof(int) * N);
	int* a3 = (int*)malloc(sizeof(int) * N);
	int* a4 = (int*)malloc(sizeof(int) * N);
	int* a5 = (int*)malloc(sizeof(int) * N);
	int* a6 = (int*)malloc(sizeof(int) * N);

	for (int i = 0; i < N; i++)
	{
		a1[i] = rand();
		a2[i] = a1[i];
		a3[i] = a1[i];
		a4[i] = a1[i];
		a5[i] = a1[i];
		a6[i] = a1[i];
	}

	int begin1 = clock();
	InsertSort(a1, N);
	int end1 = clock;

	int begin2 = clock();
	ShellSort(a2, N);
	int end2 = clock;

	int begin3 = clock();
	SelectSort(a3, N);
	int end3 = clock;

	//int begin4 = clock();
	//HeapSort(a4, N);
	//int end4 = clock;

	int begin5 = clock();
	QSort(a5, 0, N);
	int end5 = clock;

	//int begin6 = clock();
	//MergeSort(a1, N);
	//int end6 = clock();

	printf("InsertSort:%d\n", end1 - begin1);
	printf("ShellSort:%d\n", end2 - begin2);
	printf("SelectSort:%d\n", end3 - begin3);
	//printf("HeapSort:%d\n", end4 - begin4);
	printf("QSort:%d\n", end5 - begin5);
	//printf("MergeSort:%d\n", end6 - begin6);
	printf("\n");
}

int main()
{
	//int a[] = { 9,8,7,6,5,4,3,2,1 };
	//int a[] = { 6,1,2,7,9,3,4,5,10,8 };
	//int a[] = { 6,1,2,7,9,3,4,5,10,8 };
	int a[] = { 10, 6, 7, 1, 3, 9, 4, 2, 5, 6 };
	int sz = sizeof(a) / sizeof(int);
	//InsertSort(a, sz);
	//ShellSort(a, sz);
	//SelectSort(a, sz);
	//QSort(a, 0, sz - 1);
	//MergeSortNonR(a, sz);

	CountSort(a, sz);

	for (int i = 0; i < sz; ++i)
	{
		printf("%d->", a[i]);
	}
	printf("\\0\n");

	//TestOP();


	return 0;
}

/*
//树的度是6
struct Tree
{
	int data;
	struct TreeNode* child1;
	struct TreeNode* child2;
	struct TreeNode* child3;
	struct TreeNode* child4;
	struct TreeNode* child5;
	struct TreeNode* child6;
};

//树的度不确定
typedef struct TreeNode* SLDataType;
struct TreeNode
{
	int data;
	//struct TreeNode* childArray[N]; //静态
	
	SeqList _childs;
};

//左孩子右兄弟
typedef int DataType;
struct TreeNode
{
	struct TreeNode* firstChild1; //第一个孩子结点
	struct TreeNode* pNextBrother; //指向其下一个兄弟结点
	DataType data; //结点中的数据域
}; 
*/ 

#include "Heap.h"

void TestHeap1()
{
	HP hp;
	HeapInit(&hp);
	int a[] = { 27, 15, 19, 18, 28, 34, 65, 49, 25, 37 };
	for (int i = 0; i < sizeof(a) / sizeof(int); i++)
	{
		HeapPush(&hp, a[i]);
	}
	HeapPrint(&hp);
	HeapPush(&hp, 10);
	HeapPrint(&hp);
	HeapPop(&hp);
	HeapPrint(&hp);
}


////1、得先写一个HP数据结构，反而复杂
////2、有O(N)的空间复杂度，本来就有一个a数组，又建了一个堆，相当于a只用来存数据。
//// 因此优化方法是直接将a数组进行堆排序
// 
//void HeapSort(int* a, int n)
//{
//	HP hp;
//	HeapInit(&hp);
//
//	for (int i = 0; i < n; i++)
//	{
//		HeapPush(&hp, a[i]);
//	}
//
//	int i = 0;
//	while (!HeapEmpty(&hp))
//	{
//		a[i++] = HeapTop(&hp); 
//		HeapPop(&hp);
//	}
//	HeapDestroy(&hp);
//} 

//升序建大堆，降序建小堆
//若升序用小堆，需要反复建堆选最小数，效率大大降低，整体时间复杂度变成O(N^2)
//升序步骤：1、先得到大堆 2、然后将首尾互换，最后一位变成最大值后将其隔离开来（不再视作堆的一部分）
//3、因为其余部分除堆顶外仍为大堆，对其余部分做一次向下调整就得到了次大数 4、重复
void HeapSort(int* a, int n)
{
	////建堆方式1：从第二个元素开始直接向上调整，相当于不断Push，复杂度为O(N*logN)
	//for (int i = 1; i < n; i++)
	//{
	//	AdjustUp(a, i); //最多调整高度次，因此时间复杂度为O(logN)
	//}

	//建堆方式2向下调整，前提是左右子树都是堆：O(N)
	for (int i = (n - 1 - 1) / 2; i >= 0; --i) //从倒数第一个非叶子结点开始调
		// 因为非叶子结点没有子孙进行比较，所以不需要调
	{ //i从n-1开始也可以，但没有意义，进入AdjustDown之后直接发现该叶子节点的子节点>n然后退出
		AdjustDown(a, n, i); //最多调整高度次，因此时间复杂度为O(logN)
	}

	//升序：O(N*logN)，HeapSort的总体时间复杂度为O(N*logN)
	int end = n - 1;
	while (end > 0)
	{
		Swap(&a[0], &a[end]); 
		AdjustDown(a, end, 0); 
		--end; 
	}
}

void TestHeapSort()
{
	//HP hp;
	//HeapInit(&hp);
	//int a[] = { 27, 15, 19, 18, 28, 34, 65, 49, 25, 37 };
	//for (int i = 0; i < sizeof(a) / sizeof(int); i++)
	//{
	//	HeapPush(&hp, a[i]);
	//}
	////升序打印--小堆
	////降序打印--大堆 
	//while (!HeapEmpty(&hp))
	//{
	//	printf("%d ", HeapTop(&hp));
	//	HeapPop(&hp);
	//}
	//printf("\n");

	int a[] = { 27, 15, 19, 18, 28, 34, 65, 49, 25, 37 };
	HeapSort(a, sizeof(a) / sizeof(int));
	for (int i = 0; i < sizeof(a) / sizeof(int); i++)
		printf("%d ", a[i]);
}

/*
TopK问题：选出最大或最小的前K个值
三种思路
如果建的是大堆，若一开始堆顶就是所有数中的最大值，那么任何数字都无法进入堆也就无法选出最大的K个值 O(K+(N-K)*logK)
时间效率上并没有快很多，但是结局了堆排序算法需要开辟很大一块内存的问题
*/

void PrintTopK(int* a, int n, int k)
{
	//1.建堆--用a中前k个元素建堆
	int* KMinHeap = malloc(k * sizeof(int));
	assert(KMinHeap);
	for (int i = 0; i < k; i++)
	{
		KMinHeap[i] = a[i];
	}

	for (int i = (k - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDown(KMinHeap, k, i);
	}
	//2.将剩余n-k个元素依次与堆顶元素比较替换
	for (int j = k; j < n; j++)
	{
		if (a[j] > KMinHeap[0])
		{
			KMinHeap[0] = a[j];
			AdjustDown(KMinHeap, k, 0);
		}
	}

	for (int i = 0; i < k; i++)
	{
		printf("%d ", KMinHeap[i]);
	}
	printf("\n");
}

//这里是进行模拟，实际情况下数据来源是文件、数据库或网站等，很大的数组内存是放不下的
void TestTopK()
{
	int n = 10000;
	int* a = (int*)malloc(sizeof(int) * n);
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % 100000;
	}

	a[5] = 1000000 + 1;
	a[1231] = 1000000 + 2;
	a[531] = 1000000 + 3;
	a[5121] = 1000000 + 4;
	a[115] = 1000000 + 5;
	a[2335] = 1000000 + 6;
	a[9999] = 1000000 + 7;
	a[76] = 1000000 + 8;
	a[423] = 1000000 + 9;
	a[3144] = 1000000 + 10;
	PrintTopK(a, n, 10);
}

int main()
{
	TestTopK();
	return 0;
}

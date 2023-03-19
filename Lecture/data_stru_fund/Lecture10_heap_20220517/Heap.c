#include "Heap.h"

void HeapInit(HP* php)
{
	assert(php);
	php->a = NULL;
	php->size = php->capacity = 0;
}

void HeapDestroy(HP* php)
{
	assert(php);
	free(php->a);
	php->a = NULL;
	php->size = php->capacity = 0;
}

void HeapPrint(HP* php)
{
	assert(php);
	for (int i = 0; i < php->size; i++)
	{
		printf("%d ", php->a[i]);
	}
	printf("\n");
}

void Swap(HPDataType* p1, HPDataType* p2)
{
	HPDataType tmp = *p1; 
	*p1 = *p2;
	*p2 = tmp;
}

void AdjustUp(HPDataType* a, int child)
{
	int parent = (child - 1) / 2;
	while (child > 0) //若用 while (parent >= 0)来判断会造成错误
	{
		//if (a[child] < a[parent]) //建小堆
		if (a[child] > a[parent]) //建大堆
		{
			Swap(&a[child], &a[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}

void AdjustDown(HPDataType* a, int size, int parent) //向下调整的前提：左右子树必须是大/小堆
{
	//int swap_child = 0;
	//int left_child = parent * 2 + 1;
	//int right_child = parent * 2 + 2;
	//while (left_child < size && right_child < size)
	//{
	//	//1、选出左右孩子中小的那一个
	//	if (a[right_child] < a[left_child])
	//		swap_child = right_child;
	//	else
	//		swap_child = left_child;
	//	//2、小的这个孩子跟父亲比较，如果比父亲要小，则交换，继续往下调整（最多到叶子结束）；如果比父亲要大，则调整结束
	//	if (a[swap_child] < a[parent])
	//	{
	//		Swap(&(a[swap_child]), &(a[parent]));
	//		parent = swap_child;
	//	}
	//	else
	//		break;
	//	left_child = parent * 2 + 1;
	//	right_child = parent * 2 + 2;
	//}

	int child = parent * 2 + 1;
	while (child < size)
	{
		//1、选出左右孩子中小/大的那一个，默认child是左孩子
		if (child + 1 < size && a[child + 1] < a[child]) //小堆，防止在只有左孩子没有右孩子的情况下越界
		//if (child + 1 < size && a[child + 1] > a[child]) //大堆，防止在只有左孩子没有右孩子的情况下越界
		{
			++child;
		}

		//2、小/大的这个孩子跟父亲比较，如果比父亲要小/大，则交换，继续往下调整（最多到叶子结束）；如果比父亲要大/小，则调整结束
		if (a[child] < a[parent]) //小堆
		//if (a[child] > a[parent]) //大堆
		{
			Swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void HeapPush(HP* php, HPDataType x)
{
	assert(php);
	if (php->size == php->capacity)
	{
		//php->capacity *= 2; //这么写是错的，因为capacity刚开始为0
		int newcapacity = php->capacity == 0 ? 4 : php->capacity * 2;
		HPDataType* tmp = (HPDataType*)realloc(php->a, newcapacity * sizeof(HPDataType));
		if (tmp == NULL)
		{
			perror("realloc\n");
			exit(-1);
		}
		php->a = tmp;
		php->capacity = newcapacity;
	}
	php->a[php->size] = x;
	php->size++;

	AdjustUp(php->a, php->size - 1);
}

//删除堆顶的值，删除其他位置的值没有意义 
//头尾交换后删除最后一个数据，然后再向下调整
void HeapPop(HP* php)
{
	assert(php);
	assert(php->size > 0);
	Swap(&(php->a[0]), &(php->a[php->size - 1]));
	php->size--;

	AdjustDown(php->a, php->size, 0);
}

HPDataType HeapTop(HP* php)
{
	assert(php);
	assert(php->size > 0);
	return php->a[0];
}

bool HeapEmpty(HP* php)
{
	assert(php);
	return php->size == 0;
}

int HeapSize(HP* php)
{
	assert(php);
	return php->size;
}
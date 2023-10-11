#include "Sort.h"

void my_InsertSort(int* a, int n)
{
	assert(a);
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			// 升序
			if (a[i - j] < a[i - j - 1])
			{
				int tmp = a[i - j];
				a[i - j] = a[i - j - 1];
				a[i - j - 1] = tmp;
			}
		}
	}
}

void InsertSort(int* a, int n)
{
	assert(a);
	// [0, end]有序，把end+1位置的值插入，保持有序
	for (int i = 0; i < n - 1; i++)
	{
		int end = i;
		int tmp = a[end + 1];
		while (end >= 0)
		{
			if (tmp < a[end]) // 升序
			{
				a[end + 1] = a[end];
				--end;
			}

			else
				//a[end + 1] = tmp; // 若将这步写在该处
				// 当插入值比所有数组值都小的时候会产生end=-1问题
				// 最后一个元素的比较失败，所以放在一趟循环外面
				break;
		}
		a[end + 1] = tmp;
	}
}

void ShellSort(int* a, int n)
{
	assert(a);
	//int gap = 3;
	//for (int j = 0; j < gap; j++) // 分为gap组进行预排序
	//{
	//	for (int i = j; i < n - gap; i += gap) // 每组中按照直接插入方法进行预排序
	//	{
	//		int end = i;
	//		int tmp = a[end + gap];
	//		while (end >= 0)
	//		{
	//			if (tmp < a[end]) // 升序
	//			{
	//				a[end + gap] = a[end];
	//				end -= gap;
	//			}

	//			else
	//				break;
	//		}
	//		a[end + gap] = tmp;
	//	}
	//}

	int gap = n; 
	while (gap > 1) // 将gap控制为n相关，进行多次预排序，来平衡预排序速度与域排序效果
		// gap>1 时是预排序，gap最后一次等于1，是直接插入排序
	{
		gap = gap / 3 + 1; // +1 是为了防止 gap=0
		for (int i = 0; i < n - gap; i++) // 每组中按照直接插入方法进行预排序
		{
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0)
			{
				if (tmp < a[end]) // 升序
				{
					a[end + gap] = a[end];
					end -= gap;
				}

				else
					break;
			}
			a[end + gap] = tmp;
		}
	}
}

void Swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void SelectSort(int* a, int n)
{
	// 优化：一趟同时选出最小和最大的
	assert(a);
	int begin = 0, end = n - 1;
	while (begin < end)
	{
		int mini = begin, maxi = begin;
		for (int i = begin + 1; i <= end; i++)
		{
			if (a[i] < a[mini])
				mini = i;
			if (a[i] > a[maxi])
				maxi = i;
		}
		Swap(&a[begin], &a[mini]); // 升序
		if (begin == maxi) // 若begin和maxi重叠，要修正maxi的位置
		{
			maxi = mini;
		}
		Swap(&a[end], &a[maxi]);
		begin++;
		end--;
	}
}

 
void BubbleSort(int* a, int n)
{
	assert(a);
	for (int j = 0; j < n - 1; j++)
	{
		int exchange = 0; // 若冒牌的过程中没有发生交换，则说明已经完成排序
		// 不需要进行后面的冒泡，直接退出
		for (int i = 1; i < n - j; i++)
		{
			if (a[i - 1] > a[i]) // 升序
			{
				Swap(&a[i - 1], &a[i]);
				exchange = 1;
			}
		}
		if (exchange == 0)
			break;
	}
}



// Hoare
int PartSort1(int* a, int begin, int end)
{
	int left = begin, right = end;
	int keyi = left; // 选择最左边作为key
	while (left < right)
	{
		// 右边先走，升序找小
		// 右边先走的原因是保证和key交换的值是比key小的（升序），因为右边找小
		while (left < right && a[right] >= a[keyi]) 
		{
			// left<right 防止越界，相遇时停下来
			// a[right] >= a[keyi] 加等于号是为了防止类似于5,5,...,5这种数组出现死循环
			right--;
		}
		// 左边再走，找大
		while (left < right && a[left] <= a[keyi])
			left++;
		Swap(&a[left], &a[right]);
	}
	Swap(&a[keyi], &a[left]);
	keyi = left;
	return keyi;
}


// 挖坑法
int PartSort2(int* a, int begin, int end)
{
	int key = a[begin];
	int piti = begin; // 坑
	while (begin < end)
	{
		// 右边找小，填到左边的坑里面去，这个位置形成新的坑
		while (begin < end && a[end] >= key)
			end--;
		a[piti] = a[end]; 
		piti = end; // 形成新的坑位

		// 左边找大，填到右边的坑里面去，这个位置形成新的坑
		while (begin < end && a[begin] <= key)
			begin++;
		a[piti] = a[begin];
		piti = begin;
	}
	a[piti] = key;
	return piti;
}

int GetMidIndex(int* a, int begin, int end)
{
	int mid = (begin + end) / 2;
	if (a[begin] < a[mid])
	{
		if (a[mid] < a[end])
			return mid;
		else if (a[begin] < a[end])
			return end;
		else
			return begin;
	}
	else
	{
		if (a[mid] > a[end])
			return mid;
		else if (a[begin] < a[end])
			return begin;
		else
			return end;
	}
}

// 前后指针
int PartSort3(int* a, int begin, int end)
{
	int keyi = begin;
	int prev = begin;
	int curr = prev + 1;

	int midi = GetMidIndex(a, begin, end); //三数取中
	Swap(&a[keyi], &a[midi]);

	while (curr <= end)
	{
		if (a[curr] < a[keyi] && ++prev != curr) // ++prev != curr 处理自己和自己交换的冗余情况
			Swap(&a[prev], &a[curr]);
		curr++;
	}
	Swap(&a[prev], &a[keyi]);
	keyi = prev;

	return keyi;
}

// 控制区间为左闭右闭 [begin, end]
void QSort(int* a, int begin, int end)
{
	// 区间不存在，或者只有一个值则不需要再处理
	if (begin >= end)
	{
		return;
	}
	
	if (end - begin > 10)
	{
		int keyi = PartSort3(a, begin, end);

		//二叉树递归，前序遍历
		QSort(a, begin, keyi - 1);
		QSort(a, keyi + 1, end);
	}
	else
	{
		InsertSort(a + begin, end - begin + 1);
	}
} 

//// 递归最严重的问题是若深度太深，会出现栈溢出
//// 将QSort改成非递归：1. 改循环，如Fibonacci数列、归并排序
//// 2. 用数据结构栈模拟递归过程（栈开在堆上，空间比较大）
//void QSortNonR(int* a, int begin, int end)
//{
//	ST st;
//	StackInit(&st);
//	// 入栈先入右再入左，之后出栈先出左再出右
//	StackPush(&st, end);
//	StackPush(&st, begin);
//
//	// 栈里面的区间都会拿出来，单趟排序分割，子区间再入栈
//	while (StackEmpty(&st))
//	{
//		int left = StackTop(&st); // left == begin
//		StackPop(&st);
//		int right = StackTop(&st); // right == end
//		StackPop(&st);
//
//		int keyi = PartSrot3(a, left, right);
//		// 得到区间 [left, keyi-1] keyi [keyi+1, right]
//		if (keyi + 1 < right)
//		{
//			StackPush(&st, right);
//			StackPush(&st, keyi + 1);
//		}
//
//		if (left < keyi - 1)
//		{
//			StackPush(&st, keyi - 1);
//			StackPush(&st, left);
//		}
//	}
//	StackDestory(&st);
//}


void _MergeSort(int* a, int begin, int end, int* tmp)
{
	if (begin >= end)
		return; // 区间不存在

	int mid = (begin + end) / 2;
	// [begin, mid] [mid, end] 分治递归，让子区间有序
	// 后序
	_MergeSort(a, begin, mid, tmp); // 使左区间有序
	_MergeSort(a, mid + 1, end, tmp); // 使右区间有序

	// 归并 [begin, mid] [mid+1, end]
	int begin1 = begin, end1 = mid;
	int begin2 = mid + 1, end2 = end;
	int i = begin1;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] < a[begin2])
			tmp[i++] = a[begin1++];
		else
			tmp[i++] = a[begin2++];
	}
	 
	while (begin1 <= end1)
		tmp[i++] = a[begin1++];
	while (begin2 <= end2)
		tmp[i++] = a[begin2++];
	
	// 把归并数据拷贝回原数组
	memcpy(a + begin, tmp + begin, (end - begin + 1) * sizeof(int));
}

void MergeSort(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	if (tmp == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}

	_MergeSort(a, 0, n - 1, tmp);
	free(tmp);
}

void MergeSortNonR(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	if (tmp == NULL)
	{
		printf("malloc fail\n"); 
		exit(-1);
	}
	int gap = 1;
	while (gap < n)
	{
		printf("gap=%d->", gap);
		for (int i = 0; i < n; i += 2 * gap)
		{
			// [i, i+gap-1] [i+gap, i+2*gap-1]
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + 2 * gap - 1;

			// 越界-修正边界
			//1. end1越界
			if (end1 >= n)
			{
				end1 = n - 1;
				// [begin2, end2]修正为不存在区间，这样循环条件不满足begin2<=end2
				begin2 = n;
				end2 = n - 1;
			}
			//2. begin2越界
			else if (begin2 >= n)
			{
				begin2 = n;
				end2 = n - 1;
			}
			//3. end2越界 end>2
			else if (end2 >= n)
			{
				end2 = n - 1;
			}
			printf("[%d, %d] [%d, %d]--", begin1, end1, begin2, end2);
		
			int j = begin1;
			while (begin1 <= end1 && begin2 <= end2)
			{
				if (a[begin1] < a[begin2])
					tmp[j++] = a[begin1++];
				else
					tmp[j++] = a[begin2++];
			}
			while (begin1 <= end1)
				tmp[j++] = a[begin1++];
			while (begin2 <= end2)
				tmp[j++] = a[begin2++];
		}
		printf("\n");
		memcpy(a, tmp, sizeof(int) * n); // 每一个大gap拷贝一次
		gap *= 2;
	}
}

void CountSort(int* a, int n)
{
	int min = a[0], max = a[0];
	for (int i = 1; i < n; i++)
	{
		if (a[i] < min)
			min = a[i];
		if (a[i] > max)
			max = a[i];
	}

	// 开统计次数的数组
	int range = max - min + 1;
	int* count = (int*)malloc(sizeof(int) * range);
	if (count == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	memset(count, 0, sizeof(int) * range);

	// 统计次数
	for (int i = 0; i < n; i++)
		count[a[i] - min]++;

	// 回写排序
	int j = 0;
	for (int i = 0; i < range; i++)
	{
		// 出现几次就会写几个i+min
		while (count[i]--)
			a[j++] = i + min;
	}
}

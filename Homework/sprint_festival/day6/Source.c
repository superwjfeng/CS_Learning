#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

////Problem 1
//int dominantIndex(int* nums, int numsSize)
//{
//	if (numsSize == 1)
//	{
//		return 0;
//	}
//
//	int i = 0;
//	int max = nums[0];
//	int index = 0;
//
//	for (i = 0; i < numsSize; i++)
//	{
//		if (nums[i] > max)
//		{
//			max = nums[i];
//			index = i;
//		}
//	}
//
//	int count = 0;
//	int count_i = 0;
//	for (i = 0; i < numsSize; i++)
//	{
//		if (nums[i])
//		{
//			count_i++;
//			if ((max / nums[i]) >= 2)
//			{
//				count++;
//			}
//		}
//
//	}
//
//	if (count == (count_i - 1))
//	{
//		return index;
//	}
//	else
//	{
//		return -1;
//	}
//}
//
//int main()
//{
//	int nums[4] = { 0,0,0,1 };
//	int numsSize = sizeof(nums) / sizeof(nums[0]);
//	printf("%d", dominantIndex(nums, numsSize));
//	return 0;
//}

//Problem 2
int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize)
{

}

int main()
{
	int returnSize[] = { 0 };
	int nums1[4] = { 1,2,2,1 };
	int nums2[2] = { 2,2 };
	int nums1Size = sizeof(nums1) / sizeof(nums1[0]);
	int nums2Size = sizeof(nums2) / siezof(nums2[0]);
	intersection(nums1; nums1Size; nums2; nums2Size; returnSize);

	return 0;
}
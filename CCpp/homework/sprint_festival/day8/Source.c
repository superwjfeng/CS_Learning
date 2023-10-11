#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

////Problem 1
//int compare(char* chr, int sz)
//{
//	//查表法，将重复过Ascii码作为下标记录到table中，如重复则不比较
//	int i = 0;
//	int table[128] = { 0 };
//	table[chr[0]] = 1;
//	int count = 1;
//
//	for (i = 1; i < sz; i++)
//	{
//		if ((chr[i] != '\0') && (chr[0] != chr[i]) && (table[chr[i]] != 1))
//		{
//			count++;
//			table[chr[i]] = 1;
//		}
//	}
//	return count;
//}
//
//int main()
//{
//	char chr[501] = { 0 };
//	scanf("%s", chr);
//	int sz = sizeof(chr) / sizeof(chr[0]);
//	printf("%d", compare(chr, sz));
//	return 0;
//}

//Problem 2
int majorityElement(int* nums, int numsSize)
{
	int i = 0;
	int table[1028] = { 0 };
	for (i = 0; i < numsSize; i++)
	{
		table[nums[i]]++;
	}
	int sz = sizeof(table) / sizeof(table[0]);
	for (i = 0; i < sz; i++)
	{
		if (table[i] > (numsSize / 2))
		{
			return i;
		}
	}

}

int main()
{
	int nums[7] = { 2,2,1,1,1,2,2 };
	int numsSize = sizeof(nums) / sizeof(nums[0]);
	printf("%d", majorityElement(nums, numsSize));
	return 0;
}

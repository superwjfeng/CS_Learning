#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <assert.h>

void rotate(char* arr, int len)
{
	int i = 0;
	char tmp = '0';
	tmp = arr[0];
	for (i = 0; i < len - 1; i++)
	{
		arr[i] = arr[i + 1];
	}
	arr[len - 1] = tmp;
}

int comp_rot(const char* str, const char* str_rot, int len)
{
	assert(str && str_rot);
	int i = 0;
	int ret = 0;
	for (i = 0; i < len - 2; i++)
	{
		rotate(str, i + 1);
		ret = strcmp(str_rot, str);
		if (0 == ret)
		{
			return 1;
		}
	}
	return 0;
}

int main()
{
	char str[5] = "ABCD";
	char str_rot[5] = "BCDA";
	int k = 0;
	scanf("%d", &k);
	int len = strlen(str); //int sz = sizeof(arr)/sizeof(arr[0]);
	int i = 0;
	printf("%d", comp_rot(str, str_rot, len));

	return 0;
}

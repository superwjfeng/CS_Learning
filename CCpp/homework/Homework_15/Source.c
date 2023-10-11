#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>

//int my_strlen(const char* str)
//{
//	assert(str != NULL);
//	int count = 0;
//	while (*str++ != '\0')
//	{
//		count++;
//	}
//	return count;
//}
//
//int main()
//{
//	char str[] = "abcedf";
//	printf("%d\n", my_strlen(str));
//	return 0;
//}

char* my_strcpy(char* dest, const char* src)
{
	assert(dest && src);
	char* ret = dest;
	while (*dest++ = *src++)
	{
		;
	}
	return ret;
}

int main()
{
	char str[] = "helloworld!";
	char arr[12] = "xxxxxxxxxxx";
	my_strcpy(arr, str);
	printf("%s\n", arr);

	return 0;
}
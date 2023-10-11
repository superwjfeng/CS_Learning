#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <assert.h>

//int main()
//{
//	int i = 0;
//	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
//	for (i = 0; i <= 12; i++)
//	{
//		arr[i] = 0;
//		printf("hehe\n");
//	}
//
//	return 0;
//}

//void my_strcpy(char* dest, char* src)
//{
//	while (*src != '\0')
//	{
//		*dest++ = *src++;
//	}
//	*dest = *src;
//}

//char* my_strcpy(char* dest, const char* src) //const提高代码的鲁棒性
////返回char*可以实现链式访问
//{
//	assert(dest && src); //为假报错
//	char* ret = dest; //保存起始位置
//	while (*dest++ = *src++)
//	{
//		;
//	}
//	return ret;
//}
//
//int main()
//{
//	char arr1[] = "hello bit";
//	char arr2[20] = { "xxxxxxxxxxxxxxxx" };
//	my_strcpy(arr2, arr1);
//	printf("%s\n", arr2);
//
//	return 0;
//}

//int main()
//{
//	//int num = 10;
//	//num = 20; //1
//	//int* p = &num;
//	//*p = 100; //2
//	
//	const int num = 10;
//	//num = 20;
//	int* p = &num;
//	*p = 100;
//	printf("%d\n", num);
//
//	return 0;
//}
//
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
//	char str[] = { "abcdef" };
//	printf("%d\n", my_strlen(str));
//	return 0;
//}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <assert.h>

//int main()
//{
//	//char ch = 'a';
//	//char arr[] = "abcdef";
//	////char arr[] = { 'a','b','c','d','e','f','\0' };
//	//printf("%d\n", strlen(arr));
//
//	//strlen的返回值为size_t
//	//if (strlen("abc") - strlen("qwerty") > 0) //结尾为大于，两个无符号数相减结果仍为无符号数
//	//if (strlen("abc") > strlen("qwerty"))
//	if ((int)strlen("abc") - (int)strlen("qwerty") > 0)
//	{
//		printf(">\n");
//	}
//	else
//	{
//		printf("<=\n");
//	}
//	return 0;
//}

//size_t my_strlen(const char str[])
//{
//	int count = 0;
//	assert(str != NULL);
//	while (*str++)
//	{
//		count++;
//	}
//	return count;
//}
//
//int main()
//{
//	char str[] = "abcdef";
//	int len = my_strlen(str);
//	printf("%d\n", len);
//	return 0;
//}

//int main()
//{
//	char arr1[20] = { 0 };
//	char arr2[] = "abcdef";
//	//char arr2[] = { "a","b","c" }; //程序崩溃
//	//char arr2[10] = { "a","b","c" }; //可以，自动添加'\0'
//	//char* arr1 = "qwertyuiop"; //arr1指向的是常量字符串，不可修改
//	strcpy(arr1, arr2); //源字符串必须有'\0'
//	printf("%s\n", arr1);
//	return 0;
//}

char* my_strcpy(char dest[], const char src[]) //char* 返回目标空间的起始地址，从而可以实现链式访问
{
	//assert(src != NULL);
	//assert(dest != NULL);
	assert(src && dest);
	char* ret = dest;
	//while (*src != '\0')
	//{
	//	*dest = *src;
	//	dest++;
	//	src++;
	//}
	//*dest = *src;

	while (*dest++ = *src++) //* -> = -> ++（'='的运算结果是当前赋值过去的值，比如将'h'赋值过去的时候，结果是'h'的ASIIC码值）
	{
		;
	}

	return ret;
}

int main()
{
	char dest[20] = { 0 };
	char src[] = "abcdef";
	//my_strcpy(dest, src);
	printf("%s\n", my_strcpy(dest,src)); //如果返回是void则不能链式访问
	return 0;
}

//int main()
//{
//	char dest[20] = "hello ";
//	//char dest[] = { 'h','e','l','l','o' };
//	char src[] = "bit"; //dest和src都得有'\0'作为标志
//	printf("%s\n", strcat(dest, src));
//	return 0;
//}

char* my_strcat(char* dest, const char* src)
{
	assert(dest && src);
	char* ret = dest;
	while (*dest)
	{
		dest++; //如果判断条件里写*dest++，则当dest已经为'\0'时，dest还会再++一次
		//此时dest就会将'\0'包括进去，那么即使之后的代码有效，在打印时由于打印到'\0'就不再打印了，所以打印无效
	}
//
//	//while (*dest++)
//	//{
//	//	;
//	//}
//	//dest--;
//
	while (*dest++ = *src++)
	{
		;
	}
	return ret;
}

int main()
{
	char arr1[20] = "hello ";
	char arr2[] = "bit";
	my_strcat(arr1, arr2);
	printf("%s\n", arr1);
	return 0;
}
//
//int main()
//{
//	char arr[20] = "bit";
//	printf("%s\n", my_strcat(arr, arr)); //死循环
//	return 0;
//}


//int main()
//{
//	char arr1[] = "abcdef";
//	char arr2[] = "abq";
//	//printf("%d", strcmp(arr1, arr2));
//	//strcmp函数比较的不是字符串的长度，而是比较字符串中对应位置上的字符的大小，如果相同，则比较下一对，直到不同或者都遇到'\0'
//	//arr1>arr2, return 1, arr1<arr2, return -1, arr1 = arr2, return 0（因编译器而异）
//	/* 这种写法是错误的
//	int ret = strcmp(arr1, arr2);
//	if (ret == 1)
//	{
//		printf(">\n");
//	}
//	else if (ret == 0)
//	{
//		printf("==\n");
//	}
//	else if (ret == -1)
//	{
//		printf("<\n");
//	}
//	*/
//	printf("%d\n", ret);
//	return 0;
//}

//int my_strcmp(const char* s1, const char* s2)
//{
//	assert(s1 && s2);
//	while (*s1 == *s2)
//	{
//		if (*s1 == '\0')
//		{
//			return 0; //相等
//		}
//		s1++;
//		s2++;
//	}
//	//if (*s1 > *s2) //不相等
//	//	return 1;
//	//else
//	//	return -1;
//	return *s1 - *s2;
//
//}
//
//int main()
//{
//	char str1[] = "abcq";
//	char str2[] = "abc";
//
//	int ret = my_strcmp(str1, str2);
//
//	if (ret > 0)
//	{
//		printf(">\n");
//	}
//	else if (ret == 0)
//	{
//		printf("=\n");
//	}
//	else
//	{
//		printf("<\n");
//	}
//	return 0;
//}

//int main()
//{
//	char str1[] = "abcdef";
//	char str2[] = "qwertyuiop";
//	strncpy(str1, str2, 3);
//
//	char str3[] = "abcdef";
//	char str4[] = "qwe";
//	strncpy(str3, str4, 5); //src长度不够时，会拿'\0'填充
//
//
//	printf("%s\n", str1);
//	return 0;
//}

//int main()
//{
//	char str1[20] = "abcdef\0XXXXX"; //最后会补一个'\0'，和strncpy加'\0'的方式不同
//	char str2[] = "qwe";
//	strncat(str1, str2, 5);
//	printf("%s\n", str1);
//
//	return 0;
//}

//int main()
//{
//	char str1[20] = "abcdef\0XXXXX"; 
//	char str2[] = "abcdjkl";
//	printf("%d\n", strncmp(str1, str2, 4));
//	return 0;
//}
//
///*这种写法比较的都是数组的地址，而不是内容
//if (arr1 < arr2);
//if ("abc" < "abcdef");
//*/

////找子串，还有KMP算法
//int main()
//{
//	char str1[20] = "abcdefjlkjjl\0XXXXX"; 
//	char str2[] = "cdef";
//	char* ret = strstr(str1, str2);
//	if (NULL == ret)
//	{
//		printf("Cannot find the string.\n");
//	}
//	else
//	{
//		printf("%s\n", ret);
//	}
//	return 0;
//}

//char* my_strstr(const char* str1, const char* str2)
//{
//	assert(str1 && str2);
//	const char* s1 = str1; //滚动匹配 加上const和str1保持一致，否则权限被放大了
//	const char* s2 = str2;
//
//	const char* cur = str1; //记录开始匹配的位置
//	while (*cur)
//	{
//		s1 = cur;
//		s2 = str2; //匹配失败s2恢复
//		while (*s1 && *s2 && (*s1 == *s2))
//		{
//			s1++;
//			s2++;
//		}
//		if (*s2 == '\0')
//		{
//			return (char*)cur; //返回这一次匹配开始的起始位置，强转为返回类型char*
//		}
//		cur++;
//	}
//	return NULL; //找不到
//}
//
//int main()
//{
//	char str1[] = "abcdefjlkjjl\0XXXXX";
//	char str2[] = "cdef";
//	char* ret = my_strstr(str1, str2);
//	if (NULL == ret)
//	{
//		printf("Cannot find the string.\n");
//	}
//	else
//	{
//		printf("%s\n", ret);
//	}
//	return 0;
//}
//
////特殊的例子
////char str1[] = "abcdeqabcdef";
////char str2[] = "cdef";
////
////char str1[] = "abbbcdef";
////char str2[] = "bbc";

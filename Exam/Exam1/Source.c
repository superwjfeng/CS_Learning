#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int a = 1;
void test()
{
	int a = 2;
	a += 1;
}

int main()
{
	test();
	printf("%d", a);
	return 0;
}

//char reverse_words(char* str, int sz)
//{
//    int i = 0;
//    for (i = 0; i < sz - 1;)
//    {
//        while (32 != str[i])
//        {
//            i++;
//        }
//        int j = 0;
//
//    }
//    return 111;
//}
//
//int main()
//{
//    char str[] = {0};
//    while (scanf("%s", str)!='\0');
//    {
//        ;
//    }
//    int sz = sizeof(str) / sizeof(str[0]);
//    printf("%s", reverse_words(str, sz));
//    return 0;
//}

//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<string.h>
//#include<assert.h>
//void ReverseArr(char* begin, char* end)
//{
//    assert(begin && end);
//    while (begin < end)
//    {
//        char temp = *begin;
//        *begin = *end;
//        *end = temp;
//        begin++;
//        end--;
//    }
//}
//int main()
//{
//    char arr[100] = { 0 };
//    gets(arr);
//    int sz = strlen(arr);
//    //1.将字符串所有都逆序
//    ReverseArr(arr, arr + sz - 1);//将数组首地址和数组末地址传过去
//    //uoy evol I
//    //2.再逆序每个单词
//    char* start = arr;
//    while (*start)
//    {
//        char* end = start;
//        while (*end != ' ' && *end != '\0')//uoy evol I
//        {
//            end++;
//        }//出循环*end为' '或者'\0'
//        ReverseArr(start, end - 1);
//        //当*end为字符空格时，说明后面还有单词，end+1指向下一个单词的起始位置
//        if (*end == ' ')
//        {
//            start = end + 1;
//        }
//        else//此时*end为'\0',说明已经结束，将end指向赋给start，结束大循环，所有单词逆序完成
//        {
//            start = end;
//        }
//    }
//    printf("%s\n", arr);
//    return 0;
//}

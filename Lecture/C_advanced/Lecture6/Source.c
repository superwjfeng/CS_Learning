#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

//数组名通常来说是数组首元素的地址，但是有2个例外
//sizeof(数组名)，这里的数组名表示整个数组，计算的是整个数组的大小。sizeof返回数据类型在内存中所占字节数
//&数组名，这里的数组名表示整个数组，取出的是整个数组的地址

//int main()
//{
	////一维数组
	//int a[] = { 1,2,3,4 };
	//printf("%llu\n", sizeof(a)); //16，取出的是总字节数
	//printf("%llu\n", sizeof(a + 0)); //8，a+0是首元素的地址
	//printf("%llu\n", sizeof(*a)); //4，*a是首元素
	//printf("%llu\n", sizeof(a + 1)); //8，a+1是a[1]的地址
	//printf("%llu\n", sizeof(a[1])); //4，int类型的数据占4字节
	//printf("%llu\n", sizeof(&a)); //8，&a是数组指针
	//printf("%llu\n", sizeof(*&a)); //16，&a地址解引用得到的是数组指向的所有元素，即4个int数据16字节
	//printf("%llu\n", sizeof(&a + 1)); //8， 数组地址的下一个地址
	//printf("%llu\n", sizeof(&a[0])); //8，存储首元素的地址
	//printf("%llu\n", sizeof(&a[0] + 1)); //8，a[1]的地址
	
	//字符数组
	//char arr[] = { 'a','b','c','d','e','f' };
	//printf("%llu\n", sizeof(arr)); //6，一个char数据占1位，总共6位
	//printf("%llu\n", sizeof(arr + 0)); //8，首元素地址
	//printf("%llu\n", sizeof(*arr)); //1，首元素
	//printf("%llu\n", sizeof(arr[1])); //1，第二个元素
	//printf("%llu\n", sizeof(&arr)); //8，arr数组的地址
	//printf("%llu\n", sizeof(&arr + 1)); //8，arr数组的下一个地址
	//printf("%llu\n", sizeof(&arr[0] + 1)); //8，首元素的下一个地址
	//printf("%d\n", strlen(arr)); //随机值，arr数组中没有\0，所以strlen函数会继续往后找\0，统计\0之前出现的字符个数
	//printf("%d\n", strlen(arr + 0)); //随机值
	//printf("%d\n", strlen(*arr)); //错误的代码，没有给一个有效的地址，内存访问错误
	//printf("%d\n", strlen(arr[1])); //错误的代码
	//printf("%d\n", strlen(&arr)); //随机值
	//printf("%d\n", strlen(&arr + 1)); //随机值
	//printf("%d\n", strlen(&arr[0] + 1)); //随机值

	//char arr[] = "abcdef"; //[a b c d e f \0]
	//printf("%llu\n", sizeof(arr)); //7，\0也是算入字符串长度的
	//printf("%llu\n", sizeof(arr + 0)); //8 数组首元素地址
	//printf("%llu\n", sizeof(*arr)); //1 数组首元素
	//printf("%llu\n", sizeof(arr[1])); //1 数组第二个元素
	//printf("%llu\n", sizeof(&arr)); //8 整个数组的地址
	//printf("%llu\n", sizeof(&arr + 1)); //8 整个数组之后的下一位地址
	//printf("%llu\n", sizeof(&arr[0] + 1)); //8，arr[1]的地址
	//printf("%d\n", strlen(arr)); //6，\0之前的字符长度
	//printf("%d\n", strlen(arr + 0)); //6
	//printf("%d\n", strlen(*arr)); //访问错误
	//printf("%d\n", strlen(arr[1])); //访问错误
	//printf("%d\n", strlen(&arr)); //6
	//printf("%d\n", strlen(&arr + 1)); //随机值
	//printf("%d\n", strlen(&arr[0] + 1)); //5

	//char* p = "abcdef";
	//printf("%llu\n", sizeof(p)); //8 p是一个地址指针
	//printf("%llu\n", sizeof(p + 1)); //8
	//printf("%llu\n", sizeof(*p)); //1 'a'是一个char类型数据
	//printf("%llu\n", sizeof(p[0])); //1
	//printf("%llu\n", sizeof(&p)); //*p的二级指针 8
	//printf("%llu\n", sizeof(&p + 1)); //8
	//printf("%llu\n", sizeof(&p[0] + 1)); //8
	//printf("%d\n", strlen(p)); //6
	//printf("%d\n", strlen(p + 1)); //5
	//printf("%d\n", strlen(*p)); //需要一个地址，给了一个'a'，访问错误
	//printf("%d\n", strlen(p[0])); //访问错误
	//printf("%d\n", strlen(&p)); //随机值
	//printf("%d\n", strlen(&p + 1)); //随机值
	//printf("%d\n", strlen(&p[0] + 1)); //5

	////二维数组
	//int a[3][4] = { 0 };
	//printf("%llu\n", sizeof(a)); //48 二维数组a的所有元素
	//printf("%llu\n", sizeof(a[0][0])); //4 第一行第一个int元素
	//printf("%llu\n", sizeof(a[0])); //16 第一行4个int元素
	//printf("%llu\n", sizeof(a[0] + 1)); //8 第一行第二个元素的地址
	//printf("%llu\n", sizeof(*(a[0] + 1))); //4 第一行第二个元素为int数据
	////a是数组首元素的地址，a是二维数组，首元素的地址是第一行的地址
	////a[0]是第一行第一个元素的地址，sizeof(a[0])是第一行整个数组所占的内存大小
	//printf("%llu\n", sizeof(a + 1)); //8 第二行数组的地址 *(a+1) -> a[1]
	//printf("%llu\n", sizeof(*(a + 1))); //16 第二行4个元素
	//printf("%llu\n", sizeof(&a[0] + 1)); //8 第二行地址
	//printf("%llu\n", sizeof(*(&a[0] + 1))); //16 对第二行的地址解引用访问到就是第二行
	//printf("%llu\n", sizeof(*a)); //16 对第一行地址解引用就是第一行
	//printf("%llu\n", sizeof(a[3])); //16 类型已经确定了，大小就确定了，sizeof不会访问内存空间
//	return 0;
//}

//int main()
//{
//	int a[5] = { 1,2,3,4,5 };
//	int* ptr = (int*)(&a + 1);
//	printf("%d, %d", *(a + 1), *(ptr - 1)); //2; 5
//	return 0;
//}

struct Test
{
	int Num;
	char* pcName;
	short sDate;
	char cha[2];
	short sBa[4];
} *p;

int main()
{
	p = (struct Test*)0x100000;
	printf("%p\n", p + 0x1);
	printf("%p\n", (unsigned long)p + 0x1);
	printf("%p\n", (unsigned int*)p + 0x1);
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//int main()
//{
//	int aa[2][5] = { 10,9,8,7,6,5,4,3,2,1 };
//	int* ptr1 = (int*)(&aa + 1);
//	int* b = *(aa + 1);
//	int* ptr2 = (int*)(*(aa + 1)); //aa是二维数组首元素，即第一行数组的地址，数组指针+1就是下一个数组，即指向第二行数组，*(aa+1)=aa[1]
//	//*(a+1)=a[1]
//	printf("%d,%d", *(ptr1 - 1), *(ptr2 - 1));
//	return 0;
//}

//int main()
//{
//	int a[4] = { 1, 2, 3, 4 };
//	int* ptr1 = (int*)(&a + 1);
//	int* ptr2 = (int*)((int)a + 1);// Ox01 00 00 00 (small endian) -> Ox00 00 00 02 -> Ox02 00 00 00 
//	printf("%x,%x", ptr1[-1], *ptr2); //4 2000000
//	return 0;
//}

//int main()
//{
//	int a[3][2] = { (0, 1), (2, 3), (4, 5) }; //逗号表达式的结果是最后一个
//	//int a[3][2] = {{1,3}, {5,0}, {0,0}};
//	int* p;
//	p = a[0];
//	printf("%d", p[0]); //1
//	return 0;
//}

//int main()
//{
//	int a[5][5];
//	int(*p)[4];
//	p = a;
//	printf("%p,%d\n", &p[4][2] - &a[4][2], &p[4][2] - &a[4][2]); //FFFFFFFC（-4以地址打印打印原码） -4
//	return 0;
//}

//int main()
//{
//	int aa[2][5] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//	int* ptr1 = (int*)(&aa + 1);
//	int* ptr2 = (int*)(*(aa + 1));
//	printf("%d,%d", *(ptr1 - 1), *(ptr2 - 1)); //10 5
//	return 0;
//}

//int main()
//{
//	char* a[] = { "work","at","alibaba" }; //字符串首字符的地址存到a里
//	char** pa = a;
//	pa++;
//	printf("%s\n", *pa); // "at"
//	return 0;
//}

int main()
{
	char* c[] = { "ENTER", "NEW", "POINT", "FIRST" };
	char** cp[] = { c + 3, c + 2, c + 1, c }; //E, T, N, E
	char*** cpp = cp;
	printf("%s\n", **++cpp); //"POINT"
	printf("%s\n", *-- * ++cpp + 3);
	printf("%s\n", *cpp[-2] + 3);
	printf("%s\n", cpp[-1][-1] + 1);
	return 0;
}

//int main()
//{
//	char c[20] = "HelloWorld.";
//	char d[] = { "Hello", "World" };
//	//int arr[] = { 1,2,3 };
//	return 0;
//}

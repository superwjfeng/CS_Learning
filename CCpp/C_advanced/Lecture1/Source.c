#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void test(void)
{
	;
}

int check_sys()
{
	int a = 1;
	//char* p = (char*)&a;
	//return *p;
	return *(char*)&a;
}

//int main()
//{
	//int a = 1;
	//char* p = (char*)&a;
	//if (*p == 1)
	//{
	//	printf("Big endian");
	//}
	//else
	//{
	//	printf("Little endian");
	//}
	//return 0;

//	int ret = check_sys();
//	if (ret == 1)
//	{
//		printf("Big endian");
//	}
//	else
//	{
//		printf("Little endian");
//	}
//	return 0;
//}



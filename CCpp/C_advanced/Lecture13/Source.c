#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//int main()
//{
	////打开文件
	//FILE* pf = fopen("test.txt", "r");
	//if (pf == NULL)
	//{
	//	perror("fopen");
	//	return 1;
	//}

	////操作文件

	////读文件-输入操作
	//
	//int ch = 0;
	//while ((ch = fget(pf)) != EOF)
	//{
	//	printf("%c ", ch);
	//}

	////关闭文件
	//fclose(pf);

	//return 0;
//}

//
//int main()
//{
//	//stdin, stdout, stderr, 是一个程序运行时默认打开的
//	//int ch = fgetc(stdin);
//	//printf("%c\n", ch);
//	//fputc(ch, stdout);
//	char arr[256] = { 0 };
//	FILE* pf = fopen("test.txt", "r");
//	if (pf == NULL)
//	{
//		perror("fopen");
//		return 1;
//	}
//	//读文件，读一行
//	//fgets(arr, 256, pf); //实际只会读255个字符，因为最后一个要留给\0
//	while (fgets(arr, 256, pf) != NULL)
//	{
//		printf("%s", arr);
//	}
//
//	fclose(pf);
//	pf = NULL;
//	return 0;
//}

struct S
{
	char name[20];
	int age;
	double d;
};

//int printf(const char* format[, argument]...);
//int fprintf(FILE* stream, const char* format[, argument]...);
//
//int scanf(const char* format[, argument]...);
//int fscanf(FILE* stream, const char* format[, argument]...);

//int main()
//{
//	struct S s = { "Zhangsan",20,95.5 };
////	struct S s = { 0 };
//	FILE* pf = fopen("test.txt", "w");
//	//打开文件
//	fopen("test.txt", "w");
//	if (pf == NULL)
//	{
//		perror("fopen");
//		return 1;
//	}
//
//	//写文件
//	//fprintf(pf, "%s %d %lf", s.name, s.age, s.d);
//
//	//读文件
//	fscanf(pf, "%s %d %lf", s.name, &(s.age), &(s.d));
//	printf("%s %d %lf", s.name, s.age, s.d);
//
//	//关闭文件
//	fclose(pf);
//	pf = NULL;
//}


int main()
{
	char buf[256] = { 0 };
	struct S s = { "zhangsan", 20, 95.5 };
	struct S tmp = { 0 };
	sprintf(buf, "%s %d %lf", s.name, s.age, s.d);
	printf("%s\n", buf);
	//从buf字符串中提取结构体数据
	sscanf(buf, "%s %d %lf", tmp.name, &(tmp.age), &(tmp.d));
	printf("%s %d %lf", tmp.name, tmp.age, tmp.d); 
	return 0;
}

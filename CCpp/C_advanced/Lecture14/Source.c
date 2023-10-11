#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//int main()
//{
//	//打开文件
//	FILE* pf = fopen("test.txt", "r");
//	if (pf == NULL)
//	{
//		perror("fopen");
//		return 1;
//	}
//
//	//随机读
//	int ch = fgetc(pf);
//	printf("%c\n", ch);
//
//	ch = fgetc(pf);
//	printf("%c\n", ch);
//	//fseek origin参数的取值
//	//SEEK_CUR-文件指针当前的位置
//	//SEEK_END-文件末尾的位置
//	//SEEK_SET-文件开始位置
//	fseek(pf, 2, SEEK_CUR);
//	ch = fgetc(pf);
//	printf("%c\n", ch);
//
//	fseek(pf, -1, SEEK_END);
//	ch = fgetc(pf);
//	printf("%c\n", ch);
//
//	fseek(pf, 4, SEEK_SET);
//	ch = fgetc(pf);
//	printf("%c\n", ch);
//
//	//关闭文件
//	fclose(pf);
//	pf = NULL;
//
//	return 0;
//}
//
//int main()
//{
//	//打开文件
//	FILE* pf = fopen("test.txt", "w");
//	if (pf == NULL)
//	{
//		perror("fopen");
//		return 1;
//	}
//
//	//随机写
//	fputc('a', pf);
//	fputc('b', pf);
//	fputc('c', pf);
//	fputc('d', pf);
//
//	fseek(pf, -3, SEEK_CUR);
//	fputc('w', pf);
//
//	long pos = ftell(pf); //文件指针偏移量
//	printf("%ld\n", pos);
//
//	rewind(pf); //重置文件指针
//	pos = ftell(pf); 
//	printf("%ld\n", pos);
//
//	//关闭文件
//	fclose(pf);
//	pf = NULL;
//
//	return 0;
//}

//int main()
//{
//	int a = 10000;
//	FILE* pf = fopen("test.txt", "wb");
//	if (pf == NULL)
//	{
//		perror("fopen");
//		return 1;
//	}
//	
//	fwrite(&a, 4, 1, pf);
//	fclose(pf);
//	pf == NULL;
//	return 0;
//}

int main()
{
	int i = 0;
	FILE* pf = fopen("log.txt", "a");
	if (pf == NULL)
	{
		return 1;
	}
	for (i = 0; i < 10; i++)
	{
		fprintf(pf, "name:%s, file:%s, line:%d, date:%s, time:%s, i=%d\n", __func__, __FILE__, __LINE__, __DATE__, __TIME__, i);
	}


	return 0;
}

//vs不遵循ANSIC
//gcc遵循

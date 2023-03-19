#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2) 
    {
        printf("argv error\n");
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        perror("fopen");
        return 2;
    }
   
    // 按行读取
    char line[64];
    // fgets是C语言的接口来取string，因此会自动在字符结尾添加\0
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // printf("%s", line);
        fprintf(stdout, "%s", line);
    }
    //// 进行文件操作
    //const char *s1 = "hello fwrite\n";
    //fwrite(s1, strlen(s1), 1, fp); // 写的长度不需要+1，\0结尾是C语言的规定，文件不需要遵守
    //
    //const char *s2 = "hello fprintf\n";
    //fprintf(fp, "%s", s2);

    //const char *s3 = "hello fputs\n";
    //fputs(s3, fp);
    return 0;
}

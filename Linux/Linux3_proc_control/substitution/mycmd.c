#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("can not executed!\n");
        exit(1);
    }
    
    printf("获取环境变量：MY_105_VAL: %s\n", getenv("MY_105_VAL"));

    if (strcmp(argv[1], "-a")==0)
    {
        printf("hello a!\n");
    }
    else if(strcmp(argv[1], "-b")==0)
    {
        printf("hello b\n");
    }
    else
    {
        printf("default!\n");
    }
}

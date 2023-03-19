#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[], char* env[])
{
    //printf("begin ........................\n");
    //for (int i = 0; env[i]; i++)
    //{
    //    printf("env[%d]: %s\n", i, env[i]);
    //}
    //printf("end ..........................\n");
    
    for (int i = 0; i< argc; i++)
    {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    return 0;
}

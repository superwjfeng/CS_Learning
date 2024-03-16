#include <stdio.h>
#include <stdlib.h>

const char c[6] = {1, 2, 3, 4, 5, 6};

int un_g_val;

int g_val = 100;

int main(int argc, char *argv[], char *env[]) {
    // 字面常量也能通过编译
    //"hello world";
    // 10;
    //'a';

    static int S = 3;
    int stack_num = 2;
    char *p1 = (char *)malloc(16);
    char *p2 = (char *)malloc(16);
    char *p3 = (char *)malloc(16);
    char *p4 = (char *)malloc(16);

    printf("-----------------------\n");
    for (int i = 0; i < argc; i++)
        printf("argv[%d]:            %p\n", i, argv[i]);
    for (int i = 0; i < 2; i++)
        printf("env[%d]:             %p\n", i, env[i]);
    printf("Too much environment variables, only 2 given in this expriment.\n");
    printf("--------------------------------\n");
    printf("StackNum:           %p\n", &stack_num);
    printf("stack1:             %p\n", &p1);
    printf("stack2:             %p\n", &p2);
    printf("stack3:             %p\n", &p3);
    printf("stack4:             %p\n", &p4);
    printf("--------------------------------\n");
    printf("heap4:              %p\n", p4);
    printf("heap3:              %p\n", p3);
    printf("heap2:              %p\n", p2);
    printf("heap1:              %p\n", p1);
    printf("--------------------------------\n");
    printf("uninit:             %p\n", &un_g_val);
    printf("init:               %p\n", &g_val);
    printf("static:             %p\n", &S);
    printf("--------------------------------\n");
    printf("const read-only:    %p\n", c);
    printf("code addr &main:    %p\n", main);
    printf("--------------------------------\n");
    return 0;
}

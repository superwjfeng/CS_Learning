#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <errno.h>

void myperror(const char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
}

int main()
{

   // int fd = open("test", O_RDONLY);
   // if (fd < 0)
   // {
   //     myperror("open");
   //     return 1;
   // }


    //char input[16];
    //ssize_t s =  read(0, input, sizeof(input)); // ssize_t 返回值是实际读取的大小，而第三个参数是期望读取的大小，第一个参数是fd，这里就是stdin
    //if (s>0)
    //{
    //    input[s] = '\0'; // 最后一位设为'\0'
    //    printf("%s\n", input);

    //}


    //int a = 0;
    //fscanf(stdin, "%d", &a);
    //printf("%d\n", a);

   // printf("stdin: %d\n", stdin->_fileno);
   // printf("stdout: %d\n", stdout->_fileno);
   // printf("stderr: %d\n", stderr->_fileno);
    
    // stdout -> 1
    printf("hello printf 1\n");
    fprintf(stdout, "hello fprintf 1\n");
    // stderr -> 2
    errno = 1;
    perror("heelo perror 2");

    const char *s1 = "hello write 1\n";
    write(1, s1, strlen(s1));
    const char *s2 = "hello write 2\n";
    write(2, s2, strlen(s2));

    std::cout << "hello cout 1" << std::endl;
    std::cerr << "hello cerr 2" << std::endl;
    
    return 0;
}

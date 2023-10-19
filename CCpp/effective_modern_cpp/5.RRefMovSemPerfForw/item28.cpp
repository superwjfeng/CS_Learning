#include <iostream>
#include <string>

template <typename T>
void fun(T &&t)
{
    T &a = 10;
}

int main()
{
    int a = 10;
    auto &&b = a;

    fun(10);
}
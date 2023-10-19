#include <iostream>
#include <string>
#include <vector>
class A
{
public:
    A(int param) : mm(param) {}
    A(const A &a)
    {
        std::cout << "A (const A&a)" << std::endl;
        mm = a.mm;
    }
    A(A &&a)
    {
        std::cout << "A (&&a)" << std::endl;
        mm = a.mm;
        a.mm = 0;
    }
    // A &operator=(const A &a)
    // {
    //     std::cout << "A &operator=(const A &a)" << std::endl;
    //     mm = a.mm;
    //     return *this;
    // }
    // A &operator=(A &&a)
    // {
    //     std::cout << "A &operator=(A &&a)" << std::endl;
    //     mm = a.mm;
    //     a.mm = 0;
    //     return *this;
    // }
    ~A()
    {
        std::cout << "~A()" << std::endl;
    }

private:
    int mm{};
    int *nn = nullptr;
};

int main()
{
    // A a{1};
    // A aa{2};
    A b{5};
    // b = aa;

    // A c{20};
    // c = a;
    A mm = std::move(b);
    A c{10};
    // mm = std::move(c);
    // A d = std::move(a);
    // d = std::move(a);
    return 0;
}
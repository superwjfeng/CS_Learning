#include <iostream>

class A {
    void test() {}
};

class B {
    void test() {}
};

class C {
    static int a;
};

int C::a = 1;

class D {
    int a = 1;
};

class E {
    int a = 1;
    char b = 'a';
};

class F : public D {
    int b = 2;
};

class G : virtual public D {
    int c = 3;
};

class H {
    virtual void test() {}
};

class I : public H {
    int d = 4;
};

int main() {
    std::cout << "sizeof(A): " << sizeof(A) << std::endl;
    std::cout << "sizeof(B): " << sizeof(B) << std::endl;
    std::cout << "sizeof(C): " << sizeof(C) << std::endl;
    std::cout << "sizeof(D): " << sizeof(D) << std::endl;
    std::cout << "sizeof(E): " << sizeof(E) << std::endl;
    std::cout << "sizeof(F): " << sizeof(F) << std::endl;
    std::cout << "sizeof(G): " << sizeof(G) << std::endl;
    std::cout << "sizeof(I): " << sizeof(I) << std::endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <type_traits>

template <typename T>
struct Func1
{
    using type = T;
};

// template <>
// struct Func1<int>
// {
//     using type = int;
//     using b_type = float;
// };

template <typename T>
struct Func2
{
};

class Person
{
public:
    Person() = default;
    template <typename T, typename = typename Func1<T>::b_type>
    Person(T &&n)
    {
        std::cout << "Person(T &&n)" << std::endl;
    }

    Person(const Person &p)
    {
        std::cout << "Person(const Person &p)" << std::endl;
    }
};
namespace
{
    template <bool, typename _Tp = void>
    struct enable_if
    {
    };

    // Partial specialization for true.
    template <typename _Tp>
    struct enable_if<true, _Tp>
    {
        typedef _Tp type;
    };
}

// class Person
// {
// public:
//     template <
//         typename T,
//         typename = typename std::enable_if<
//             !std::is_same<Person,
//                           typename std::decay<T>::type>::value>::type>
//     explicit Person(T &&n);
// };

int main()
{
    Person p;
    Person p1(p);
    return 0;
}
// https://en.cppreference.com/w/cpp/language/static
#include <iostream>
#include <array>
 

struct Foo;
 
struct S
{
    static int a[]; // declaration, incomplete type
    static Foo x;   // declaration, incomplete type
    static S s;     // declaration, incomplete type (inside its own definition)
};
 
int S::a[10]; // definition, complete type
struct Foo {};
Foo S::x;     // definition, complete type
S S::s;       // definition, complete type

 
int main()
{
    std::cout << "S::a[0] is "<< S::a[0] << '\n';
}
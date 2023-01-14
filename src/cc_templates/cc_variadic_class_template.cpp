// https://en.cppreference.com/w/cpp/language/parameter_pack
#include <iostream>

using namespace std;

// Part 1
//   A variadic class template
template<class... Types>
struct Tuple {};
 
Tuple<> t0;           // Types contains no arguments
Tuple<int> t1;        // Types contains one argument: int
Tuple<int, float> t2; // Types contains two arguments: int and float
// Tuple<0> t3;          // error: 0 is not a type

//   A variadic function template
template<class... Us>
void f(Us... args){

};
 
void test_f() {
    f();       // OK: args contains no arguments
    f(1);      // OK: args contains one argument: int
    f(2, 1.0); // OK: args contains two arguments: int and double
}


//   Pack expansion 
template<class... Ts>
void g(Ts... args)
{
    f(&args...); // “&args...” is a pack expansion
                 // “&args” is its pattern
                 // expands to f(&E1, &E2, &E3)
}
 
void test_g() {
    g(1, 0.2, "a"); // g: Ts... args expand to int E1, double E2, const char* E3
                    //    &args... expands to &E1, &E2, &E3
                    // f: Us... args expand to int* E1, double* E2, const char** E3
}

template<class... Ts>
void g2(int n, Ts... args) {
    f(args...);              // expands to f(E1, E2, E3)
    f(n, ++args...);         // expands to f(n, ++E1, ++E2, ++E3);
    f(++args..., n);         // expands to f(++E1, ++E2, ++E3, n);
}

void test_g2() {
    g2(1, 2, 3);
}

//      Pack expansion can be used in Brace-enclosed initializers.
//      More examples : https://www.ibm.com/docs/en/zos/2.3.0?topic=only-variadic-templates-c11
template<typename... Ts>
void func(Ts... args)
{
    const int size = sizeof...(args) + 2;
    int res[size] = {1, args..., 2};
 
    // since initializer lists guarantee sequencing, this can be used to
    // call a function on each element of a pack, in order:
    int dummy[sizeof...(Ts)] = {
            (std::cout << args << "_", 0)... // comma operator: https://en.cppreference.com/w/cpp/language/operator_other
        }; 
    cout << endl;

    int n_dummy = sizeof(dummy) / sizeof(int);
    cout << "dummy, with size " << n_dummy << ", elements: ";
    for(int i=0; i<n_dummy; i+=1) {
        cout << dummy[i] << " ";
    }
    cout << std::endl;
}


void test_func() {
    func(1, 2, 3);
}


// Part 2: example
 
void tprintf(const char* format) // base function
{
    std::cout << format;
}
 
template<typename T, typename... Targs>
void tprintf(const char* format, T value, Targs... Fargs) // recursive variadic function
{
    for (; *format != '\0'; format++)
    {
        if (*format == '%')
        {
            std::cout << value;
            tprintf(format + 1, Fargs...); // recursive call
            return;
        }
        std::cout << *format;
    }
}
 
int main()
{
    // Part 1
//   A variadic function template
    test_f();
//   Pack expansion 
    test_g();
    test_g2();
//      Pack expansion can be used in Brace-enclosed initializers.
//      More examples : https://www.ibm.com/docs/en/zos/2.3.0?topic=only-variadic-templates-c11
    test_func();

    // Part2
    tprintf("% world% %\n", "Hello", '!', 123);

    //output:
    // Hello world! 123
}
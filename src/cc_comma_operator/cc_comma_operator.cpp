// https://en.cppreference.com/w/cpp/language/operator_other

#include <iostream>
 
int main()
{

    int a[] = {1, (std::cout << "op1 has been evaluated" << std::endl, 5, 2), 3};

    int n = 1;
    int m = (++n, std::cout << "n = " << n << '\n', ++n, 2 * n);
    std::cout << "m = " << (++m, m) << '\n';
    /*
n = 2
m = 7
    */
}


// https://en.cppreference.com/w/cpp/language/enum

#include <iostream>
#include <cstdint>

#include <iostream>
#include <cstdint>
 
// Part1: Unscoped enumerations
// enum that takes 16 bits
enum smallenum: std::int16_t
{
    a,
    b,
    c
};

/*
Values of unscoped enumeration type are implicitly-convertible to integral types. 
If the underlying type is not fixed, the value is convertible to the first type from 
the following list able to hold their entire value range: int, unsigned int, long, 
unsigned long, long long, or unsigned long long, extended integer types with higher c
onversion rank (in rank order, signed given preference over unsigned) (since C++11). 
If the underlying type is fixed, the values can be converted to their underlying type 
(preferred in overload resolution), which can then be promoted.
*/
 
// color may be red (value 0), yellow (value 1), green (value 20), or blue (value 21)
enum color
{
    red,
    yellow,
    green = 20,
    blue
};

// the constant d is 0, the constant e is 1, the constant f is 3
enum
{
    d,
    e,
    f = e + 2
};

// Part2: 

/*
enum struct|class name { enumerator = constexpr , enumerator = constexpr , ... }	(1)	
enum struct|class name : type { enumerator = constexpr , enumerator = constexpr , ... }	(2)

1) declares a scoped enumeration type whose underlying type is int (the keywords class and struct are exactly equivalent)
2) declares a scoped enumeration type whose underlying type is type

Each enumerator becomes a named constant of the enumeration's type (that is, name), which is 
contained within the scope of the enumeration, and can be accessed using scope resolution operator. 
There are no implicit conversions from the values of a scoped enumerator to integral types, 
although static_cast may be used to obtain the numeric value of the enumerator.
*/
 
// altitude may be altitude::high or altitude::low
enum class altitude: char
{
    high = 'h',
    low = 'l', // trailing comma only allowed after CWG 518
}; 

enum class Color2 { red, green = 20, blue };

void test_color2() {
    Color2 r = Color2::blue;
    // int n = r; // error: no implicit conversion from scoped enum to int
    int n = static_cast<int>(r); // OK, n = 21
}
 
// Part3
// enumeration types (both scoped and unscoped) can have overloaded operators
std::ostream& operator<<(std::ostream& os, color c)
{
    switch(c)
    {
        case red   : os << "red";    break;
        case yellow: os << "yellow"; break;
        case green : os << "green";  break;
        case blue  : os << "blue";   break;
        default    : os.setstate(std::ios_base::failbit);
    }
    return os;
}
 
std::ostream& operator<<(std::ostream& os, altitude al)
{
    return os << static_cast<char>(al);
}

int main()
{
    color col = red;
    int n = blue; // n == 21

    altitude a;
    a = altitude::low;
 
    std::cout << "col = " << col << '\n'
              << "a = "   << a   << '\n'
              << "f = "   << f   << '\n';

    test_color2();
 
 /*
col = red
a = l
f = 3
 */
}
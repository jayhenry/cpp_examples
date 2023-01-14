// https://en.cppreference.com/w/cpp/utility/integer_sequence
/*
The class template std::integer_sequence represents a compile-time sequence of integers. 
When used as an argument to a function template, the parameter pack Ints can be deduced and used in pack expansion.
For example, `a2t` funtion below shows how to use it.
*/

#include <tuple>
#include <iostream>
#include <array>
#include <utility>
 
// debugging aid
template<typename T, T... ints>
void print_sequence(std::integer_sequence<T, ints...> int_seq)
{
    std::cout << "The sequence of size " << int_seq.size() << ": ";
    ((std::cout << ints << ' '), ...);
    std::cout << '\n';
}
 
// convert array into a tuple
template<typename Array, std::size_t... I>
auto a2t_impl(const Array& a, std::index_sequence<I...>)
{
    return std::make_tuple(a[I]...);
}
 
template<typename T, std::size_t N, typename Indices = std::make_index_sequence<N>>
auto a2t(const std::array<T, N>& a)
{
    return a2t_impl(a, Indices{});
}
 
// pretty-print a tuple
template<class Ch, class Tr, class Tuple, std::size_t... Is>
void print_tuple_impl(std::basic_ostream<Ch,Tr>& os,
                      const Tuple& t,
                      std::index_sequence<Is...>)
{
    ((os << (Is == 0? "" : ", ") << std::get<Is>(t)), ...);
}
 
template<class Ch, class Tr, class... Args>
auto& operator<<(std::basic_ostream<Ch, Tr>& os,
                 const std::tuple<Args...>& t)
{
    os << "(";
    print_tuple_impl(os, t, std::index_sequence_for<Args...>{});
    return os << ")";
}
 
int main()
{
    /*
template< class T, T... Ints >
class integer_sequence;

T	-	an integer type to use for the elements of the sequence
...Ints	-	a non-type parameter pack representing the sequence

Member type	Definition
value_type	T

Member functions:
size [static]: returns the number of elements in Ints
    */
    print_sequence(std::integer_sequence<unsigned, 9, 2, 5, 1, 9, 1, 6>{});
    // template<class T, T N>
    // using make_integer_sequence = std::integer_sequence<T, /* a sequence 0, 1, 2, ..., N-1 */ >;
    print_sequence(std::make_integer_sequence<int, 20>{});
    // template<std::size_t N>
    // using make_index_sequence = std::make_integer_sequence<std::size_t, N>;
    print_sequence(std::make_index_sequence<10>{});
    // template<class... T>
    // using index_sequence_for = std::make_index_sequence<sizeof...(T)>;
    print_sequence(std::index_sequence_for<float, std::iostream, char>{});
 
    std::array<int, 4> array = {1, 2, 3, 4};
 
    // convert an array into a tuple
    auto tuple = a2t(array);
    static_assert(std::is_same_v<decltype(tuple),
                                 std::tuple<int, int, int, int>>, "");
 
    // print it to cout
    std::cout << "The tuple: " << tuple << '\n';

/* output:
The sequence of size 7: 9 2 5 1 9 1 6 
The sequence of size 20: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 
The sequence of size 10: 0 1 2 3 4 5 6 7 8 9 
The sequence of size 3: 0 1 2 
The tuple: (1, 2, 3, 4)
*/
}
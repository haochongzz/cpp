#include <string>
#include <type_traits>

template <typename T>
int compare(const T &, const T &);

// the type of the parameters in pf determines the type of template argument for
// T. The the pointer pf points to the instantiation of compare with T bound to
// int.
int (*pf)(const int &, const int &) = compare;

// it is an error if the template argument cannot be determined from the
// function pointer type.
void func(int (*)(const std::string &, const std::string &));
void func(int (*)(const int &, const int &));

using fp = int (*)(const std::string &, const std::string &);

int main() {
    func(compare);
    // we can disambiguate the call to func by using explicit template argument.
    func(compare<int>);
}

// argument deduction
// lvalue reference as function parameters

// reference binding rules say that argument must be lvalue.
template <typename T>
void foo(T &x);

// reference binding rules say that we can pass any argument.
template <typename T>
void foo(const T &x);
// foo(i), foo(ci), foo(5)

// rvalue reference as function parameters

// normal binding rules say we can pass a rvalue. <- wrong!
template <typename T>
void foo(T &&x);

// -----------------------------------------------------------------------------
// reference collapsing
// rule 1:
//  When we pass an lvalue (e.g., int i) to a function parameter that is an
//  rvalue reference to a template type parameter (e.g, T&&), the compiler
//  deduces the template type parameter as the argument’s lvalue reference type
//  (e.g int&).
// rule 2:
//  If we indirectly create a reference to a reference, then those references
//  `collapse.`
//  X& &, X& &&, X&& & -> X&
//  X&& && -> X&&
// For example:
//   foo(i) would have a resulting instantiation:
//   void foo<int&>(int& &&x);
//   where T is int& and function parameter is int& &&, which collapse to int&.
//   void foo<int&>(int &x)
//
// Summary:
// Reference collapsing applies only when a reference to a reference is created
// indirectly, such as in a type alias or a template parameter.
//
// An argument of any type can be passed to a function parameter that is an
// rvalue reference to a template parameter type (i.e., T&&). When an lvalue is
// passed to such a parameter, the function parameter is instantiated as an
// ordinary, lvalue reference (T&).

// std::move() function
template <typename T>
typename std::remove_reference<T>::type &&move(T &&t) {
    return static_cast<typename std::remove_reference<T>::type &&>(t);
}
// static_cast from lvalue to rvalue is permitted by a special rule.

// A function parameter that is an rvalue reference to a template type parameter
// (i.e., T&&) preserves the constness and lvalue/rvalue property of its
// corresponding argument.

// -----------------------------------------------------------------------------
// forwarding
// Unlike move, forward must be called with an explicit template argument
// (§ 16.2.2, p. 682). forward returns an rvalue reference to that explicit
// argument type. That is, the return type of forward<T> is T&&.

void foo(int &&v1, int &v2)  // note v2 is a reference
{
    std::cout << v1 << " " << ++v2 << std::endl;
}
// version 1: solve half of the problem, t2 is a lvalue of type rvalue reference
// to T2.
template <typename F, typename T1, typename T2>
void flip(F f, T1 &&t1, T2 &&t2) {
    f(t2, t1);
}
// version 2:
template <typename F, typename T1, typename T2>
void flip(F f, T1 &&t1, T2 &&t2) {
    f(std::forward<T2>(t2), std::forward<T1>(t1));
}
// When used with a function parameter that is an rvalue reference to template
// type parameter(T&&), forward preserves all the details about an argument’s
// type.

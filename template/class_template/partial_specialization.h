// https://en.cppreference.com/w/cpp/language/partial_specialization
// partial specialization

// allows customizing class and variable (since C++14) templates for a given
// category of template arguments.

// syntax:
// template < parameter-list >
// class-key class-head-name < argument-list > declaration

template <typename T, typename U, int I>
class Foo {};  // primary template

template <typename T, int I>
class Foo<T, T *, I> {};  // partial specialization where U is a pointer to T

// argument list
// the argument list cannot be identical to the non-specialized argument list
// (it must specialize something)
template <typename T, typename U, int I>
class Foo<T, U, I> {};

// name lookup
// partial template specializations are not found by name lookup. only if the
// primary template is found by name lookup, its partial specializations are
// considered.
namespace foo {
template <typename T, typename U>
class Bar {};

template <typename T>
class Bar<T, T *> {};
}  // namespace foo
// using foo::Bar;
// Bar<int, int *> x;
using foo::Bar<int, int *>;

// partial ordering
//
// When a class or variable (since C++14) template is instantiated, and there
// are partial specializations available, the compiler has to decide if the
// primary template is going to be used or one of its partial specializations.
//
// 1) If only one specialization matches the template arguments, that
// specialization is used
// 2) If more than one specialization matches, partial
// order rules are used to determine which specialization is more specialized.
// The most specialized specialization is used, if it is unique (if it is not
// unique, the program cannot be compiled)
// 3) If no specializations match, the
// primary template is used

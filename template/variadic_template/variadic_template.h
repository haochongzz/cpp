// A variadic template is a template function or class that can take a varying
// number of parameters. The varying parameters are known as a parameter pack.
// There are two kinds of parameter packs: A template parameter pack represents
// zero or more template parameters, and a function parameter pack represents
// zero or more function parameters.
#include <iostream>

template <typename T, typename... Args>
void foo(const T &t, const Args &...rest);

// function to end the recursion and print the last element
// this function must be declared before the variadic version of print is
// defined
template <typename T>
std::ostream &print(std::ostream &os, const T &t) {
    return os << t;  // no separator after the last element in the pack
}
// this version of print will be called for all but the last element in the pack
template <typename T, typename... Args>
std::ostream &print(std::ostream &os, const T &t, const Args &...rest) {
    os << t << ", ";  // print the first argument

    return print(os, rest...);  // recursive call; print the other argument
}
// A declaration for the nonvariadic version of print must be in scope when the
// variadic version is defined. Otherwise, the variadic function will recurse
// indefinitely.

// pack expansion
// When we expand a pack, we also provide a pattern to be used on each expanded
// element. Expanding a pack separates the pack into its constituent elements,
// applying the pattern to each element as it does so. We trigger an expansion
// by putting an ellipsis (...) to the right of the pattern.
template <typename... Args>
std::ostream &ErrorMsg(std::ostream &os, const Args &...rest) {
    // print(os, ToString(a1), ToString(a2), ..., ToString(an)
    return print(os, ToString(rest)...);
}

// forwarding parameter pack
template <class... Args>
inline void EmplaceBack(Args &&...args) {
    chk_n_alloc();
    alloc.construct(first_free++, std::forward<Args>(args)...);
}

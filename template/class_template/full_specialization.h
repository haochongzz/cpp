// https://en.cppreference.com/w/cpp/language/template_specialization
// explicit (full) specialization

// allows customizing the template code for a given set of template arguments.

#include <type_traits>
#include <vector>

template <typename T>  // primary template
struct is_void : std::false_type {};
template <>  // explicit specialization for T = void
struct is_void<void> : std::true_type {};

void foo() {
    static_assert(
        is_void<char>::value == false,
        "for any type T other than void, the class is derived from false_type");
    static_assert(is_void<void>::value == true,
                  "but when T is void, the class is derived from true_type");
}

// explicit specialization has to appear after the non-specialized template
// declaration.
namespace foo {

template <typename T>  // primary template
class Foo {
    /* ... */
};
template <>  // specialization in same namespace
class Foo<int> {
    /* ... */
};

// specialization must be declared before the first use that would cause
// implicit instantiation, in every translation unit where such use occurs.
template <typename T>  // primary function template
void bar(const std::vector<T> &v) {
    /* ... */
}

void f(const std::vector<int> &v) { bar(v); }  // implicit instantiates bar()

template <>
void bar<int>(
    const std::vector<int> &v) {  // template argument can be omitted if
                                  // template argument deduction can happen
    /* ... */
}

// member specialization
template <typename T>
class Bar {
    class Foo {};  // member class Foo
};

template <>  // class template specialization
class Bar<int> {
    void f();  // member function of a specialization
};
// template <> not used for a member of specialization
void Bar<int>::f() { /* ... */ }

}  // namespace foo

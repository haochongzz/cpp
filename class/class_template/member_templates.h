template <typename T>
class Foo {
    // constructors can be templates too
    template <typename U>
    Foo(int i) { /* ... */
    }

    template <typename U>
    void bar(const U &);
};

// when a member template is defined outside of the class body, it takes two
// sets of template parameters: one for the enclosing class, and another one for
// itself.
template <typename T>
template <typename U>
void Foo<T>::bar(const U &x) {  // argument deduction
    // ...
}



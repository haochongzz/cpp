// instantiation definition
// an explicit instantiation definition forces instantiation of the class,
// struct, or union they refer to. It may appear in the program anywhere after
// the template definition, and for a given argument-list, is only allowed to
// appear once in the entire program.
//
// this can be used to reduce compilation time.

template <typename T>
class Foo {};

// compiler will not generate code for that instantiation when it sees `extern`.
extern template class Foo<int>;  // instantiation declaration
// compliet generates code for instanstiation when it sees instantiation
// definition.
template class Foo<int>;  // instantiation definition

// instantiate all members
// compiler instantiates all members of a class template when it sees
// instantiation definition because it does not know which member functions will
// be used.

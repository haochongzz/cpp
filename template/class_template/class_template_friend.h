#ifndef FRIENDSHIP_H_
#define FRIENDSHIP_H_

// When a class contains a friend declaration, the class and the friend can
// independently be templates or not. A class template that has a nontemplate
// friend grants that friend access to all the instantiations of the template.
// When the friend is itself a template, the class granting friendship controls
// whether friendship includes all instantiations of the template or only
// specific instantiation(s).
// ----------------------------------------------------------------------------
template <typename T>
class Foo {
  // grants non-template friend access to all instantiations.
  friend class Bar;
};

// forward declartion necessary to befriend a specific instantiantion of a
// template
template <typename T>
class Pal;

class C {
    // Pal instantiated with C is a friend to C.
    friend class Pal<C>;
    // all instances of Pal2 are friends to C.
    template <typename T>
    friend class Pal2;  // no forward declaration required.
};

template <typename T>
class C2 {
    // one-to-one friendship
    friend class Pal<T>;  // a template declaration for Pal must be in scope.
    // all instances of Pal2 are friends of each instance of C2. no forward
    // declaration required.
    template <typename X>
    friend class Pal2;
    // Pal3 is a nontemplate class that is a friend of every instance of C2.
    friend class Pal3;
};

#endif  // FRIENDSHIP_H_

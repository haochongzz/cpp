// enables implicit conversion or explicit conversion from a class type to
// another type.

class Foo {
   public:
    // implicit conversion
    operator int() const { return 42; }

    // explicit conversion: conversion function that participates in
    // direct-initialization and explicit conversions only.
    explicit operator int *() const { nullptr; }
};

Foo foo;
int n = static_cast<int>(foo);
int m = foo;

int *ptr = static_cast<int *>(foo);
// int *ptr = foo;  // error no implicit conversion

// returning a pointer to function
int func(int *, int);

// use type alias
using pf = int (*)(int *, int);
pf f1(int);

// declare f1 directly.
// Reading this declaration from the inside out, we see that f1 has a parameter
// list, so f1 is a function. f1 is preceded by a * so f1 returns a pointer. The
// type of that pointer itself has a parameter list, so the pointer points to a
// function. That function returns an int.
int (*f1(int))(int *, int);

// use trailling return
auto f1(int) -> int (*)(int *, int);
auto f2(int) -> int (*)[10];  // returns a pointer to array

// use decltype. decltype returns a function type! need to add *.
decltype(func) *f1(int);
// Function templates can be overloaded by other templates or by ordinary,
// nontemplate functions. As usual, functions with the same name must differ
// either as to the number or the type(s) of their parameters.
//
// Function matching (§ 6.4, p. 233) is affected by the presence of function
// templates in the following ways:
//
//   • The candidate functions for a call include any function-template
//   instantiation for which template argument deduction (§ 16.2, p. 678)
//   succeeds.
//
//   • The candidate function templates are always viable, because template
//   argument deduction will have eliminated any templates that are not viable.
//
//   • As usual, the viable functions (template and nontemplate) are ranked by
//   the conversions, if any, needed to make the call. Of course, the
//   conversions used to call a function template are quite limited (§ 16.2.1,
//   p. 679).
//
//   • Also as usual, if exactly one function provides a better match than any
//   of the others, that function is selected. However, if there are several
//   functions that provide an equally good match, then:
//
//   – If there is only one nontemplate function in the set of equally good
//   matches, the nontemplate function is called.
//
//   – If there are no nontemplate functions in the set, but there are multiple
//   function templates, and one of these templates is more specialized than any
//   of the others, the more specialized function template is called.
//
//   – Otherwise, the call is ambiguous.
#include <string>

template <typename T>
void foo(const T &);

template <typename T>
void foo(T *);

void foo(const std::string &);

// foo(std::string("hi")); matches: void foo(const std::string &) because it is
// non-template function.
// foo("hello world"); matches: void foo(T *) because it is more specialized.

// missing function declaration.
void foo(char *p) {
    // if the declaration for the version that takes a const string& is not in
    // scope, the return will call foo(const T&) with T instantiated to string
    return foo(std::string(p));
}

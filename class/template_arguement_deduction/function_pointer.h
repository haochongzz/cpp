#include <string>

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
func(compare);

// we can disambiguate the call to func by using explicit template argument.
func(compare<int>);

using fp = int (*)(const std::string &, const std::string &);
typedef int (*fp)(const std::string &, const std::string &);

template <typename T, size_t N>
T *begin(T (&arr)[N]);
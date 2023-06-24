// const conversions and array or function to pointer are the only automatic
// conversions for arguments to parameters with template types.

// function parameters that use the same template type parameter
// the arguments to such parameters must have essentially the same type,
// mismatched deduced types is an error.

// function template explicit arguments
//  explicit template arguments are matched to corresponding template parameters
//  from left to right.
//  normal conversions apply for explicit speficified arguments.
template <typename T>
bool compare(const T &lhs, const T &rhs) {}

int main() {
    long value;
    compare(value, 1024);  // error: template parameters doesn't match
    compare<int>(value, 1024);
    compare<long>(value, 1024);
}

// array parameter
void print(const int arr[10]);
void print(const int *arr);
void print(const int arr[]);

// pass array size by STL convetions: iterator!
void print(const int *begin, const int *end);

// array reference parameter, array size is part of the parameter
// void f(int &arr[10]);  // error: declares arr as an array of references
void f(int (&arr)[10]);  // ok: arr is a reference to an array

template <typename T, int N>
void f(T (&arr)[N]);

// pass a multidimensional array
void print(int (*matrix)[10], int row); 
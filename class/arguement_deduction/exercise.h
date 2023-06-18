#ifndef EXERCISE_H_
#define EXERCISE_H_

#include <iostream>

template <typename IT, typename T>
IT find(IT begin, IT end, const T &val) {
    while (begin != end && *begin != val) begin++; 
    return begin;                                   
}

template <typename T, int N>
int array_size(T (&arr)[N]) {
    return N;
}

#endif  // EXERCISE_H_
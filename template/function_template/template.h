#ifndef TEMPLATE_H_
#define TEMPLATE_H_

#include <iostream>

template <typename Iter, typename Val>
Iter find(Iter bg, Iter ed, const Val &v) {
    for (Iter it = bg; it != ed; ++it)
        if (*it == v)
            return it;
    return ed;
}

template <typename T, std::size_t N>
void print(const T (&arr)[N]) {
    for (std::size_t i = 0; i < N; ++i) {
        std::cout << arr[i] << std::endl;
    }
}

#endif
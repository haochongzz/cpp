#include <vector>
#include <iostream>

#include "exercise.h"

int main() {
    std::vector<int> v{1, 2, 3, 4, 5};

    auto it = find(v.begin(), v.end(), 3);

    std::cout << "find 3 at position: " << it - v.begin() << std::endl;

    char arr[] = {'a', 'b', 'c'};

    std::cout << "array size: " << array_size(arr) << std::endl;

    return 0;
}
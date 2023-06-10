#include <iostream>
#include <memory>

class Y {
   public:
    Y() = default;

    Y(const Y &rhs) : data(rhs.data) {
        std::cout << "Y copy constructor" << std::endl;
    }

   private:
    int data;
};

class hasY {
   public:
    hasY() = default;
    hasY(const hasY &) = delete;
    hasY(hasY &&) = default;

    Y mem;
};

int main(int argc, char **argv) {
    hasY hy, hy2 = std::move(hy);

    return 0;
}
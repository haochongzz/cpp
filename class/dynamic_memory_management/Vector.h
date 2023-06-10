#ifndef VECTOR_H_
#define VECTOR_H_

#include <memory>

// ----------------------------------------------
// | 0 | 1 | 2 | 3 | 4 | unconstructed elements |
// ----------------------------------------------
// |                   |                        |
// first_elem          first_free               cap

template <typename T>
class Vector {
   public:
    using size_type = size_t;
    using iterator = T *;
    using reference = T &;

    Vector() : first_elem(nullptr), first_free(nullptr), cap(nullptr) {}

    explicit Vector(size_type n, const T &val = T()) {
        first_elem = alloc.allocate(n);
        for (int i = n; i > 0; --i) alloc.construct(first_free++, val);
        cap = first_free;
    }

    Vector(std::initializer_list<T> il) {
        first_elem = alloc.allocate(il.size());
        for (auto &val : il) alloc.construct(first_free++, val);
        cap = first_free;
    }

    // copy constructor
    Vector(const Vector &rhs) {
        first_elem = alloc.allocate(rhs.size());
        cap = first_free =
            std::uninitialized_copy(rhs.begin(), rhs.end(), first_elem);
    }

    Vector(Vector &&rhs)
        : first_elem(rhs.first_elem), first_free(rhs.first_free), cap(rhs.cap) {
        rhs.first_elem = rhs.first_free = rhs.cap;
    }

    ~Vector() { free(); }

    Vector &operator=(const Vector &rhs) {}
    Vector &operator=(Vector &&rhs) {}
    reference operator[](size_type n) { return first_elem[n]; }

    void push_back(const T &val) {}

    void pop_back() {}

    bool empty() const { return begin() == end(); }
    size_type size() const { return first_free - first_elem; }
    size_type capacity() const { return cap - first_elem; }
    iterator begin() { return first_elem; }
    iterator end() { return first_free; }

   private:
    static std::allocator<T> alloc;

    // Class invariant: these three pointers should be either all 'nullptr' or
    // all pointing to the same memory block.
    iterator first_elem;
    iterator first_free;
    iterator cap;

    void free() {
        while (!empty()) alloc.destroy(--first_free);
        if (capacity()) alloc.deallocate(first_elem, capacity());
    }
};

template <typename T>
std::allocator<T> alloc;

#endif
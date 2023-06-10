#include "String.h"

std::allocator<char> String::alloc;

String::String(const_iterator ci) {
    while (ci && *ci != '\0') push_back(*ci++);
}

String::String(const String &rhs) {
    first_elem = alloc.allocate(rhs.size());
    first_free = cap =
        std::uninitialized_copy(rhs.cbegin(), rhs.cend(), first_elem);
}

String::String(String &&rhs)
    : first_elem(rhs.first_elem), first_free(rhs.first_free), cap(rhs.cap) {
    rhs.first_elem = rhs.first_free = rhs.cap;
}

String &String::operator=(const String &rhs) {
    iterator new_first_elem = alloc.allocate(rhs.size());
    iterator new_first_free =
        std::uninitialized_copy(rhs.cbegin(), rhs.cend(), new_first_elem);
    free();
    first_elem = new_first_elem;
    first_free = cap = new_first_free;
    return *this;
}

String &String::operator=(String &&rhs) {
    if (this != &rhs) {
        free();
        first_elem = rhs.first_elem;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.first_elem = rhs.first_free = rhs.cap = nullptr;
    }
}

String::~String() { free(); }

void String::push_back(const_reference cr) {
    if (size() == capacity()) reallocate(empty() ? 1 : 2 * capacity());
    alloc.construct(first_free++, cr);
}

void String::pop_back() {
    if (!empty()) alloc.destroy(--first_free);
}

void String::reallocate(size_type n) {
    iterator new_first_elem = alloc.allocate(n);
    iterator new_first_free = new_first_elem;
    for (auto it = begin(); it != end(); ++it)
        alloc.construct(new_first_free++, std::move(*it));
    // iterator new_first_free =
    //     std::uninitialized_copy(std::make_move_iterator(begin()),
    //                             std::make_move_iterator(end()),
    //                             new_first_elem);
    free();
    first_elem = new_first_elem;
    first_free = new_first_free;
    cap = first_elem + n;
}

void String::free() {
    if (!empty()) alloc.destroy(--first_free);
    alloc.deallocate(first_elem, capacity());
    first_elem = first_free = cap = nullptr;
}

std::ostream &operator<<(std::ostream &os, const String &s) {
    for (auto it = s.cbegin(); it != s.cend(); ++it) os << *it;
    return os;
}

#include "strvec.h"

// static data member generally should be defined outside class declaration.
std::allocator<std::string> StrVec::alloc;

StrVec::StrVec(const StrVec &rhs) {
    auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

// must specify 'noexcept' on both the declaration and definition.
StrVec::StrVec(StrVec &&rhs) noexcept
    : elements(rhs.elements), first_free(rhs.first_free), cap(rhs.cap) {
    rhs.elements = rhs.first_free = rhs.cap = nullptr;
}

StrVec &StrVec::operator=(const StrVec &rhs) {
    // call alloc_n_copy to allocate exactly as many elements as in rhs
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;

    return *this;
}

StrVec &StrVec::operator=(StrVec &&rhs) noexcept {
    if (this != &rhs) {
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;

        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

StrVec::~StrVec() { free(); }

void StrVec::push_back(const std::string &s) {
    chk_n_alloc();

    alloc.construct(first_free++, s);
}

std::pair<std::string *, std::string *> StrVec::alloc_n_copy(
    const std::string *b, const std::string *e) {
    std::string *data = alloc.allocate(e - b);

    return {data, uninitialized_copy(b, e, data)};
}

void StrVec::free() {
    if (elements) {
        for (auto p = first_free; p != elements; /* empty */)
            alloc.destroy(--p);
        alloc.deallocate(elements, capacity());
    }
}

void StrVec::reallocate() {
    size_t new_capacity = elements ? capacity() * 2 : 1;
    std::string *data = alloc.allocate(new_capacity);

    std::string *dest = data;
    std::string *src = elements;
    // exception safety?
    for (size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*src++));
    free();

    elements = data;
    first_free = dest;
    cap = elements + new_capacity;
}

#ifndef STRING_H_
#define STRING_H_

#include <iostream>
#include <memory>

// base element: char
// ----------------------------------------------
// | 0 | 1 | 2 | 3 | 4 | unconstructed elements |
// ----------------------------------------------
// |                   |                        |
// first_elem          first_free               cap

class String {
   public:
    typedef size_t size_type;
    typedef char *iterator;
    typedef const char *const_iterator;
    typedef char &reference;
    typedef const char &const_reference;

    String() : first_elem(nullptr), first_free(nullptr), cap(nullptr) {}
    String(const_iterator);
    String(const String &);
    String(String &&);
    ~String();
    
    String &operator=(const String &);
    String &operator=(String &&);
    reference &operator[](size_type n) { return first_elem[n]; }
    const_reference &operator[](size_type n) const { return first_elem[n]; }

    void push_back(const_reference);
    void pop_back();

    bool empty() const { return cbegin() == cend(); }
    size_type size() const { return first_free - first_elem; }
    size_type capacity() const { return cap - first_elem; }
    iterator begin() { return first_elem; }
    iterator end() { return first_free; }
    const_iterator begin() const { return first_elem; }
    const_iterator end() const { return first_free; }
    const_iterator cbegin() const { return begin(); }
    const_iterator cend() const { return end(); }

    std::string str() const { return std::string(cbegin(), cend()); }

   private:
    static std::allocator<char> alloc;

    // Class invariant: these three pointers should be either all 'nullptr' or
    // all pointing to the same memory block.
    iterator first_elem;
    iterator first_free;
    iterator cap;

    void reallocate(size_type);
    void free();

    friend std::ostream &operator<<(std::ostream &, const String &);
};

std::ostream &operator<<(std::ostream &, const String &);

#endif
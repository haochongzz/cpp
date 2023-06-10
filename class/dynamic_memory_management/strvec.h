#ifndef STRVEC_H_
#define STRVEC_H_

#include <memory>
#include <string>
#include <utility>

// ----------------------------------------------
// | 0 | 1 | 2 | 3 | 4 | unconstructed elements |
// ----------------------------------------------
// |                   |                        |
// elements            first_free               cap

class StrVec {
   public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(const StrVec &);
    // the compiler synthesizes the move constructor and move-assignment
    // operator only if its own copy-control members are not defined and all
    // data members can be moved.
    StrVec(StrVec &&) noexcept;
    StrVec &operator=(const StrVec &);
    StrVec &operator=(StrVec &&) noexcept;
    ~StrVec();

    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }

    void push_back(const std::string &s);

   private:
    static std::allocator<std::string> alloc;
    std::string *elements;
    std::string *first_free;
    std::string *cap;

    void chk_n_alloc() {
        if (size() == capacity()) reallocate();
    }
    std::pair<std::string *, std::string *> alloc_n_copy(const std::string *,
                                                         const std::string *);
    void reallocate();
    void free();
};

#endif
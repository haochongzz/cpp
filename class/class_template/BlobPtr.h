#ifndef BLOBPTR_H_
#define BLOBPTR_H_

#include <memory>
#include <string>
#include <vector>

// forward declarations of friend function templates.
template <typename T>
class BlobPtr;
template <typename T>
bool operator==(const BlobPtr<T> &, const BlobPtr<T> &);
template <typename T>
bool operator<(const BlobPtr<T> &, const BlobPtr<T> &);

template <typename T>
class Blob;

template <typename T>
class BlobPtr {
   public:
    using size_type = typename std::vector<T>::size_type;

    BlobPtr() : wptr(), curr(0) {}
    explicit BlobPtr(Blob<T> &b, size_type pos = 0) : wptr(b.data), curr(0) {}

    // implicitly synthesized copy-control members?

    T &operator*();
    T *operator->();

    BlobPtr &operator++();
    BlobPtr operator++(int);
    BlobPtr &operator--();
    BlobPtr operator--(int);

   private:
    std::weak_ptr<std::vector<T>> wptr;
    size_type curr;

    std::shared_ptr<std::vector<T>> check(const std::string &);

    friend bool operator==<T>(const BlobPtr &, const BlobPtr &);
    friend bool operator< <T>(const BlobPtr &, const BlobPtr &);
};

template <typename T>
T &BlobPtr<T>::operator*() {
    auto sp = check("deference out of range");
    return (*sp)[curr];
}

template <typename T>
T *BlobPtr<T>::operator->() {
    // delegate the real work to operator *.
    return &this->operator*();
}

template <typename T>
BlobPtr<T> &BlobPtr<T>::operator++() {
    check("increment out of range");
    ++curr;
    return *this;
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator++(int) {
    auto ret = *this;
    ++*this;
    return ret;
}

template <typename T>
BlobPtr<T> &BlobPtr<T>::operator--() {
    check("decrement out of range");
    --curr;
    return *this;
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator--(int) {
    auto ret = *this;
    --*this;
    return ret;
}

template <typename T>
std::shared_ptr<std::vector<T>> BlobPtr<T>::check(const std::string &msg) {
    auto sptr = wptr.lock();
    if (!sptr) throw std::runtime_error("unbound BlobPtr.");
    if (curr >= sptr->size()) throw std::out_of_range(msg);
    return sptr;
}

template <typename T>
bool operator==(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
    // compare identity
    return lhs.wptr.lock() == rhs.wptr.lock() && lhs.curr == rhs.curr;
}

template <typename T>
bool operator!=(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
    return !(lhs == rhs);
}

template <typename T>
bool operator<(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
    // compare identity
    return lhs.wptr.lock() == rhs.wptr.lock() && lhs.curr < rhs.curr;
}

template <typename T>
bool operator>(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
    return rhs < lhs;
}

template <typename T>
bool operator<=(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
    return !(lhs > rhs);
}

template <typename T>
bool operator>=(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
    return !(lhs < rhs);
}

#endif  // BLOBPTR_H_
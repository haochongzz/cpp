#ifndef CONSTBLOBPTR_H_
#define CONSTBLOBPTR_H_

#include <memory>
#include <string>
#include <vector>

// forward declarations of friend function templates.
template <typename T>
class ConstBlobPtr;
template <typename T>
bool operator==(const ConstBlobPtr<T> &, const ConstBlobPtr<T> &);
template <typename T>
bool operator<(const ConstBlobPtr<T> &, const ConstBlobPtr<T> &);

template <typename T>
class Blob;

template <typename T>
class ConstBlobPtr {
   public:
    using size_type = typename std::vector<T>::size_type;

    ConstBlobPtr() : wptr(), curr(0) {}
    explicit ConstBlobPtr(const Blob<T> &b, size_type pos = 0)
        : wptr(b.data), curr(pos) {}

    // implicitly synthesized copy-control members?

    const T &operator*() const;
    const T *operator->() const;

    ConstBlobPtr &operator++();
    ConstBlobPtr operator++(int);
    ConstBlobPtr &operator--();
    ConstBlobPtr operator--(int);

   private:
    std::weak_ptr<std::vector<T>> wptr;
    size_type curr;

    std::shared_ptr<std::vector<T>> check(const std::string &) const;

    friend bool operator==<T>(const ConstBlobPtr &, const ConstBlobPtr &);
    friend bool operator< <T>(const ConstBlobPtr &, const ConstBlobPtr &);
};

template <typename T>
const T &ConstBlobPtr<T>::operator*() const {
    const auto sp = check("deference out of range");
    return (*sp)[curr];
}

template <typename T>
const T *ConstBlobPtr<T>::operator->() const {
    // delegate the real work to operator *.
    return &this->operator*();
}

template <typename T>
ConstBlobPtr<T> &ConstBlobPtr<T>::operator++() {
    check("increment out of range");
    ++curr;
    return *this;
}

template <typename T>
ConstBlobPtr<T> ConstBlobPtr<T>::operator++(int) {
    auto ret = *this;
    ++*this;
    return ret;
}

template <typename T>
ConstBlobPtr<T> &ConstBlobPtr<T>::operator--() {
    check("decrement out of range");
    --curr;
    return *this;
}

template <typename T>
ConstBlobPtr<T> ConstBlobPtr<T>::operator--(int) {
    auto ret = *this;
    --*this;
    return ret;
}

template <typename T>
std::shared_ptr<std::vector<T>> ConstBlobPtr<T>::check(
    const std::string &msg) const {
    auto sptr = wptr.lock();
    if (!sptr) throw std::runtime_error("unbound ConstBlobPtr.");
    if (curr >= sptr->size()) throw std::out_of_range(msg);
    return sptr;
}

template <typename T>
bool operator==(const ConstBlobPtr<T> &lhs, const ConstBlobPtr<T> &rhs) {
    // compare identity
    return lhs.wptr.lock() == rhs.wptr.lock() && lhs.curr == rhs.curr;
}

template <typename T>
bool operator!=(const ConstBlobPtr<T> &lhs, const ConstBlobPtr<T> &rhs) {
    return !(lhs == rhs);
}

template <typename T>
bool operator<(const ConstBlobPtr<T> &lhs, const ConstBlobPtr<T> &rhs) {
    // compare identity
    return lhs.wptr.lock() == rhs.wptr.lock() && lhs.curr < rhs.curr;
}

template <typename T>
bool operator>(const ConstBlobPtr<T> &lhs, const ConstBlobPtr<T> &rhs) {
    return rhs < lhs;
}

template <typename T>
bool operator<=(const ConstBlobPtr<T> &lhs, const ConstBlobPtr<T> &rhs) {
    return !(lhs > rhs);
}

template <typename T>
bool operator>=(const ConstBlobPtr<T> &lhs, const ConstBlobPtr<T> &rhs) {
    return !(lhs < rhs);
}

#endif  // CONSTBLOBPTR_H_
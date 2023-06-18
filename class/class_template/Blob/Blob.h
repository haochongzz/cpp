#ifndef BLOB_H_
#define BLOB_H_

#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

// forward declarations of friend class.
template <typename T>
class BlobPtr;
template <typename T>
class ConstBlobPtr;

template <typename T>
class Blob {
   public:
    using size_type = typename std::vector<T>::size_type;

    using iterator = BlobPtr<T>;
    using const_iterator = ConstBlobPtr<T>;

    Blob() : data(std::make_shared<std::vector<T>>()) {}

    Blob(std::initializer_list<T> il)
        : data(std::make_shared<std::vector<T>>(il)) {}
    
    template <typename It>
    Blob(It b, It e) : data(std::make_shared<std::vector<T>>(b, e)) {}

    Blob(const Blob &);
    Blob &operator=(const Blob &);

    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }

    void push_back(const T &);
    void push_back(T &&);
    void pop_back();

    const T &front() const;
    T &front();
    const T &back() const;
    T &back();

    const T &at(size_type pos) const;
    T &at(size_type pos);
    const T &operator[](size_type pos) const;
    T &operator[](size_type pos);

    const_iterator begin() const { return const_iterator(*this); }
    iterator begin() { return iterator(*this); }
    const_iterator end() const { return const_iterator(*this, size()); }
    iterator end() { return iterator(*this, size()); }
    const_iterator cbegin() const { return begin(); }
    const_iterator cend() const { return end(); }

   private:
    // value-like
    std::shared_ptr<std::vector<T>> data;

    void check(size_type pos, const std::string &msg) const {
        if (pos >= size())  // [0, size)
            throw std::out_of_range(msg);
    }

    friend class BlobPtr<T>;
    friend class ConstBlobPtr<T>;
};

template <typename T>
Blob<T>::Blob(const Blob &rhs)
    : data(std::make_shared<std::vector<T>>(*rhs.data)) {}

template <typename T>
Blob<T> &Blob<T>::operator=(const Blob &rhs) {
    data = std::make_shared<std::vector<T>>(*rhs.data);
    return *this;
}

template <typename T>
void Blob<T>::push_back(const T &rhs) {
    data.push_back();
}

template <typename T>
void Blob<T>::push_back(T &&rhs) {
    data->push_back(std::move(rhs));
}

template <typename T>
void Blob<T>::pop_back() {
    check(0, "pop_back on empty Blob");
    data->pop_back();
}

template <typename T>
const T &Blob<T>::front() const {
    check(0, "front on empty Blob");
    return data->front();
}

template <typename T>
T &Blob<T>::front() {
    check(0, "front on empty Blob");
    return data->front();
}

template <typename T>
const T &Blob<T>::back() const {
    check(0, "back on empty Blob");
    return data->back();
}

template <typename T>
T &Blob<T>::back() {
    check(0, "back on empty Blob");
    return data->back();
}

template <typename T>
const T &Blob<T>::at(size_type pos) const {
    check(pos, "Blob subscript out of range");
    return (*data)[pos];
}

template <typename T>
T &Blob<T>::at(size_type pos) {
    return const_cast<T &>(const_cast<const Blob &>(*this).at(pos));
}

template <typename T>
const T &Blob<T>::operator[](size_type pos) const {
    return at(pos);
}

template <typename T>
T &Blob<T>::operator[](size_type pos) {
    return at(pos);
}

#endif  // BLOB_H_

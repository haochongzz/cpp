#ifndef SHAREDPOINTER_H_
#define SHAREDPOINTER_H_

#include <atomic>

template <typename T>
class SharedPointer {
   public:
    SharedPointer() = default;

    SharedPointer(T *ptr) : ptr_(ptr), ref_count_(new std::atomic<int>(1)) {}

    SharedPointer(const SharedPointer &rhs) {
        ptr_ = rhs.ptr_;
        ref_count_ = rhs.ref_count_;
        if (ref_count_) (*ref_count_)++;  // atomic increment
    }

    SharedPointer<T> &operator=(const SharedPointer &rhs) {
        if (this != &rhs) {
            release();
            ptr_ = rhs.ptr_;
            ref_count_ = rhs.ref_count_;
            if (ref_count_) (*ref_count_)++;  // atomic increment
        }
    }

    T &operator*() const {
        return *ptr_;
    }

    T *operator->() const {
        // return &(this->operator*());
        return ptr_;
    }

    ~SharedPointer() { release(); }

   private:
    T *ptr_;
    std::atomic<int> *ref_count_;

    void release() {
        if (ref_count_ && --(*ref_count_) == 0) {
            delete ptr_;
            delete ref_count_;
            ptr_ = ref_count_ = nullptr;
        }
    }
};

#endif

#ifndef SALESDATA_H_
#define SALESDATA_H_

#include <string>

// 令一个类展现出类指针行为的最好方法是使用shared_ptr来管理类中资源。但是，有时我们希望
// 直接管理，则使用引用计数 reference count
class HasPtr {
public:
    // constructor allocates a new string and a new counter, which it sets to 1
    HasPtr(const std::string &s = std::string()): ps_(new std::string(s)), i_(0), use_(new std::size_t(1)) {}

    // copy constructor copies all three data members and increments the counter
    HasPtr(const HasPtr &p): ps_(p.ps_), i_(p.i_), use_(p.use_) { ++ *use_; }

    HasPtr& operator=(const HasPtr &p) {
        ++ *p.use_;
        if (-- *use_ == 0) {
            delete ps_;
            delete use_;
        }
        ps_ = p.ps_;
        i_ = p.i_;
        use_ = p.use_;
        return *this;
    }
    
    ~HasPtr() {
        if (-- *use_ == 0) {
            delete ps_;
            delete use_;
        }
    }

private:
    std::string *ps_;
    int i_;
    std::size_t *use_; // member to keep track of how many objects share
};

#endif
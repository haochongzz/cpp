#ifndef SALESDATA_H_
#define SALESDATA_H_

#include <string>

class HasPtr {
public:
    HasPtr(const std::string &s = std::string()): ps_(new std::string(s)), i_(0) { }

    // each HasPtr has its own copy of the string to which ps points
    HasPtr(const HasPtr &p): ps_(new std::string(*p.ps_)), i_(p.i_) { }
    
    // 即使被赋值的对象是自身，也能保证是正确的.
    HasPtr& operator=(const HasPtr &p) {
        std::string *ps = new std::string(*p.ps_);
        delete ps_;
        ps_ = ps;
        i_ = p.i_;
        return *this;
    }
    
    ~HasPtr() { delete ps_; }

private:
    std::string *ps_;
    int i_;
};

#endif
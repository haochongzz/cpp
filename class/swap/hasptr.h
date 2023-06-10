#include <iostream>
#include <string>

// valuelike
class HasPtr {
   public:
    HasPtr(const std::string &s = std::string())
        : ps(new std::string(s)), i(0) {}
    HasPtr(const char *cs) : ps(new std::string(cs)), i(0) {}

    // each HasPtr has its own copy of the string to which ps points
    HasPtr(const HasPtr &p) : ps(new std::string(*p.ps)), i(p.i) {}
    HasPtr(HasPtr &&p) : ps(p.ps), i(p.i) {
        p.ps = 0;
        p.i = 0;
    }

    HasPtr &operator=(const HasPtr &);
    HasPtr &operator=(HasPtr);

    bool operator<(const HasPtr &rhs) const;

    ~HasPtr() { delete ps; }  // implicitly inline

   private:
    std::string *ps;
    int i;

    friend void swap(HasPtr &lhs, HasPtr &rhs);
};

// implementation 1
HasPtr &HasPtr::operator=(const HasPtr &rhs) {
    auto newp = new std::string(*rhs.ps);
    delete ps;
    ps = newp;
    i = rhs.i;
    return *this;
}

// implementation 2: use Swap in assignment operator
// note: this is an ambigous overloaded = operator
// when the passed-in argument is a lvalue, copy constructor is used, move
// constructor is used if rvalue.
HasPtr &HasPtr::operator=(HasPtr rhs) {
    swap(*this, rhs);
    return *this;
}

bool HasPtr::operator<(const HasPtr &rhs) const {
    std::cout << "operator< between <" << *ps << "> and <" << *rhs.ps << ">"
              << std::endl;
    return *ps < *rhs.ps;
}

inline void swap(HasPtr &lhs, HasPtr &rhs) {
    using std::swap;

    std::cout << "swap(HasPtr &lhs, HasPtr &rhs) between <" << *lhs.ps
              << "> and <" << *rhs.ps << ">" << std::endl;

    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
}
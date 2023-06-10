#ifndef CONSTSTRBLOBPTR_H_
#define CONSTSTRBLOBPTR_H_

#include <memory>
#include <string>
#include <vector>

class StrBlob;

class ConstStrBlobPtr {
   public:
    typedef std::vector<std::string>::size_type size_type;

    ConstStrBlobPtr();
    explicit ConstStrBlobPtr(const StrBlob &sb, size_type pos = 0);

    const std::string &operator*() const;
    const std::string *operator->() const;
     
    ConstStrBlobPtr &operator++();
    ConstStrBlobPtr operator++(int);
    ConstStrBlobPtr &operator--();
    ConstStrBlobPtr operator--(int);

   private:
    std::weak_ptr<std::vector<std::string>> wptr;
    size_type curr;

    std::shared_ptr<std::vector<std::string>> check(
        size_type pos, const std::string &msg) const;

    friend bool operator==(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator!=(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator<(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator>(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator<=(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator>=(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
};

bool operator==(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
bool operator!=(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
bool operator<(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
bool operator>(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
bool operator<=(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
bool operator>=(const ConstStrBlobPtr &, const ConstStrBlobPtr &);

#endif
#include "ConstStrBlobPtr.h"

#include "StrBlob.h"

ConstStrBlobPtr::ConstStrBlobPtr() : wptr(), curr(0) {}
ConstStrBlobPtr::ConstStrBlobPtr(const StrBlob &sb, size_type pos)
    : wptr(sb.data), curr(pos) {}

std::shared_ptr<std::vector<std::string>>
ConstStrBlobPtr::check(size_type pos, const std::string &msg) const {
  auto ret = wptr.lock();
  if (!ret)
    throw std::runtime_error("unbound ConstStrBlobPtr");
  if (pos >= ret->size())
    throw std::out_of_range(msg);
  return ret;
}

const std::string &ConstStrBlobPtr::operator*() const {
  auto sp = check(curr, "deference past end of ConstStrBlobPtr");
  return (*sp)[curr];
}

const std::string *ConstStrBlobPtr::operator->() const {
  // delegate the real work to the dereference operator.
  return & this->operator*();
}

ConstStrBlobPtr &ConstStrBlobPtr::operator++() {
  check(curr, "increment past end of ConstStrBlobPtr");
  ++curr;
  return *this;
}

ConstStrBlobPtr ConstStrBlobPtr::operator++(int) {
  auto ret = *this;
  ++*this;
  return ret;
}

ConstStrBlobPtr &ConstStrBlobPtr::operator--() {
  --curr;
  check(curr, "decrement past begin of ConstStrBlobPtr");
  return *this;
}

ConstStrBlobPtr ConstStrBlobPtr::operator--(int) {
  auto ret = *this;
  --*this;
  return ret;
}

bool operator==(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
  // compare identity
  return lhs.wptr.lock() == rhs.wptr.lock() && lhs.curr == rhs.curr;
}

bool operator!=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
  return !(lhs == rhs);
}

bool operator<(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
  return lhs.wptr.lock() == rhs.wptr.lock() && lhs.curr < rhs.curr;
}

bool operator>(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
  return rhs < lhs;
}

bool operator<=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
  return !(lhs > rhs);
}

bool operator>=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
  return !(lhs < rhs);
}
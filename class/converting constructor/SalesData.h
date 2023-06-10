#ifndef SALESDATA_H_
#define SALESDATA_H_

#include <iostream>
#include <string>

class SalesData {
public:
    SalesData(std::string s, unsigned cnt, double price) : book_no(s), units_sold(cnt), revenue(cnt * price) {}

    SalesData() : SalesData("", 0, 0) {}

    // 如果构造函数只接受一个实参，则实际上定义了实参转换为此class type的隐式转换规则。
    // string null_book = "null";
    // 构造了一个临时SalesData对象, null_book被隐式的转换成SalesData对象。
    // item.combine(nullbook)
    SalesData(std::string s) : SalesData(s, 0, 0) {}

    // 抑制构造函数定义的隐式类型转换。只能在类内声明构造函数时使用explicit关键字。
    explicit SalesData(std::istream &is) : SalesData() { read(is, *this); }

    SalesData &combine(const SalesData &rhs);

    friend std::istream &read(std::istream &is, SalesData &rhs);

private:
    std::string book_no;
    unsigned units_sold;
    double revenue;
};

SalesData &SalesData::combine(const SalesData &rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

std::istream &read(std::istream &is, SalesData &rhs) {
    is >> rhs.book_no >> rhs.units_sold >> rhs.revenue;
    return is;
}

#endif
#ifndef SALESDATA_H_
#define SALESDATA_H_

#include <iostream>
#include <string>

class SalesData {
public:
    SalesData(std::string s, unsigned cnt, double price) : book_no(s), units_sold(cnt), revenue(cnt * price) {}

    // 其余构造函数全部委托给另一个构造函数
    SalesData() : SalesData("", 0, 0) {}
    SalesData(std::string s) : SalesData(s, 0, 0) {}
    SalesData(std::istream &is) : SalesData() { read(is, *this); }

private:
    std::string book_no;
    unsigned units_sold;
    double revenue;
};

#endif

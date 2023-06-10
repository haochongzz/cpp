#ifndef SALESDATA_H_
#define SALESDATA_H_

#include <iostream>
#include <string>

class SalesData {
public:
    // other members and constructors as before
    SalesData(std::string s, unsigned cnt, double price) : book_no_(s), unit_sold_(cnt), revenue_(cnt * price) {}
    
    // declaration equivalent to the synthesized copy constructor
    // 调用函数时，非引用类型的参数需要拷贝初始化，同样的，非引用类型的函数返回值也需要
    // 拷贝初始化。这个特性解释了为什么拷贝构造函数的参数是引用类型的。cycle！
    SalesData(const SalesData&);

    // 我们可以将拷贝控制成员定义为=default来显式的要求编译器生成synthesized version
    // 生成的合成函数是内联函数. 如果不希望这样，需要在类外定义使用=default.
    SalesData &operator=(const SalesData&) = default;

private:
    std::string book_no_;
    int unit_sold_;
    double revenue_;
};

#endif
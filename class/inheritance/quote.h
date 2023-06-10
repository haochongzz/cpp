#ifndef QUOTE_H_
#define QUOTE_H_

#include <iostream>
#include <string>

class Quote {
   public:
    Quote() = default;
    Quote(const std::string &book, double sales_price)
        : book_no(book), price(sales_price) {}

    virtual ~Quote() = default;

    std::string isbn() const { return book_no; }
    virtual double net_price(std::size_t n) const { return n * price; }
    virtual std::ostream &debug(std::ostream &os) const;

   private:
    std::string book_no;

   protected:
    double price = 0.0;
};

#endif
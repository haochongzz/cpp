#include "quote.h"

std::ostream &Quote::debug(std::ostream &os) const {
    os << "Quote::book_no " << book_no << " Quote::price: " << price;
    return os;
}